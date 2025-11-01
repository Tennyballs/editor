#ifndef MAIN_H
#define MAIN_H

#include "Image.h"
#include "Helper.h"
#include "Object.h"

unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;

Object *objects;
uint32_t objectsLength;

struct MainData
{
    GLuint shaderProgram;
    EmscriptenWebGLContextAttributes attrs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE handle;
} MainData;

void objects_realloc(int add)
{
    objectsLength+=add;
    if(!objects)
    {
        objects = (Object *)malloc(sizeof(Object) * (objectsLength));
    }

    realloc(objects, sizeof(Object) * (objectsLength));
}

#endif//MAIN_H