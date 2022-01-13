#ifndef __SECTION_GENERATOR_H__
#define __SECTION_GENERATOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

Elf32_stct_item *section_container_summoner(int size, char *name, char *content, bool symtab, bool rel, bool strtab, uint32_t offset, uint32_t align, int idx);

void section_container_destroyer(Elf32_stct_item *container);

void sections_list_destroyer(Elf32_stct_item *cargo);

void section_containers_display(Elf32_stct_item *cargo);

Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int size, bool symtab, bool rel, bool strtab, uint32_t offset, uint32_t align, int idx);

Elf32_stct_list swap_section(Elf32_stct_item *cargo, uint32_t off1, uint32_t off2);

Elf32_stct_item *finder(Elf32_stct_list cargo, uint32_t offset);

Elf32_stct_item *symtab_finder(Elf32_stct_list cargo);

Elf32_stct_item *finder_realoc(Elf32_stct_list cargo, int idx);

Elf32_stct_list remove_section(Elf32_stct_list cargo, uint32_t offset);

void section_containers_display(Elf32_stct_item *cargo);

Elf32_stct_list section_offset_remappage(Elf32_stct_list cargo, uint16_t header_size);

Elf32_stct_list reindex(Elf32_stct_list cargo);

Elf32_stct_item *last_finder(Elf32_stct_list cargo);

#endif