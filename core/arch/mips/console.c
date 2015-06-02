
#include "ling_common.h"

void console_init()
{
    DBINIT();
}

int ser_cons_write(char *buf, int len)
{
#if defined(__ENABLEIO_STARTERKIT_DEBUG)
    db_puts(buf, len);
#else
# error "no __ENABLEIO_STARTERKIT_DEBUG"
#endif
    return 0;
}
