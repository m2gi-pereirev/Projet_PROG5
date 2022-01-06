#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <stdio.h>
#include <stdlib.h>

#include "display_header.h"
#include "display_section_headers.h"
#include "display_section.h"
#include "display_symbole.h"

/**
 * @brief Display help message to use the program, on the correct output
 *
 * @param stream were the help as to be print stderr for usage error, or stdout for help message
 * @param exit_code EXIT_FAILURE or EXIT_SUCCESS
 * @param programe_name argv[0]
 */
void print_usage(FILE *stream, int exit_code, char *programe_name);

#endif
