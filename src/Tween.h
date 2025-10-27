#ifndef TWEEN_H
#define TWEEN_H

typedef struct Tween
{
    unsigned long time_start;
    unsigned long time_end;

    double value_begin;
    double value_end;
    void (*func)(double value);
    double (*ease)(double t);
    char finished;

    double *property;
} Tween;

unsigned long getTime();

// void tween_to_string();
void tweens_push(Tween *tween);
void tweens_update();
void tweens_purge();


#endif // TWEEN_H