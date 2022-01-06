#ifndef __DISPLAY_RELOCATION_H__
#define __DISPLAY_RELOCATION_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

#include "core.h"

void print_relocation_section(Elf32_Rel *rel_section, Elf32_Shdr *shdr, char *shdr_name);

#endif