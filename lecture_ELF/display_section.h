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

void section_print_number(int num);
void section_print_display_header();
void section_print_address(Elf32_Addr address);
void section_print_size(Elf32_Word size);
void section_print_entrysize(Elf32_Word entrysize);
void section_print_link(Elf32_Word link);
void section_print_info(Elf32_Word info);
void section_print_alignement(Elf32_Word align);

/**
 * @brief Print the section headers of the file
 *
 * @param shdr
 * @param shnum
 */
void affichage_section(Elf32_Shdr *shdr, int shnum);

#endif