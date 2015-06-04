#include <stdbool.h>

#include "ling_common.h"

static struct {
    bool is_initialized;
} the_console = {
    .is_initialized = false
};

void console_init()
{
    DBINIT();
    the_console.is_initialized = true;
}

int console_is_initialized(void) {
    return (int)the_console.is_initialized;
}

int ser_cons_write(char *buf, int len)
{
#if defined(__ENABLEIO_STARTERKIT_DEBUG)
    if (!the_console.is_initialized) return -1;
    db_puts(buf, len);
#else
# warning "No ser_cons_write! printk() is disabled"
#endif
    return 0;
}
