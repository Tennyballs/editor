#ifndef EASINGS_H
#define EASINGS_H

static struct Easings
{
    double (*instant)(double t);
    double (*inExpo)(double t);
    double (*outExpo)(double t);
    double (*inOutExpo)(double t);
} Easings;

double instant(double t);
double inExpo(double t);
double outExpo(double t);
double inOutExpo(double t);

#endif // EASINGS_H