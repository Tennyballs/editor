#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>


typedef struct __attribute__((packed)) Position {
    long x;
    long y;
} Position;

typedef struct __attribute__((packed)) Size {
    unsigned int width;
    unsigned int height;
} Size;

typedef struct __attribute__((packed)) Transform {
    float rotateX;
    float rotateY;
    float rotateZ;
    float x;
    float y;
    float z;
} Transform;

typedef struct __attribute__((packed)) Colors {
    Color backgroundColor;
    Color color;
} Colors;

typedef struct __attribute((packed)) Border {
    float width;
    Color color;
} Border;

typedef struct __attribute__((packed)) Properties {
    const char *id;
    Colors color;
    Position position;
    Size size;
    Transform transform;
    Border border;
} Properties;

EM_JS(void, set, (Properties *properties), {
    let bytesRead = 0;

    function getString()
    {
        const ret = UTF8ToString(Module.HEAPU32[(properties + bytesRead) >> 2]);
        bytesRead += 4;
        return ret;
    }

    function getU32()
    {
        const ret = Module.HEAPU32[(properties + bytesRead) >> 2];
        bytesRead += 4;
        return ret;
    }

    function get32()
    {
        const ret = Module.HEAP32[(properties + bytesRead) >> 2];
        bytesRead += 4;
        return ret;
    }


    function getF32()
    {
        const ret = Module.HEAPF32[(properties + bytesRead) >> 2];
        bytesRead += 4;
        return ret;
    }

    function getColor()
    {
        return `#${getU32().toString(16).padStart(8,'0')}`;
    }

    function getTransform()
    {

        return `translate3d(calc(${get32()}px - 50%), calc(${get32()}px - 50%), ${get32()}px) rotateX(${getF32()}deg) rotateY(${getF32()}deg) rotateZ(${getF32()}deg)`;
    }

    const element = document.getElementById(getString());

    if(!element) return;

    element.style.backgroundColor = getColor();
    element.style.color = getColor();
    element.style.left = `${getU32()}px`;
    element.style.top = `${getU32()}px`;
    element.style.width = `${getU32()}px`;
    element.style.height = `${getU32()}px`;
    element.style.transform = getTransform();
})

#endif // PROPERTIES_H