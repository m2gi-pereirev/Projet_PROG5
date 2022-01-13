#ifndef __REORGANIZATION_H__
#define __REORGANIZATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "utils.h"
#include "section_manipulator.h"
#include "freed.h"

void elf_reorganization(Elf32_file *elf);

void shdr_rel_entry_delete(Elf32_Shdr_named *shdrn);

#endif