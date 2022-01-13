#ifndef __LOADING_H__
#define __LOADING_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "utils.h"
#include "endianess.h"
#include "section_manipulator.h"
#include "freed.h"

/**
 * @brief Open binary file for reading
 *
 * @param filename file to open
 */
char *load_file_content(char *filename);

void storage_elf_content(char *content, Elf32_file *elf);

#endif