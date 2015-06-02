#include "ling_common.h"
#include "mm.h"

#define GC_RESERVE (16 * 1024)

#define PIC32MX_KSEG0  0x80000000
#define MEMORY_END     (PIC32MX_KSEG0 - BMXDRMSZ)

static void *free_page = PIC32MX_KSEG0;

void mm_init(void)
{
}

void *mm_alloc_pages(int nr_pages)
{
	if (((uintptr_t)free_page + nr_pages * PAGE_SIZE) > (MEMORY_END - GC_RESERVE))
		return 0;
	void *allocated = free_page;
	free_page += nr_pages * PAGE_SIZE;
	return allocated;
}

int mm_alloc_left(void)
{
	return (MEMORY_END - (uintptr_t)free_page) / PAGE_SIZE;
}

void *mm_alloc_tmp(void)
{
	return free_page;
}

