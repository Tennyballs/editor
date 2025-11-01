#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include <math.h>

typedef struct Camera3D {
    // Projection parameters
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    // Transform
    float position[3];
    float rotation[3];
    float scale[3];
} Camera3D;

Camera3D *camera3d_create(float fov, float aspect_ratio, float near_plane, float far_plane)
{
    Camera3D *cam = (Camera3D *)malloc(sizeof(Camera3D));

    if(!cam)
    {
        return NULL;
    }

    // Projection parameters
    cam->fov         = fov;
    cam->aspectRatio = aspect_ratio;
    cam->nearPlane   = near_plane;
    cam->farPlane    = far_plane;

    for(size_t i = 0; i < 3; i++)
    {
        cam->position[i] = 0.0f;
        cam->rotation[i] = 0.0f;
        cam->scale[i] = 1.0f;
    }

    return cam;
}

// // Do we even need this?
// void camera3d_destroy(Camera3D *cam)
// {
//     if (cam) {
//         free(cam);
//     }
// }

#endif//CAMERA_H