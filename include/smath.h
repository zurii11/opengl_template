#ifndef STUPID_MATH_H
#define STUPID_MATH_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct vec2
{
    float x;
    float y;
} vec2;

typedef struct vec3
{
    float x;
    float y;
    float z;
} vec3;

typedef struct vec4
{
    float x;
    float y;
    float z;
    float w;
} vec4;

typedef float mat4[4][4];

typedef enum AXIS {
    X,
    Y,
    Z
} AXIS;

static float radians(float degrees)
{
    return degrees * (M_PI / 180);
}

static float degrees(float radians)
{
    return radians * (180 / M_PI);
}

static void scale(mat4 matrix, float scale)
{
    matrix[0][0] = scale;
    matrix[1][1] = scale;
    matrix[2][2] = scale;
}

static void translate(mat4 matrix, vec3 translation_vector)
{
    matrix[0][3] += translation_vector.x;
    matrix[1][3] += translation_vector.y;
    matrix[2][3] += translation_vector.z;
}

static void rotate(mat4 matrix, float angle_radians, AXIS axis)
{
    switch(axis) {
        case X:
            matrix[1][1] = cosf(angle_radians);
            matrix[1][2] = sinf(angle_radians)*-1;
            matrix[2][1] = sinf(angle_radians);
            matrix[2][2] = cosf(angle_radians);
            break;
        case Y:
            matrix[0][0] = cosf(angle_radians);
            matrix[0][2] = sinf(angle_radians);
            matrix[2][0] = sinf(angle_radians)*-1.0f;
            matrix[2][2] = cosf(angle_radians);
            break;
        case Z:
            matrix[0][0] = cosf(angle_radians);
            matrix[0][1] = sinf(angle_radians)*-1.0f;
            matrix[1][0] = sinf(angle_radians);
            matrix[1][1] = cosf(angle_radians);
            break;
    }
    
}

static void multiplyMatrices(mat4 result, mat4 matrixA, mat4 matrixB)
{
    // Temporary matrix needed incase the result matrix
    // is one of the matrices used in multiplication
    mat4 temp = {0};
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            temp[row][col] = 0;
            for(int i = 0; i < 4; i++) {
                temp[row][col] += matrixA[row][i] * matrixB[i][col];
            }
        }
    }

    memcpy(result, temp, sizeof(temp));
}

// Pass by reference
static void setIdentityMatrix(mat4 matrix)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

/* Dynamically allocate memory for martrix
static float** genIdentityMatrix()
{
    // Allocate memory for 4 pointers to floats
    float** identity_matrix = malloc(4 * sizeof(float*));
    // Allocate memory for 4 floats and set the pointers in the array,
    // creating a 2d array, which is an array of pointers to other arrays
    for(int i = 0; i < 4; i++) {
        identity_matrix[i] = malloc(4 * sizeof(float));
    }

    // Set the identity matrix
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            // When i == j the positions follow a diagonal pattern
            // 1 0 0 0 - i0 j0
            // 0 1 0 0 - i1 j1
            // 0 0 1 0 - i2 j2
            // 0 0 0 1 - i3 j3
            identity_matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }

    return identity_matrix;
}

static void freeMatrix(float** matrix)
{
    for(int i = 0; i < 4; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
*/

static void logMat4(mat4 matrix)
{
    for(unsigned int i = 0; i < 4; i++) {
        for(unsigned int j = 0; j < 4; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

#endif