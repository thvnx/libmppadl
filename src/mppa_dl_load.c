/**
 * Copyright (C) 2018 Kalray SA.
 */

#include "mppa_dl_load.h"

size_t mppa_dl_load_segments_memsz(mppa_dl_handle_t *hdl)
{
	size_t memsz = 0;
	int i;
	GElf_Phdr phdr;

	/* iterate program headers, in descending order, then compute the
	   required memory size to load segments */
	for (i = (int)hdl->phdrnum - 1; i >= 0; i--) {
		if (gelf_getphdr(hdl->elf_desc, i, &phdr) == NULL) {
			mppa_dl_errno(E_ELF_PHDR);
			return memsz;
		}

		if (phdr.p_type == PT_LOAD) {
			memsz = phdr.p_vaddr + phdr.p_memsz;
			i = -1;
		}
	}

	return memsz;
}

size_t mppa_dl_load_segments_align(mppa_dl_handle_t *hdl)
{
	size_t malign = 0;
	int i;
	GElf_Phdr phdr;

	/* iterate program headers, in ascending order, then compute the
	   maximum alignement required to load segments */
	for (i = 0; i < (int)hdl->phdrnum; i++) {
		if (gelf_getphdr(hdl->elf_desc, i, &phdr) == NULL) {
			mppa_dl_errno(E_ELF_PHDR);
			return malign;
		}

		if (phdr.p_type == PT_LOAD)
			malign = malign >= phdr.p_align ? malign : phdr.p_align;
	}

	return malign;
}