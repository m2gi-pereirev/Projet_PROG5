#ifndef __SAVING_H__
#define __SAVING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "endianess.h"
#include "section_manipulator.h"

/**
 * @brief Opened the file for output with the filename parametre
 *
 * @param filename Name of the output file
 * @return FILE* poiter to opened file
 */
FILE *load_elf_output(char *filename);

/**
 * @brief
 *
 * @param file
 * @param ehdr
 * @param big_endian
 */
void write_file_header(FILE *file, Elf32_Ehdr *ehdr, bool big_endian);

void write_sections(FILE *file, Elf32_stct_list sections_array);

void write_section_headers(FILE *file, Elf32_Shdr_named *shdrn, bool big_endian);

void write_sections_names(FILE *file, Elf32_stct_list sections_array);

void write_symbols(FILE *file, Elf32_Sym_named *symn, Elf32_Shdr_named *shdrn, int shnum, bool big_endian);

void write_elf_content(Elf32_file *elf, FILE *file);

#endif