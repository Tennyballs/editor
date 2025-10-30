#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "Easings.h"
#include "Color.h"

// #define ELEMENT_AUTO_INIT

#include "Element.h"

unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;
Element cube;


EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    SCREEN_WIDTH = uiEvent->windowInnerWidth;
    SCREEN_HEIGHT = uiEvent->windowInnerHeight;

    SCREEN_CENTER_X = SCREEN_WIDTH / 2.0;
    SCREEN_CENTER_Y = SCREEN_HEIGHT / 2.0;

    return false;
}

void loop()
{
    UpdateAllElements();

    double now = emscripten_get_now() / 500.0;

    cube.transform.rotation.x = now * 15;
    cube.transform.rotation.y = now * 23;
    cube.transform.rotation.z = now * 62;

    cube.transform.position.y = sin(now) * 100.0 - 50;
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
    cube.id = "niko-cube";
    cube.transform.scale.x = 1;
    cube.transform.scale.y = 1;
    cube.transform.position.x = -96/2;
    cube.transform.position.y = -96/2;


    Element front;
    Element back;
    Element left;
    Element right;
    Element top;
    Element bottom;

    front.id = "front";
    back.id = "back";
    left.id = "left";
    right.id = "right";
    top.id = "top";
    bottom.id = "bottom";

    front.transform.scale.x = 1;
    front.transform.scale.y = 1;
    back.transform.scale.x = 1;
    back.transform.scale.y = 1;
    left.transform.scale.x = 1;
    left.transform.scale.y = 1;
    right.transform.scale.x = 1;
    right.transform.scale.y = 1;
    top.transform.scale.x = 1;
    top.transform.scale.y = 1;
    bottom.transform.scale.x = 1;
    bottom.transform.scale.y = 1;

    front.transform.position.z = -96 / 2;
    back.transform.position.z = 96 / 2;

    left.transform.rotation.y = 90;
    left.transform.position.x = 96 / 2;

    right.transform.rotation.y = -90;
    right.transform.position.x = -96 / 2;

    top.transform.rotation.x = -90;
    top.transform.position.y = -96 / 2;

    bottom.transform.rotation.x = 90;
    bottom.transform.position.y = 96 / 2;

    ElementPush(&front);
    ElementPush(&back);
    ElementPush(&left);
    ElementPush(&right);
    ElementPush(&top);
    ElementPush(&bottom);

    ElementPush(&cube);
    emscripten_set_main_loop(loop, -1, true);
    
    return 0;
}
