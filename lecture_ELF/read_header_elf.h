#ifndef __READ_HEADER_ELF_H__
#define __READ_HEADER_ELF_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "bfile.h"

/**
 * @brief Read the current file and fill the header's structure
 *
 * @param ehdr structure of header for 32-bit architecture
 */
void header_read(Elf32_Ehdr *ehdr);

/**
 * @brief Check if the magic number is ELF
 *
 * @param ehdr structure
 * @return true if the magic number corresponds to ELF
 * @return false if the magic number didn't corresponds to ELF
 */
bool is_magic_number(Elf32_Ehdr *ehdr);

#endif