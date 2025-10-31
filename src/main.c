#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#include <emscripten/html5_webgl.h>

// GL
#define GLFW_INCLUDE_ES3
#include <GL/glfw.h>
#include "Image.h"



unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;


EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    SCREEN_WIDTH = uiEvent->windowInnerWidth;
    SCREEN_HEIGHT = uiEvent->windowInnerHeight;

    SCREEN_CENTER_X = (double) SCREEN_WIDTH / 2.0;
    SCREEN_CENTER_Y = (double) SCREEN_HEIGHT / 2.0;

    emscripten_set_canvas_element_size("#canvas", SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}

struct MainData
{
    EmscriptenWebGLContextAttributes attrs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE handle;
} MainData;

void loop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

int main()
{
    if (!glfwInit()) {
        return -1;
    }
    emscripten_webgl_init_context_attributes(&MainData.attrs);
    MainData.attrs.alpha = false;
    MainData.attrs.antialias = false;
    MainData.attrs.majorVersion = 2;
    MainData.handle = emscripten_webgl_create_context("#canvas", &MainData.attrs);
    if(emscripten_webgl_make_context_current(MainData.handle)){
        return -1;
    }
    double WIDTH, HEIGHT;
    emscripten_get_element_css_size("body", &WIDTH, &HEIGHT);
    SCREEN_WIDTH = WIDTH;
    SCREEN_HEIGHT = HEIGHT;
    SCREEN_CENTER_X = WIDTH / 2.0;
    SCREEN_CENTER_Y = HEIGHT / 2.0;
    emscripten_set_canvas_element_size("#canvas", SCREEN_WIDTH, SCREEN_HEIGHT);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, true, resizeCallback);

    Image *img = load_image("/Niko.png");
    printf("Image '%s' loaded with success!\n", "/Niko.png");
    printf("Image dimensions: %ix%i\n", img->width, img->height);
    

    printf("Success!\n");
    emscripten_set_main_loop(loop, -1, true);
    return 0;
}
