#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <time.h>
#include <signal.h>

#define ONE_SEC 1000000000

void
start_timer(uint_fast64_t interval_nano, uint_fast64_t value_nano);

void
stop_timer(void);

void
timer_set_cb(void(*time_cb)(int));

int
get_time(void);

#endif
