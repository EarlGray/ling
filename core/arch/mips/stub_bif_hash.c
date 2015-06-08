#include "hash.h"
#include "bif_impl.h"
#include "proc.h"

term_t cbif_md5_1(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_md5_update2(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_md5_init0(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_md5_final1(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_md5_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }

term_t cbif_sha1(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha_init0(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha_update2(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha_final1(proc_t *proc, term_t *regs) { bif_not_implemented(); }

term_t cbif_sha224_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha256_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha384_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }
term_t cbif_sha512_mac_n3(proc_t *proc, term_t *regs) { bif_not_implemented(); }

term_t cbif_aes_cbc_crypt4(proc_t *proc, term_t *regs) { bif_not_implemented(); }

term_t cbif_exor2(proc_t *proc, term_t *regs)
{
	int i;
	term_t Bin1 = regs[0];
	term_t Bin2 = regs[1];

	if (!is_list(Bin1) && !is_boxed_binary(Bin1))
		badarg(Bin1);
	if (!is_list(Bin2) && !is_boxed_binary(Bin2))
		badarg(Bin2);

	int sz1 = iolist_size(Bin1);
	if (sz1 < 0)
		badarg(Bin1);
	int sz2 = iolist_size(Bin2);
	if (sz2 != sz1)
		badarg(Bin2);
	assert(sz1 <= 65536);	//TODO: use heap_tmp_buf for larger binaries
	uint8_t data1[sz1];
	iolist_flatten(Bin1, data1);
	uint8_t data2[sz2];
	iolist_flatten(Bin2, data2);

	uint8_t *data3;
	term_t result = heap_make_bin(&proc->hp, sz1, &data3);
	for (i = 0; i < sz1; i++)
		data3[i] = data1[i] ^ data2[i];

	return result;
}

term_t cbif_rand_bytes1(proc_t *proc, term_t *regs)
{
	term_t N = regs[0];
	if (!is_int(N) || int_value(N) < 0)
		badarg(N);
	int len = int_value(N);

	uint8_t *ptr;
	term_t bin = heap_make_bin(&proc->hp, len, &ptr);
	uint8_t *p = ptr;
	while (p <= ptr +len -4)
	{
		uint32_t rnd = mt_lrand();
		PUT_UINT_32(p, rnd);
		p += 4;
	}
	uint32_t last = mt_lrand();
	switch(ptr +len -p)
	{
	case 3:
		*p++ = (uint8_t)(last >> 16);
	case 2:
		*p++ = (uint8_t)(last >> 8);
	case 1:
		*p++ = (uint8_t)last;
	case 0:
		break;
	}

	return bin;
}

