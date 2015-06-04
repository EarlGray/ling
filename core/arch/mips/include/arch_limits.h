#ifndef __LING_MIPS_ARCH_LIMITS_H__
#define __LING_MIPS_ARCH_LIMITS_H__

// it's a bad, bad idea to name a header "limits.h"
#define USHRT_MAX (unsigned short)((1u << (CHAR_BIT * sizeof(unsigned short))) - 1)
#define UCHAR_MAX (unsigned char) ((1u << (CHAR_BIT * sizeof(unsigned char ))) - 1)
#define UINT_MAX  (unsigned int)  (~ 0u)

#ifdef __PAGE_SHIFT
# undef __PAGE_SHIFT
#endif
#ifdef __PAGE_SIZE
# undef __PAGE_SIZE
#endif

#define __PAGE_SHIFT 12
#define __PAGE_SIZE  (1 << __PAGE_SHIFT)

#endif // __LING_MIPS_ARCH_LIMITS_H__
