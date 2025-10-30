#ifndef ELEMENT_H
#define ELEMENT_H

#include <emscripten/emscripten.h>

typedef struct __attribute__((packed)) Border
{
    int width;
    char type;
    Color fill;
} Border;

typedef struct __attribute__((packed)) Vec3 {
    float x, y, z;
} Vec3;

typedef struct __attribute__((packed)) Vec2 {
    float x, y;
} Vec2;

typedef struct __attribute__((packed)) Style {
    Vec3 position;
    Vec3 rotation;
    Vec2 skew;
    Vec2 scale;
} Struct;

typedef struct __attribute__((packed)) Element {
    const char *id;
    struct Style style;
    struct Border border;
} Element;

EM_JS(void, ElementPush, (Element *ptr), {
    quad_ptrs.push(ptr);
})

EM_JS(void, ElementApplyChanges, (Element *ptr), {

    const id = UTF8ToString(HEAPU32[(ptr)>>2]);
    let element = document.getElementById(id);
    if(!element)
    {

#ifdef ELEMENT_AUTO_INIT

        // console.warn("Element not found, Auto init enabled.");

        element = document.createElement('div');
        element.id = id;
        element.classList.add('quad');
        document.body.appendChild(element);
        // console.log(element);

#else // ELEMENT_AUTO_INIT

        console.error("Element not found, did you initialize it?");
        return;
#endif // ELEMENT_AUTO_INIT

    }

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
        rotateX(${rotX}deg) rotateX(${rotY}deg) rotateZ(${rotZ}deg)
        skew(${skewx}, ${skewy})
        scale(${scaleX}, ${scaleY})
    `;
})

#endif//ELEMENT_H