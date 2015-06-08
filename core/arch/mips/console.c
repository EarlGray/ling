#include <stdbool.h>

#include "ling_common.h"
#include "outlet.h"

static struct {
    bool is_initialized;
    outlet_t *attached_outlet;
} the_console = {
    .is_initialized = false,
    .attached_outlet = 0,
};

void console_init()
{
    DBINIT();
    the_console.is_initialized = true;
}

int console_is_initialized(void) {
    return (int)the_console.is_initialized;
}

int console_write(char *buf, int len) {
    printk(buf);
}

int console_do_pending(void) {
    return 0;
}

void console_attach(outlet_t *ol) {
	if (the_console.attached_outlet != 0)
		printk("%ptWARNING: steals control over console from %pt\n",
				T(ol->oid), T(the_console.attached_outlet->oid));
	the_console.attached_outlet = ol;
}

void console_detach(outlet_t *ol) {
	assert(the_console.attached_outlet == ol);
	the_console.attached_outlet = 0;
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
