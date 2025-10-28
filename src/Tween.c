#include "Tween.h"
#include <sys/time.h>
#include <stdio.h>


Tween *tweens[0xFF];

void tweens_push(Tween *tween)
{
    static int index = 0;
    tweens[index++] = tween;
}

unsigned long getTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long ret = tv.tv_usec;
    ret /= 1000;
    ret += (tv.tv_sec * 1000);
    return ret;
}

void tweens_update()
{
    long time = getTime();
    for (size_t i = 0; i < 0xFF; i++)
    {
        Tween *tween = tweens[i];

        if(tween->time_start >= time){
            continue;
        }

        if(tween->time_end <= time)
        {
            if(!tween->finished && tween->func)
            {
                tween->finished = 1;
                tween->func(tween->value_end);
            }
            continue;
        }
        
        double iTime = (double) ((time - tween->time_start) / 1000.0) / ((double) (tween->time_end - tween->time_start) / 1000.0);
        double iValue = 0;

        
        if(tween->ease && tween->func)
        {
            tween->func(tween->ease(iTime) * (tween->value_end - tween->value_begin) + tween->value_begin);
        }
    }
    
}