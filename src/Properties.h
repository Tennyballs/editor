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
} Transform;

typedef struct __attribute__((packed)) Properties {
    const char *id;
    union Color backgroundColor, textColor;
    Position position;
    Size size;
    Transform transform;
} Properties;

EM_JS(void, set, (Properties *properties), {
    const offset = properties;
    const element = document.getElementById(UTF8ToString(Module.HEAPU32[(offset + 0) >> 2]));

    if(!element) return;

    element.style.backgroundColor = `#${Module.HEAPU32[(offset + 4) >> 2].toString(16).padStart(8,'0')}`;
    element.style.color = `#${Module.HEAPU32[(offset + 8) >> 2].toString(16).padStart(8,'0')}`;
    element.style.left = Module.HEAPU32[(offset + 12) >> 2] + "px";
    element.style.top = Module.HEAPU32[(offset + 16) >> 2] + "px";
    element.style.width = Module.HEAPU32[(offset + 20) >> 2] + "px";
    element.style.height = Module.HEAPU32[(offset + 24) >> 2] + "px";
    element.style.transform = `translate(-50%, -50%) rotateX(${ Module.HEAPF32[(offset + 28) >> 2] }deg) rotateY(${ Module.HEAPF32[(offset + 32) >> 2] }deg) rotateZ(${ Module.HEAPF32[(offset + 36) >> 2] }deg) `;
})

#endif // PROPERTIES_H