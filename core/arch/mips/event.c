
#include "ling_common.h"

#include "event.h"

int console_do_pending(void);

void events_poll(uint64_t ticks)
{
	//TODO
}

int events_do_pending(void)
{
	//TODO
	return console_do_pending();
}

static unsigned int _excep_code;
static unsigned int _excep_addr;

int _general_exception_handler(void)
{
    asm volatile ("mfc0 %0,$13" : "=r"(_excep_code));
    asm volatile ("mfc0 %0,$14" : "=r"(_excep_addr));    
    
    _excep_code = (_excep_code & 0x0000007C) >> 2;
    
    while (1) {
        
    }
}

int _bev_exception()
{
    while (1);
}
