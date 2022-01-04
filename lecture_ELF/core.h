#ifndef __CORE_H__
#define __CORE_H__

#include <elf.h>

/**
 * @brief Structure containing the different section headers, their names and the number of headers
 *
 */
typedef struct Section_headers_named
{
  int shnum; // Number of section headers
  char **names; // Names of sections headers
  Elf32_Shdr *shdr; // Content of section headers
} Elf32_Shdr_named;

#endif