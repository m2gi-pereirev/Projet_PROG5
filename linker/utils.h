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
  int rel_num;       // Number of entries in section
  int info;          //
  uint32_t *sym_val; // Value of entries
  char **names;      // Names of entries
  Elf32_Rel *rel;    // Array of relocation entries
} Elf32_Rel_named;

// ELF file structure

typedef struct Elf32_stct Elf32_stct;

struct Elf32_stct
{
  unsigned long size; // Size of the section
  int idx;            // Index of section
  char *name;         // Name of the section
  char *content;      // Array contaning the content of the section
  Elf32_stct *next;   // Pointer to the next section
};

typedef struct Elf32_file
{
  bool big_endian;
  unsigned long int eh_size;  //
  Elf32_Ehdr *ehdr;           // Header of the file
  Elf32_stct *section;        // Array of section
  unsigned long int sh_size;  //
  Elf32_Shdr_named *shdrn;    // Section headers
  unsigned long int sym_size; //
  Elf32_Sym_named *symn;      // Symbols table
  int nb_rel;                 // Number of relocation table
  Elf32_Rel_named *reln;      // Array of relocations table
} Elf32_file;

#endif