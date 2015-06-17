#include "ling_common.h"

void domain_poweroff(void) {
    printk("domain_poweroff()\n");
    while (1) {
        asm volatile ("WAIT");
    }
}
