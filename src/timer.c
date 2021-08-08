#include "timer.h"

timer_t Timer;

void
start_timer(uint_fast64_t interval_nano, uint_fast64_t value_nano)
{
    struct itimerspec value;
    value.it_value.tv_sec = interval_nano;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 1;
    value.it_interval.tv_nsec = 0;

    timer_create (CLOCK_REALTIME, NULL, &Timer);

    timer_settime (Timer, 0, &value, NULL);
}

void
stop_timer(void)
{
    struct itimerspec value;

    value.it_value.tv_sec = 0;
    value.it_value.tv_nsec = 0;

    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_settime (Timer, 0, &value, NULL);
}

int
get_time(void) 
{
    time_t t1;
    struct tm *a;
    unsigned int current_time = 0;

    t1 = time(NULL);
    a = localtime(&t1);
    current_time = a->tm_min + (a->tm_hour * 100);

    return current_time;
}

void
timer_set_cb(void(*time_cb)(int))
{
    (void) signal(SIGALRM, time_cb);
}
