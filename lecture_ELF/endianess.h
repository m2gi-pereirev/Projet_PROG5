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
 * @brief Allows to switch from big to small endian and vice versa for the section headers
 *
 * @param shdr ELF section headers structure
 */
void section_headers_endianess(Elf32_Shdr *shdr);

#endif