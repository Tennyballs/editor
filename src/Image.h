#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

typedef struct __attribute__((packed)) Image
{
    int width, height, channels;
    unsigned char *data;
} Image;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image *load_image(const char *__src)
{
    Image *img = (Image *)malloc(sizeof(Image));
    int width, height, channels;
    unsigned char *data = stbi_load(__src, &width, &height, &channels, 0);
    if(data==NULL)
    {
        free(img);
        printf("Error stbi_load('%s')\n", __src);
        return NULL;
    }
    img->data = data;
    img->width = width;
    img->height = height;
    img->channels = channels;

    return img;
}
#endif//IMAGE_H