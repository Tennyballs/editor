#ifndef COLOR_H
#define COLOR_H

typedef union Color {
    struct __attribute__((packed)) RGBA
    {
        unsigned char a;
        unsigned char b;
        unsigned char g;
        unsigned char r;
    } values;
    unsigned int value;
} Color;

#endif // COLOR_H