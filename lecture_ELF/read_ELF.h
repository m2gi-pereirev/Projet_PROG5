#ifndef __READ_HEADER_ELF_H__
#define __READ_HEADER_ELF_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>
#include <getopt.h>
#include <assert.h>

#include "endianess.h"
#include "display.h"

typedef struct execution_options
{
  int nb_files;
  bool all; // display all the section
  bool header; // display only the header file
  bool section_headers; // display only section headers
  bool big_endian_file;
} Exec_options;

/**
 * @brief Read the current file and fill the header's structure
 * @param ehdr structure of header for 32-bit architecture
 */
void header_read(Elf32_Ehdr *ehdr, FILE *filename);

/**
 * @brief Read the current file and fill the section's structure
 *
 * @param shdr structure of section for 32-bit architecture
 */
// void section_read(Elf32_Ehdr *ehdr , Elf32_Shdr *shdr);

void section_read(Elf32_Shdr *shdr);

#endif