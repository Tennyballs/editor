#include <stdio.h>
#include <math.h>

#include "Easings.h"
#include "Color.h"
#include "Properties.h"
#include "Tween.h"

Properties props = {"canvas"};

void loop()
{
    tweens_update();
}

unsigned int SCREEN_WIDTH, SCREEN_HEIGHT;
double SCREEN_CENTER_X, SCREEN_CENTER_Y;

void meow(double value)
{
    props.size.width = value * SCREEN_WIDTH;
    set(&props);
}

int main()
{


    double width, height;

    emscripten_get_element_css_size("body", &width, &height);

    SCREEN_WIDTH = (unsigned int)width;
    SCREEN_HEIGHT = (unsigned int)height;

    SCREEN_CENTER_X = width / 2;
    SCREEN_CENTER_Y = height / 2;

    props.border.width = 10;
    props.border.color.value = 0xFFFFFFFF;

    //
    props.color.backgroundColor.value = 0xFF0000FF;
    
    props.position.x = SCREEN_CENTER_X;
    props.position.y = SCREEN_CENTER_Y;

    props.size.height = SCREEN_HEIGHT;
    props.size.height = SCREEN_HEIGHT;

    unsigned long time = getTime();
    
    Tween meowT;

    meowT.func = &meow;
    meowT.ease = &outExpo;
    
    meowT.value_begin = 0;
    meowT.value_end = 1;

    meowT.time_start = getTime() + 1000;
    meowT.time_end = meowT.time_start + 5000;

    tweens_push(&meowT);


    emscripten_set_main_loop(loop, -1, true);
    
    return 0;
}
