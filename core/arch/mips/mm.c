#include "ling_common.h"
#include "mm.h"

#define GC_RESERVE (16 * 1024)

#define PIC32MX_KSEG0  0xa0000000

extern char _heap, _eheap;

static void *free_page;
static void *endofheap = &_eheap;

#define MEMORY_END ((uintptr_t)endofheap)

void mm_init(void)
{
    uintptr_t heapstart = (uintptr_t)&_heap;
    free_page = (void *)(heapstart + (PAGE_SIZE - 1) & ~(PAGE_SIZE - 1));
    printk("mm_init: heap: [0x%08x : 0x%08x]\n",
            (uintptr_t)free_page, (uintptr_t)endofheap);
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

