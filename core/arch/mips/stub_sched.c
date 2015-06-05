/* fake it until you make it */

#include <stdlib.h>
#include "term.h"
#include "proc.h"
#include "hash.h"

hash_t *registry;

proc_t *scheduler_next(proc_t *current, int reds_left) {
	return current;
}

void scheduler_runtime_start(void) {
	printk("scheduler_runtime_start() called, TODO\n");
}

uint64_t scheduler_runtime_get(void) {
    printk("scheduler_runtime_get() called, TODO\n");
    return 0;
}

proc_t *scheduler_lookup(term_t pid)
{
	printk("scheduler_lookup() called, TODO\n");
	return NULL;
}

int scheduler_new_local_mail_N(proc_t *proc, term_t msg) {
	printk("scheduler_new_local_mail_N() called, TODO\n");
	return -1;
}

proc_t *scheduler_process_by_name(term_t name) {
	printk("scheduler_process_by_name() called, TODO\n");
	return NULL;
}

int scheduler_run_queue(void) {
	printk("scheduler_run_queue() called, TOOD\n");
}

term_t scheduler_list_processes(heap_t *hp) {
	printk("scheduler_list_processes() called, TODO\n");
	return nil;
}

term_t scheduler_list_registered(heap_t *hp) {
    printk("scheduler_list_registered() called, TODO\n");
    return nil;
}

void scheduler_add_purged(proc_t *proc) {
    printk("scheduler_add_purged() called, TODO\n");
}

void scheduler_register(proc_t *proc, term_t name) {
    printk("scheduler_register() called, TOOD\n");
}

void scheduler_unregister(proc_t *proc) {
    printk("scheduler_unregister() called, TODO\n");
}

int scheduler_signal_exit_N(proc_t *proc, term_t source, term_t reason) {
    printk("scheduler_signal_exit_N() called, TODO\n");
}

int scheduler_enlist_N(proc_t *spawning) {
    printk("scheduler_enlist_N() called, TODO\n");
}
