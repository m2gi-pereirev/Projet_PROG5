#ifndef __RELOCATIONS_H__
#define __RELOCATIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "section_manipulator.h"
#include "freed.h"
#include "reorganization.h"

/**
 * @brief Return the index of the relocation section headers
 *
 * @param shdrn pointer to the sections headers table structure
 * @param offset
 * @return int index of the section
 */
int rel_link_section_finder(Elf32_Shdr_named *shdrn, int *offset);

/**
 * @brief Execute the relocation
 *
 * @param elf poiter to the file structure
 */
void relocations_execution(Elf32_file *elf);

#endif