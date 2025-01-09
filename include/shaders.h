#ifndef SHADERS_H
#define SHADERS_H

#include <glad/glad.h>
#include <stdio.h>
#include <stddef.h>

unsigned int shader_ids[5]; // Arbitrary length
unsigned int shader_count = 0;

// Read and create shaders
// Return shader id on success, -1 on error
static int load_shader(char* filename, GLenum shader_type)
{
    FILE *file_ptr;
    if((file_ptr = fopen(filename, "r")) == NULL) {
        printf("Error opening the shader file: %s\n", filename);
        return -1;
    }


    fseek(file_ptr, 0L, SEEK_END);
    size_t fsize = ftell(file_ptr);
    //fseek(file_ptr, 0L, SEEK_SET);
    rewind(file_ptr);

    char *shader_source = malloc(fsize+1);
    size_t bytes_read = fread(shader_source, 1, fsize, file_ptr);
    shader_source[bytes_read] = '\0';

    fclose(file_ptr);

//  glShaderSource expects const GLchar** or const char** which means it expects pointer to 
//  an array of strings, that's why we need to first
//  wrap shader_source in a pointer and then pass it's address
    const char* shader_source_ptr = shader_source;
    unsigned int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_source_ptr, NULL);
    glCompileShader(shader_id);

    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        printf("Error compiling vertex shader: %s", infoLog);
        return -1;
    }

    shader_ids[shader_count] = shader_id;
    shader_count++;

    return shader_id;
}

// Create program and attach shaders
// return shader program id on success, -1 on error
static int create_shader_program()
{
    unsigned int shaderProgram = glCreateProgram();
    for(unsigned int i = 0; i < shader_count; i++) {
        glAttachShader(shaderProgram, shader_ids[i]);
    }
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error linking shaders: %s", infoLog);
        return -1;
    }

    for(unsigned int i = 0; i < shader_count; i++) {
        glDeleteShader(shader_ids[i]);
    }

    return shaderProgram;
}
#endif