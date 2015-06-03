#include "ling_common.h"
#include "mm.h"

#define GC_RESERVE (8 * 1024)

extern char _heap, _eheap;

static char *free_page;
static char *endofheap = &_eheap;

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
	printk("mm_alloc_pages(%d) -> *%08x: %d pages left, free_page=*%08x\n",
	       nr_pages, allocated, mm_alloc_left(), (uintptr_t)free_page);
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

