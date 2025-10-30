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

EM_JS(void, ElementPush, (Element *ptr), {
    quad_ptrs.push(ptr);
})

EM_JS(void, UpdateAllElements, (), {
    quad_ptrs.forEach(ptr => {
        const id = UTF8ToString(HEAPU32[(ptr)>>2]);
        const element = document.getElementById(id);

        if(!element) {console.error(`Element with id ${id} dosent exist.`); return;}

        const x = HEAPF32[(ptr+4)>>2];
        const y = HEAPF32[(ptr+8)>>2];
        const z = HEAPF32[(ptr+12)>>2];
        const rotX = HEAPF32[(ptr+16)>>2];
        const rotY = HEAPF32[(ptr+20)>>2];
        const rotZ = HEAPF32[(ptr+24)>>2];
        const skewx = HEAPF32[(ptr+28)>>2];
        const skewy = HEAPF32[(ptr+32)>>2];
        const scaleX = HEAPF32[(ptr+36)>>2];
        const scaleY = HEAPF32[(ptr+40)>>2];

        element.style.transform = `
            translate3d(calc(-50% + ${x}px), calc(-50% + ${y}px), ${z}px)
            rotateX(${rotX}deg) rotateY(${rotY}deg) rotateZ(${rotZ}deg)
            skew(${skewx}, ${skewy})
            scale(${scaleX}, ${scaleY})
        `;


    });
})

#endif//ELEMENT_H