#ifndef OBJECT_H
#define OBJECT_H

#include "Vector.h"

typedef struct __attribute__((packed)) Object {
    GLuint VAO, position, uv, textureID, EBO;
} Object;


void object_draw();

Object object_create_from_points(float *vertices);

#endif//OBJECT_H