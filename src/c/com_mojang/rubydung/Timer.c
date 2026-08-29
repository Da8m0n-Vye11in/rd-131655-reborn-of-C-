#include "com_mojang/rubydung/Timer.h"
#include <time.h>

void Timer_init(Timer* t, int targetFps) {
    (void)targetFps;
    t->ticks = 0; t->partialTicks = 0.0f;
}

void Timer_advance(Timer* t) { (void)t; }
