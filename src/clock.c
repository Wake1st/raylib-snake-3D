#include "clock.h"

Clock InitClock(float start)
{
  return (Clock){
      .rate = start,
      .age = 0.f,
  };
}

bool TickClock(Clock *clock)
{
  clock->age += GetFrameTime();

  if (clock->age >= clock->rate)
  {
    clock->age -= clock->rate;
    return true;
  }
  else
  {
    return false;
  }
}

void DecreaseClockRate(Clock *clock)
{
  clock->rate *= 0.9f;
}

void SetClockRate(Clock *clock, float rate)
{
  clock->rate = rate;
}
