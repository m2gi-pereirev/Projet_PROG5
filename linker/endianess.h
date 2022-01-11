#ifndef __ENDIANESS_H__
#define __ENDIANESS_H__

#include <byteswap.h>
#include <elf.h>

/**
 * @brief Allows you to switch from large to small endian and vice versa for the file header
 *
 * @param ehdr ELF header structure
 */
void header_endianess(Elf32_Ehdr *ehdr);

/**
 * @brief Allows you to switch from big to small endian and vice versa for the section headers
 *
 * @param shdr ELF section headers structure
 */
void section_headers_endianess(Elf32_Shdr *shdr);

/**
 * @brief Allows to switch from big to small endian and vice versa for the symbols table
 *
 * @param sym Elf symbole table structure
 */
void symbole_endianess(Elf32_Sym *sym);

/**
 * @brief Allows to switch from big to small endian and vice versa for one relocation entry
 *
 * @param rel Elf relocation structure
 */
void rel_section_endianess(Elf32_Rel *rel);

#endif