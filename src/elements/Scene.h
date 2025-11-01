#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Camera.h"

typedef struct __attribute__((packed)) Scene3D {
    Camera3D *mainCamera;
    Object objects[32];
} Scene3D;

Scene3D *scene3d_create(Camera3D *camera)
{
    Scene3D *scene = (Scene3D *) malloc(sizeof(Scene3D));
    scene->mainCamera = camera;
    return scene;
}

void renderScene(Scene3D *scene)
{
    
}

#endif//SCENE_H