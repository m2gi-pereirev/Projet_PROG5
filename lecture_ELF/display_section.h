#ifndef __DISPLAY_SECTION_H__
#define __DISPLAY_SECTION_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <inttypes.h>

/**
 * @brief prints the name of section
 *
 * @param name
 */
void section_print_name(Elf32_Word name);

/**
 * @brief prints the type of section
 *
 * @param type
 */
void section_print_type(Elf32_Word type);

/**
 * @brief prints the flags of section
 *
 * @param flags
 */
void section_print_flags(Elf32_Word flags);

/**
 * @brief prints the offset of section
 *
 * @param decalage
 */
void section_print_decalage(Elf32_Off decalage);

/**
 * @brief Print the section headers of the file
 *
 * @param shdr
 * @param shnum
 */
void affichage_section(Elf32_Shdr *shdr, int shnum);

#endif