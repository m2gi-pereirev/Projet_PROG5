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
#include "core.h"

typedef struct execution_options
{
  int nb_files; // nb_files passed in arguments
  bool header; // display only the header file
  bool section_headers; // display only section headers
  bool big_endian_file; // true if file is in big_endian
  bool symb;
} Exec_options;


/**
 * @brief Read the current file and fill the header's structure
 * @param ehdr structure of header for 32-bit architecture
 */
void header_read(Elf32_Ehdr *ehdr, FILE *filename);

/**
 * @brief
 *
 * @param exec_op
 * @param filename
 * @param ehdr
 * @return Elf32_Shdr*
 */
void section_headers_read(Exec_options *exec_op, FILE *filename, Elf32_Ehdr *ehdr, Elf32_Shdr_named *shdr_named);



void symbole_table_elf (Exec_options *exec_op, FILE *filename, Elf32_Ehdr *ehdr, Elf32_Shdr_named *shdr_named, Elf32_Sym_named *sym_named);

#endif