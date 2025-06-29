#ifndef CLOCK_H
#define CLOCK_H

#include "raylib.h"

typedef struct Clock
{
  float rate;
  float age;
} Clock;

Clock InitClock(float start);
bool TickClock(Clock *clock);
void DecreaseClockRate(Clock *clock);
void SetClockRate(Clock *clock, float rate);

#endif
