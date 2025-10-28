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

void meow(double value)
{
    props.position.x = value;
    props.position.y = value;
    props.transform.rotateY = value;
    set(&props);
}

int main()
{
    props.backgroundColor.value = 0xFF00A0FF;
    props.size.width = 128;
    props.size.height = 128;

    unsigned long time = getTime();
    
    Tween meowT;

    meowT.func = &meow;
    meowT.ease = &inOutExpo;
    meowT.value_begin = 0;
    meowT.value_end = 360;
    meowT.time_start = getTime() + 1000;
    meowT.time_end = meowT.time_start + 5000;

    tweens_push(&meowT);



    emscripten_set_interval(&tweens_purge, 1000.000, NULL);
    emscripten_set_main_loop(loop, -1, true);
    
    return 0;
}
