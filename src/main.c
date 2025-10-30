#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "Easings.h"
#include "Color.h"

#define ELEMENT_AUTO_INIT

#include "Element.h"

unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;

Element myElement;

void loop()
{
    double v = (double)((int) emscripten_get_now() % 1000) / 1000.0;
    myElement.style.position.x = SCREEN_CENTER_X;
    myElement.style.position.y = SCREEN_CENTER_Y;
    myElement.style.rotation.z = inOutExpo(v) * 360;
    ElementApplyChanges(&myElement);
}


EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    SCREEN_WIDTH = uiEvent->windowInnerWidth;
    SCREEN_HEIGHT = uiEvent->windowInnerHeight;

    SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    return false;
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
    // stuff below here does the rest of the work.


    ElementPush(&myElement);
    myElement.id = "niko";
    myElement.style.scale.x = 1;
    myElement.style.scale.y = 1;


    emscripten_set_main_loop(loop, -1, true);
    
    return 0;
}
