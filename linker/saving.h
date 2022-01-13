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
 * @brief Write the header of the elf in the file
 *
 * @param file pointer to the file opened in write binary mode
 * @param ehdr pointer to the file header informations
 * @param big_endian if the file is a big endian file
 */
void write_file_header(FILE *file, Elf32_Ehdr *ehdr, bool big_endian);

/**
 * @brief Write the sections in the file
 *
 * @param file pointer to the file opened in write binary mode
 * @param sections_array pointer to the head of the chained list of sections
 */
void write_sections(FILE *file, Elf32_stct_list sections_array);

/**
 * @brief Write the section headers in the file, except the name sections
 *
 * @param file pointer to the file opened in write binary mode
 * @param shdrn pointer to the section headers informations
 * @param big_endian if the file is in big endian
 */
void write_section_headers(FILE *file, Elf32_Shdr_named *shdrn, bool big_endian);

/**
 * @brief Write the name sections in the file
 *
 * @param file pointer to the file opened in write binary mode
 * @param sections_array pointer to the head of the chained list of section
 */
void write_sections_names(FILE *file, Elf32_stct_list sections_array);

/**
 * @brief Write the symbols table in the file
 *
 * @param file pointer to the file opened in write binary mode
 * @param symn pointer to symbols table informations
 * @param shdrn pointer to sections headers informations
 * @param shnum number of entries in section headers
 * @param big_endian is the elf file is in big endian or not
 */
void write_symbols(FILE *file, Elf32_Sym_named *symn, Elf32_Shdr_named *shdrn, int shnum, bool big_endian);

/**
 * @brief Write all the elf informations in the opened file
 *
 * @param elf pointer to the elf informations
 * @param file pointer to file (already opened)
 */
void write_elf_content(Elf32_file *elf, FILE *file);

#endif