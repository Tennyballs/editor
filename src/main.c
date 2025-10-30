#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;


EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    SCREEN_WIDTH = uiEvent->windowInnerWidth;
    SCREEN_HEIGHT = uiEvent->windowInnerHeight;

    SCREEN_CENTER_X = (double) SCREEN_WIDTH / 2.0;
    SCREEN_CENTER_Y = (double) SCREEN_HEIGHT / 2.0;

    emscripten_set_canvas_element_size("canvas", SCREEN_WIDTH, SCREEN_HEIGHT);

    return false;
}

void loop()
{

}

int main()
{
    double width, height;

    emscripten_get_element_css_size("body", &width, &height);


    SCREEN_WIDTH = (unsigned int)width;
    SCREEN_HEIGHT = (unsigned int)height;

    SCREEN_CENTER_X = width / 2;
    SCREEN_CENTER_Y = height / 2;

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, NULL, true, resizeCallback);
    emscripten_set_canvas_element_size("canvas", SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // stuff below here does the rest of the work.


    emscripten_set_main_loop(loop, -1, true);
    return 0;
}
