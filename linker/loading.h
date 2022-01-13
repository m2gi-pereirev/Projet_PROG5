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

/**
 * @brief Store the file header
 *
 * @param content pointer to the content of the file
 * @param header pointer of the structure to store informations
 */
void header_storage(char *content, Elf32_Ehdr *header);

/**
 * @brief Store the section headers informations
 *
 * @param content pointer to the content of the file
 * @param shdrn pointer to the structure to store section headers informations
 * @param offset the byte start of section header
 * @param shstrndx the index entry of section headers name
 * @param is_big_endian boolean of endianess statement of the file
 */
void section_headers_storage(char *content, Elf32_Shdr_named *shdrn, unsigned long offset, Elf32_Half shstrndx, bool is_big_endian);

/**
 * @brief Store the symbols table of the elf file
 *
 * @param content pointer to the content of the file
 * @param shdrn The section headers informations of the file
 * @param symn Pointer to the structure to store symbols table informations
 * @param is_big_endian boolean of endianess statement of the file
 * @return int Size of the symbols table section
 */
int sym_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, bool is_big_endian);

/**
 * @brief Simple boolean condition to know if it's NULL section
 *
 * @param shdrn Pointer to the structure where is contain the section headers entry
 * @param i index of the table entry
 * @return true if it's not a NULL section
 * @return false if it's a NULL section
 */
bool is_section_code(Elf32_Shdr_named *shdrn, int i);

/**
 * @brief Simple boolean condition to know if it's SYMTAB section
 *
 * @param shdrn Pointer to the structure where is contain the section headers entry
 * @param i index of the table entry
 * @return true if it's not a SYMTAB section
 * @return false if it's a SYMTAB section
 */
bool is_symtab_type(Elf32_Shdr_named *shdrn, int i);

/**
 * @brief Simple boolean condition to know if it's REL section
 *
 * @param shdrn Pointer to the structure where is contain the section headers entry
 * @param i index of the table entry
 * @return true if it's not a REL section
 * @return false if it's a REL section
 */
bool is_rel_type(Elf32_Shdr_named *shdrn, int i);

/**
 * @brief Simple boolean condition to know if it's STRTAB section
 *
 * @param shdrn Pointer to the structure where is contain the section headers entry
 * @param i index of the table entry
 * @return true if it's not a STRTAB section
 * @return false if it's a STRTAB section
 */
bool is_strtab_type(Elf32_Shdr_named *shdrn, int i);

/**
 * @brief Generate a chained list, using the Elf_stct_list structure to store all the sections
 *
 * @param content pointer to the content of the file
 * @param shdrn section headers informations
 * @param cargo pointer to the head of the chained list
 * @return Elf32_stct_list
 */
Elf32_stct_list section_content_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_stct_list cargo);

/**
 * @brief Generate an array to store the differents relocation tables
 *
 * @param content pointer to the content of the file
 * @param shdrn section headers informations
 * @param symn symbols table
 * @param nb_rel Number of relocation sections in the file
 * @param is_big_endian boolean of endianess statement of the file
 * @return Elf32_Rel_named*
 */
Elf32_Rel_named *rel_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, int *nb_rel, bool is_big_endian);

/**
 * @brief Store the file informations in the Elf32_file structure
 *
 * @param content pointer to the content of the file
 * @param elf pointer to the structure to store file informations
 */
void storage_elf_content(char *content, Elf32_file *elf);

#endif