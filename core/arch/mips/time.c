#include "ling_common.h"
#include "time.h"

uint64_t start_of_day_wall_clock = 0;

void time_init(void) {}

#warning "TODO: time.h"
uint64_t monotonic_clock(void) {
    printf("TODO: monotonic_clock()");
    return 0;
}

uint64_t wall_clock(void) {
    printf("TODO: wall_clock()");
    return 0;
}

void expand_time(struct time_exp_t *xt, uint64_t wall_clock) {
    memset(xt, 0, sizeof(*xt));
    xt->tm_year = 115;
    xt->tm_mon = 1;
    xt->tm_mday = 17;
    xt->tm_wday = 2;
}

