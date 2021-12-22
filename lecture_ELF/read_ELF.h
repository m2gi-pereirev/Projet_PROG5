#ifndef __READ_HEADER_ELF_H__
#define __READ_HEADER_ELF_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "bfile.h"
#include "display_header.h"
#include "display_section.h"

/**
 * @brief Read the current file and fill the header's structure
 * @param ehdr structure of header for 32-bit architecture
 */
void header_read(Elf32_Ehdr *ehdr);

/**
 * @brief Read the current file and fill the section's structure
 *
 * @param shdr structure of section for 32-bit architecture
 */
void section_read(Elf32_Ehdr *ehdr , Elf32_Shdr *shdr);

#endif