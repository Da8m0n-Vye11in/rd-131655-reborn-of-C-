#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Timer {
    int ticks;
    float partialTicks;
} Timer;

void Timer_init(Timer* t, int targetFps);
void Timer_advance(Timer* t);

#ifdef __cplusplus
}
#endif

#endif // TIMER_H
