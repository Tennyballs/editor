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

    /* Linux */
    struct timeval tv;

    gettimeofday(&tv, NULL);

    unsigned long ret = tv.tv_usec;
    /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
    ret /= 1000;

    /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
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
        
        // get the current time
        // double = cTime * ((cTime - timeStart) / (timeEnd - timeStart))

        double iTime = (double) ((time - tween->time_start) / 1000.0) / ((double) (tween->time_end - tween->time_start) / 1000.0);
        double iValue = 0;

        
        if(tween->ease)
        {
            iValue = tween->ease(iTime) * ((tween->value_end - tween->value_begin) + tween->value_begin);
        } else {
            iValue = iTime * (tween->value_end - tween->value_begin) + tween->value_begin;
        }


        if(tween->func)
        {
            tween->func(iValue);
            return;
        }
        printf("No function attached to tween, please read this :sobbing:...\n");
    }
    
}

// void tween_to_string(Tween *tween)
// {
//     printf("Tween{\n\tcurrentTime=%ld\n\tstartTime=%ld\n\tendTime=%ld\n\tcurrentValue=%f\n\tstartValue=%f\n\tendValue=%f\n}\n",tween->time_current, tween->time_start, tween->time_end, tween->value_current, tween->value_begin, tween->value_end);
// }

void tweens_purge()
{
    long time = getTime();
    int count = 0;
    long long int freespace = 0;
    long index = 0;
    for (size_t i = 0; i < 0xFF; i++)
    {
        Tween *tween = tweens[i];

        if(!tween || tween->time_end < time)
        {
            freespace |= (1 << index++);
        } else {
            count++;
        }
    }
}