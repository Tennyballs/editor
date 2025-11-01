#include <stdio.h>
#include <math.h>
#include <stdbool.h>


#include <emscripten/html5_webgl.h>

// GL
#define GLFW_INCLUDE_ES3
#include <GL/glfw.h>
#include "Image.h"
#include "Helper.h"
#include "Object.h"
#include "Arrays.h"



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
    GLuint shaderProgram;
    EmscriptenWebGLContextAttributes attrs;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE handle;
} MainData;

Object myObject;

void loop()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    object_draw(&myObject);
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

    Image *img = load_image("/texture/Niko.png");

    MainData.shaderProgram = helper_basic_shader_program_setup();
    glUseProgram(MainData.shaderProgram);

    GLuint niko = helper_gen_texture(img);
    float positions[] = {
        -1.0f,  -1.0f,  0.0f,
        1.0f,   -1.0f,  0.0f,
        -1.0f,  1.0f,   0.0f,
        1.0f,   1.0f,   0.0f
    };

    float uvs[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };

    myObject = object_create_from_points(positions, uvs, 4);
    myObject.textureID = niko;



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    emscripten_set_main_loop(loop, -1, true);
    return 0;
}
