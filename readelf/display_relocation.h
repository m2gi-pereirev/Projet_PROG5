#ifndef __DISPLAY_RELOCATION_H__
#define __DISPLAY_RELOCATION_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <byteswap.h>
#include <inttypes.h>

#include "utils.h"

void print_relocation_section(Elf32_Rel_named *rel_named, Elf32_Off offset, char *rel_name);

#endif