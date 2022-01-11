#ifndef __SECTION_GENERATOR_H__
#define __SECTION_GENERATOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


Elf32_stct_item *section_container_summoner(int size, int idx, char *name, char *content);

void section_container_destroyer(Elf32_stct_item *container);

void sections_list_destroyer(Elf32_stct_item *cargo);

void section_containers_display(Elf32_stct_item *cargo);

Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int idx, int size);

#endif