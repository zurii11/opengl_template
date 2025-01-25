#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct Batch {
    float* vertices;
    uint* indices;
    uint vertex_count; // current number of vertices
    uint index_count; // current number of indices
    uint vao;
    uint vbo;
    uint ebo;
    uint vertex_capacity;
    uint index_capacity;
} Batch;

typedef struct Rect
{
    float* vertices;
    uint* indices;
    uint size_of_vertices;
    uint size_of_indices; 
} Rect;

void batch_init(Batch* batch)
{
    glGenVertexArrays(1, &batch->vao);
    glGenBuffers(1, &batch->vbo);
    glGenBuffers(1, &batch->ebo);

    batch->vertex_capacity = 1024;
    batch->index_capacity = 2048;

    batch->vertices = malloc(batch->vertex_capacity * 8 * sizeof(float));
    batch->indices= malloc(batch->index_capacity * sizeof(uint));
    batch->vertex_count = 0;
    batch->index_count = 0;

    glBindVertexArray(batch->vao);
    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

// ensure capacity, if needed more, double _capacity and reallocate(4 vertices per rect, 6 indices per rect)
// memcpy rect->vertices to batch->vertices(count*8)
// Append indices with offset
// increase vertex count and index count
void batch_add_rect(Batch* batch, Rect* rect)
{
    uint rect_vertex_count = rect->size_of_vertices / 8 / sizeof(float);
    uint rect_index_count = rect->size_of_indices / sizeof(uint);

    if(batch->vertex_count + rect_vertex_count > batch->vertex_capacity)
    {
        batch->vertex_capacity *= 2;
        batch->vertices = realloc(batch->vertices, batch->vertex_capacity * 8 * sizeof(float));
    }

    if(batch->index_count + rect_index_count > batch->index_capacity)
    {
        batch->index_capacity *= 2;
        batch->indices = realloc(batch->indices, batch->index_capacity * sizeof(uint));
    }

    memcpy(batch->vertices + (batch->vertex_count * 8), rect->vertices, rect->size_of_vertices);

    for(int i = 0; i < rect_index_count; i++) {
        batch->indices[batch->index_count + i] = rect->indices[i] + batch->vertex_count;
    }

    batch->vertex_count += rect_vertex_count;
    batch->index_count += rect_index_count;
}

// exit if 0 vertices
// use buffer oprhaning for performance for vbo and ebo
// bind vao
// draw call
// reset counts
void batch_flush(Batch* batch)
{
    if(batch->vertex_count == 0) return;

    glBindBuffer(GL_ARRAY_BUFFER, batch->vbo);
    glBufferData(GL_ARRAY_BUFFER, batch->vertex_count * 8 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, batch->vertex_count * 8 * sizeof(float), batch->vertices);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch->index_count * sizeof(uint), NULL, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, batch->index_count * sizeof(uint), batch->indices);

    glBindVertexArray(batch->vao);
    glDrawElements(GL_TRIANGLES, batch->index_count, GL_UNSIGNED_INT, 0);

    batch->vertex_count = 0;
    batch->index_count = 0;
}

#endif