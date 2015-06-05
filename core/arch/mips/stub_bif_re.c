#include "term.h"
#include "proc.h"
#include "bif_impl.h"

void pcre_init(void) {
	printk("pcre_init() : fake stub called\n");
}

term_t cbif_re_compile1(proc_t *proc, term_t *regs) {
	bif_not_implemented();
}

term_t cbif_re_compile2(proc_t *proc, term_t *regs) {
	bif_not_implemented();
}

term_t cbif_re_run2(proc_t *proc, term_t *regs) {
	bif_not_implemented();
}

term_t cbif_re_run3(proc_t *proc, term_t *regs) {
	bif_not_implemented();
}
