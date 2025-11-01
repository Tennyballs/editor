#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#include <emscripten/html5_webgl.h>

// GL
#define GLFW_INCLUDE_ES3
#include <GL/glfw.h>

// my classes
#include "Main.h"

EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData);

void loop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (size_t i = 0; i < objectsLength; i++)
    {
        Object obj = objects[i];
        object_draw(&obj);
    }
    
    
    glFlush();
}

void setCanvasSize();

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

    setCanvasSize();

    MainData.shaderProgram = helper_basic_shader_program_setup("/shaders/2d/shader.vert", "/shaders/2d/shader.frag");
    glUseProgram(MainData.shaderProgram);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    emscripten_set_main_loop(loop, -1, true);
    return 0;
}

void setCanvasSize()
{
    double WIDTH, HEIGHT;
    emscripten_get_element_css_size("body", &WIDTH, &HEIGHT);
    SCREEN_WIDTH = WIDTH;
    SCREEN_HEIGHT = HEIGHT;
    SCREEN_CENTER_X = WIDTH / 2.0;
    SCREEN_CENTER_Y = HEIGHT / 2.0;
    emscripten_set_canvas_element_size("#canvas", SCREEN_WIDTH, SCREEN_HEIGHT);
    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, true, resizeCallback);
    glViewport(0, 0, WIDTH, HEIGHT);
}

EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    SCREEN_WIDTH = uiEvent->windowInnerWidth;
    SCREEN_HEIGHT = uiEvent->windowInnerHeight;

    SCREEN_CENTER_X = (double) SCREEN_WIDTH / 2.0;
    SCREEN_CENTER_Y = (double) SCREEN_HEIGHT / 2.0;

    emscripten_set_canvas_element_size("#canvas", SCREEN_WIDTH, SCREEN_HEIGHT);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    return true;
}