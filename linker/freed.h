#ifndef __FREED_H__
#define __FREED_H__

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "section_manipulator.h"

/**
 * @brief free pointer to avoid leaks of memory
 *
 * @param *elf pointer to the elf32_file structure
 */
void free_elf32_file(Elf32_file *elf);

#endif