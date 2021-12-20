#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <elf.h>
#include <inttypes.h>


/**
 * @brief prints the magic number
 *
 * @param ident
 */
void print_magic(unsigned char *ident);

/**
 * @brief prints the first line if the file is an ELF
 *
 * @param ident
 */
void print_isElfType(unsigned char *ident);

/**
 * @brief prints the class of the file 32 or 64 bits
 *
 * @param ident
 */
void print_class(unsigned char *ident);

/**
 * @brief prints data type little endian or big endian
 *
 * @param ident
 */
void print_data(unsigned char *ident);

/**
 * @brief prints the ELF version
 *
 * @param ident
 */
void print_version_id(unsigned char *ident);

/**
 * @brief prints the OS ABI
 *
 * @param ident
 */
void print_os(unsigned char *ident);

/**
 * @brief prints the ABI version
 *
 * @param ident
 */
void print_abi_version(unsigned char *ident);

/**
 * @brief prints the type of the file
 *
 * @param type
 */
void print_type(Elf32_Half type);

/**
 * @brief prints for which machine the file is made
 *
 * @param machine
 */
void print_machine(Elf32_Half machine);

/**
 * @brief prints for which machine the file is made
 *
 * @param version
 */
void print_version(Elf32_Word version);

/**
 * @brief prints the addresses and values contained at the end of the header.
 *
 * @param ehdr
 */
void print_adresse_offset(Elf32_Ehdr *ehdr);

/**
 * @brief prints the correspondant value of flags
 *
 * @param flags
 */
void print_flags(Elf32_Word flags);

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