#ifndef __LING_MIPS_ARCH_LIMITS_H__
#define __LING_MIPS_ARCH_LIMITS_H__

#ifdef __PAGE_SHIFT
# undef __PAGE_SHIFT
#endif
#ifdef __PAGE_SIZE
# undef __PAGE_SIZE
#endif

#define __PAGE_SHIFT 12
#define __PAGE_SIZE  (1 << __PAGE_SHIFT)

#endif // __LING_MIPS_ARCH_LIMITS_H__
