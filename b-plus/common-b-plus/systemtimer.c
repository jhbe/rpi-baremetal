#include "systemtimer.h"

#define SYSTEMTIMER_BASE    0x20003000UL

typedef struct {
	volatile uint32_t cs;
	volatile uint32_t clo;
	volatile uint32_t clh;
	volatile uint32_t c0;
	volatile uint32_t c1;
	volatile uint32_t c2;
	volatile uint32_t c3;
} SYSTEMTIMER;
SYSTEMTIMER *st = (SYSTEMTIMER *)SYSTEMTIMER_BASE;

uint64_t systemtimer_get(void) {
	return ((uint64_t)st->clh << 32) | (uint64_t)st->clo;
}
