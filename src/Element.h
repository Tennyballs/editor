#ifndef ELEMENT_H
#define ELEMENT_H

#include <emscripten/emscripten.h>

typedef struct __attribute__((packed)) Vec3 {
    float x, y, z;
} Vec3;

typedef struct __attribute__((packed)) Vec2 {
    float x, y;
} Vec2;

typedef struct __attribute__((packed)) Transform {
    Vec3 position;
    Vec3 rotation;
    Vec2 skew;
    Vec2 scale;
} Transform;

typedef struct __attribute__((packed)) Element {
    const char *id;
    Transform transform;
} Element;


#endif//ELEMENT_H