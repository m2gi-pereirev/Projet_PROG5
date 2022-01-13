#ifndef __REORGANIZATION_H__
#define __REORGANIZATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

#include "utils.h"
#include "section_manipulator.h"
#include "freed.h"

/**
 * @brief Affect the symbols value with the correct offset of the section if it's a sections type
 *
 * @param shdrn pointer to the sections headers structure
 * @param symn pointer to the symbols structure
 * @param reln pointer to the relocation section structure
 * @param nb_rel number of relocations
 */
void symbol_value_affectation(Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, Elf32_Rel_named *reln, int nb_rel);

/**
 * @brief Remove the relocations section in the chained list
 *
 * @param sections_array chained list of the sections file
 * @param shdrn pointer to the section headers structure
 * @return Elf32_stct_list the modified chained list
 */
Elf32_stct_list remove_rel_section(Elf32_stct_list sections_array, Elf32_Shdr_named *shdrn);

/**
 * @brief Change the index of Section header string table index in the section headers
 *
 * @param shdrn pointer to section headers structure
 * @return uint16_t index of shstrndx
 */
uint16_t new_shstrndx(Elf32_Shdr_named *shdrn);

/**
 * @brief Modifie the offset of section headers to match with the new file (without relocation section)
 *
 * @param cargo chained list of file sections
 * @param shdrn pointer to section headers structure
 * @param ehdr pointer to file header
 * @param symn pointer to symbols header
 */
void section_header_adresse_correction(Elf32_stct_list cargo, Elf32_Shdr_named *shdrn, Elf32_Ehdr *ehdr, Elf32_Sym_named *symn);

/**
 * @brief Change the section index in the symbols table using offset of sections
 *
 * @param symn pointer to symbols table structure
 * @param shdrn pointer to section headers structure
 */
void symbols_reindex(Elf32_Sym_named *symn, Elf32_Shdr_named *shdrn);

/**
 * @brief Delete relocatoin sectino headers entries
 *
 * @param shdrn pointer to section headers structure
 */
void shdr_rel_entry_delete(Elf32_Shdr_named *shdrn);

/**
 * @brief Delete the relocation section and remap the file
 *
 * @param elf poiter to Elf32_file structure
 */
void elf_reorganization(Elf32_file *elf);

#endif