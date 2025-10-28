#include "Easings.h"
#include <math.h>

double linear(double t)
{
    return t;
}

double instant(double t)
{
    return 1;
}

double inExpo(double t)
{
    return t == 0 ? 0 : pow(2, 10 * t - 10);
}

double outExpo(double t)
{
    return t == 1 ? 1 : 1 - pow(2, -10 * t );
}

double inOutExpo(double t)
{
    return t == 0 ? 0 : t == 1 ? 1 : t < 0.5 ? pow(2, 20 * t - 10) / 2 : (2 - pow(2, -20 * t + 10)) / 2;
}