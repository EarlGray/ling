#ifndef __LING_CORE_MIPS_OS_H__
#define __LING_CORE_MIPS_OS_H__

#define _DISABLE_OPENADC10_CONFIGPORT_WARNING (1)
#define _SUPPRESS_PLIB_WARNING

#define PIC32_STARTER_KIT (1)
#ifdef __XC32
#include <xc.h>
#endif

#include <plib.h>
 
#define QUICK_SIZE 4096

#define isfinite(val) (!isinf((double)val))

#endif //__LING_CORE_MIPS_OS_H__
