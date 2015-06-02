#ifndef __LING_CORE_MIPS_OS_H__
#define __LING_CORE_MIPS_OS_H__

#define PIC32_STARTER_KIT (1)
#ifdef __XC32
#include <xc.h>
#endif

#define _DISABLE_OPENADC10_CONFIG_WARNING

#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
 
#define QUICK_SIZE 4096

#endif //__LING_CORE_MIPS_OS_H__
