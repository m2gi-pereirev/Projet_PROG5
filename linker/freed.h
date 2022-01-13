#ifndef __FREED_H__
#define __FREED_H__

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "section_manipulator.h"

void free_elf32_reln(Elf32_Rel_named *reln, int nb_rel);

void free_elf32_file(Elf32_file *elf);

#endif