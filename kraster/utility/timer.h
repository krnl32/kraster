#ifndef KRASTER_TIMER_H
#define KRASTER_TIMER_H

#include <stdint.h>

uint64_t kraster_timer_now_ns(void);
uint64_t kraster_timer_now_ms(void);
double kraster_timer_now_sec(void);

#endif
