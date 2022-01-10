#ifndef __CORE_H__
#define __CORE_H__

#include <elf.h>
#include <stdbool.h>

/**
 * @brief Structure containing the different section headers, their names and the number of headers
 *
 */
typedef struct Section_headers_named
{
  int shnum;        // Number of section headers
  char **names;     // Names of sections headers
  Elf32_Shdr *shdr; // Content of section headers
} Elf32_Shdr_named;

typedef struct Symbols_table_named
{
  int sym_num;    // Number of section headers
  char **names;   // Names of sections headers
  Elf32_Sym *sym; // Content of section headers
} Elf32_Sym_named;

typedef struct Rel_section_named
{
  bool rel_type;    // If true it's relocation section else if false it's a relocation section with addend
  int rel_num;      // Number of entries in section
  char **names;     // Names of entries
  uint32_t *sym_val; // Value of entries
  Elf32_Rel *rel;   // Array of relocation entries
  Elf32_Rela *rela; // Array of relocation entries with addend
} Elf32_Rel_named;

#endif