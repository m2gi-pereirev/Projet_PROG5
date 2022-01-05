#ifndef __DISPLAY_SYMBOLE_H__
#define __DISPLAY_SYMBOLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

#include "core.h"

/**
 * @brief Print the table of symbols
 *
 * @param *sym
 */
void print_table_sym(Elf32_Sym_named *sym_named);

#endif