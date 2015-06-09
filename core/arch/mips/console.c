#include <stdbool.h>
#include <string.h>

#include "ling_common.h"
#include "outlet.h"

#define RINGBUFSZ 2048
struct {
    unsigned start;
    char buf[RINGBUFSZ];
} ringbuf = {
    .start = 0,
};

void ringbuf_append(const char *buf, size_t len) {
    if (ringbuf.start == RINGBUFSZ)
        ringbuf.start = 0;
    if ((ringbuf.start + len) <= RINGBUFSZ) {
        memcpy(ringbuf.buf + ringbuf.start, buf, len);
        ringbuf.start += len;
    } else {
        size_t chunk_len = RINGBUFSZ - ringbuf.start;

        memcpy(ringbuf.buf + ringbuf.start, buf, chunk_len);
        ringbuf.start = 0;

        ringbuf_append(buf + chunk_len, len - chunk_len);
    }
}


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
    ringbuf_append(buf, len);
#if defined(__ENABLEIO_STARTERKIT_DEBUG)
    //db_puts(buf, len);
#else
# warning "No ser_cons_write! printk() is disabled"
#endif
    return 0;
}
