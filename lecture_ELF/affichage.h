#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <elf.h>

void print_type_name(char *type);
void print_magic(unsigned char *ident);
void print_isElfType(unsigned char *ident);
void print_class(unsigned char *ident);
void print_data(unsigned char *ident);
void print_version_id(unsigned char *ident);
void print_os(unsigned char *ident);
void print_abi_version(unsigned char *ident);
void print_type(Elf32_Half type);
void print_machine(Elf32_Half machine);
void print_version(Elf32_Word version);
void print_adresse_offset(Elf32_Ehdr *ehdr);

/**
 * @brief Print the header of the file
 *
 * @param ehdr
 */
void affichage_entete(Elf32_Ehdr *ehdr);

/**
 * @brief return if ti's a ELF formated file
 *
 * @param ident 16 first bit of the file
 * @result true if it's ELF formated file
 * @result false if it's not ELF formated file
 */
bool is_ELF_header(unsigned char *ident);

#endif