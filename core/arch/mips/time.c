#include "ling_common.h"
#include "time.h"

uint64_t start_of_day_wall_clock = 0;

uint64_t fake_clock = 1234567890;

void time_init(void) {}

#warning "TODO: time.h"
uint64_t monotonic_clock(void) {
	fake_clock += 1000000;
    return fake_clock;
}

uint64_t wall_clock(void) {
	fake_clock += 1000000;
    return fake_clock;
}

void expand_time(struct time_exp_t *xt, uint64_t wall_clock) {
    memset(xt, 0, sizeof(*xt));
    xt->tm_year = 115;
    xt->tm_mon = 1;
    xt->tm_mday = 17;
    xt->tm_wday = 2;
}

