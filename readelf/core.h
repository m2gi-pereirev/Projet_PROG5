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
  bool rel_type;     // If true it's relocation section else if false it's a relocation section with addend
  int rel_num;       // Number of entries in section
  char **names;      // Names of entries
  uint32_t *sym_val; // Value of entries
  Elf32_Rel *rel;    // Array of relocation entries
  Elf32_Rela *rela;  // Array of relocation entries with addend
} Elf32_Rel_named;

// ELF file structure

typedef struct Elf32_stct Elf32_stct;

struct Elf32_stct
{
  unsigned long size; // Size of the section
  char *name;         // Name of the section
  char *content;      // Array contaning the content of the section
  Elf32_stct *next;   // Pointer to the next section
};

typedef struct Elf32_file
{
  Elf32_Ehdr *ehdr;        // Header of the file
  Elf32_stct *section;     // Array of section
  Elf32_Shdr_named *shdrn; // Section header
  Elf32_Sym_named *symn;   // Symbole table
} Elf32_file;

#endif