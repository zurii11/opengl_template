#ifndef SHAPES_H
#define SHAPES_H

typedef unsigned int uint;
typedef unsigned long ulong;

typedef struct Rect
{
    float* vertices;
    uint* indices;
    uint sizeOfVertices;
    uint sizeOfIndices; 
} Rect;


static void drawRect(Rect* rect, uint VAO, uint VBO, uint EBO)
{
    printf("VERTICES: %lu\n", sizeof(rect->vertices));
    printf("INDICES: %lu\n", sizeof(rect->indices));
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy dara from vertices to VBO using GL_STATIC_DRAW(data is set once, used many times)
    glBufferData(GL_ARRAY_BUFFER, rect->sizeOfVertices, rect->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Copy dara from indices to EBO using GL_STATIC_DRAW(data is set once, used many times)
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, rect->sizeOfIndices, rect->indices, GL_STATIC_DRAW);
    // Configure the attributes
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Unbind the VBO, it is already saved with VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

#endif