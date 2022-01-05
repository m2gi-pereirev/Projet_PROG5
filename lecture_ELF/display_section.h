#ifndef __DISPLAY_SECTION_H__
#define __DISPLAY_SECTION_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <inttypes.h>
#include <string.h>

#include "core.h"

/**
 * @brief prints the name of section
 *
 * @param name
 */
void section_print_name(char *name);

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
 * @brief
 *
 * @param num
 */
void section_print_number(int num);

/**
 * @brief
 *
 */
void section_print_display_header();

/**
 * @brief
 *
 * @param address
 */
void section_print_address(Elf32_Addr address);

/**
 * @brief
 *
 * @param size
 */
void section_print_size(Elf32_Word size);

/**
 * @brief
 *
 * @param entrysize
 */
void section_print_entrysize(Elf32_Word entrysize);

/**
 * @brief
 *
 * @param link
 */
void section_print_link(Elf32_Word link);

/**
 * @brief
 *
 * @param info
 */
void section_print_info(Elf32_Word info);

/**
 * @brief
 *
 * @param align
 */
void section_print_alignement(Elf32_Word align);

/**
 * @brief
 *
 */
void section_print_flag_key_info();

/**
 * @brief Print the section headers of the file
 *
 * @param shdr
 * @param shnum
 */
void print_section_headers(Elf32_Shdr_named *shdr_named);

#endif