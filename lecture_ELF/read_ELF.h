#ifndef __READ_HEADER_ELF_H__
#define __READ_HEADER_ELF_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <elf.h>
#include <getopt.h>
#include <assert.h>

#include "endianess.h"
#include "display.h"
#include "core.h"

//! Strutures

typedef struct execution_options
{
  int nb_files;         // nb_files passed in arguments
  bool header;          // display only the header file
  bool section_headers; // display only section headers
  bool big_endian_file; // true if file is in big_endian
  bool hexdump;
  bool symb;
  bool rel;
} Exec_options;

typedef struct hexdump_option
{
  bool is_string;
  int section_number;
  char *section_name;
} hexdump_option;

//! Prototype

//* Detection of arguments
/**
 * @brief Detects the arguments and initializes the program accordingly, by using getopt_long
 *
 * @param argc Number of arguments
 * @param argv Array of strings containing the arguments
 * @param exec_op Structure to initialize the program
 * @param hexdump Structure if the display of a section is requested
 * @return char** Array of strings containing the paths of the file(s)
 */
char **options_read(int argc, char **argv, Exec_options *exec_op, hexdump_option *hexdump);

//$ ----

/**
 * @brief Initialize the program with the options_read function
 *
 * @param argc Number of arguments
 * @param argv Array of strings containing the arguments
 * @param exec_op Structure to initialize the program
 * @param hexdump Structure if the display of a section is requested
 * @return char** Array of strings containing the paths of the file(s)
 */
char **init_execution(int argc, char **argv, Exec_options *exec_op, hexdump_option *hexdump);

//*--------------------------------------------------------------------------------------------------
//* ELF detection
/**
 * @brief return if it's a ELF file
 *
 * @param ident 16 first bit of the file
 * @result true if it's ELF file
 * @result false if it's not ELF file
 */
bool is_ELF_file(unsigned char *ident);

//$ ----

/**
 * @brief return if it's a 32-bits ELF file
 *
 * @param ident 16 first bit of the file
 * @return true if it's 32-bits ELF file
 * @return false if it's not 32-bits ELF file
 */
bool is_ELF32(unsigned char *ident);

//*--------------------------------------------------------------------------------------------------
//* ELF auxiliairies

/**
 * @brief Returns the section index corresponding to the one contained in the hexdump structure
 *
 * @param hexdump Structure containing an int or an string corresponding to a section name
 * @param shdr_named Structure containing all section headers of the file
 * @return int Index of the section header
 */
int section_index_finder(hexdump_option *hexdump, Elf32_Shdr_named *shdr_named);

//*--------------------------------------------------------------------------------------------------
//* ELF reading
/**
 * @brief Reads the file header into the file
 *
 * @param ehdr Structure to contain the information read
 * @param *filename Pointer to the opened file
 */
void header_read(Elf32_Ehdr *ehdr, FILE *filename);

//$ ----

/**
 * @brief Reads the section headers of the file
 *
 * @param exec_op Settings of the program
 * @param *filename Pointer to the opened file
 * @param ehdr Structure containing the file header information
 * @param shdr_named Structure to contain the information read
 */
void section_headers_read(Exec_options *exec_op, FILE *filename, Elf32_Ehdr *ehdr, Elf32_Shdr_named *shdr_named);

//$ ----

/**
 * @brief Reads the table of symbols from the file
 *
 * @param exec_op Settings of the program
 * @param *filename Pointer to the opened file
 * @param shdr_named Structure containing the section headers information
 * @param sym_named Structure to contain the information read
 */
void symbole_table_elf(Exec_options *exec_op, FILE *filename, Elf32_Shdr_named *shdr_named, Elf32_Sym_named *sym_named);

/**
 * @brief Reads the desired section from the file
 *
 * @param exec_op Settings of the program
 * @param *filename Pointer to the opened file
 * @param hexdump Structure containing an int or an string corresponding to a section name
 * @param shdr_named Structure containing the section headers information
 * @param *section_content String containing the data of the section
 * @return int Returns the number of blocks read in the section (in bytes)
 */
int section_content_read(Exec_options *exec_op, FILE *filename, hexdump_option *hexdump, Elf32_Shdr_named *shdr_named, char *section_content);

//*--------------------------------------------------------------------------------------------------
//* FREE

/**
 * @brief Free the memory space used by the shdr_named structure, to avoid memory leaks
 *
 * @param shdr_named Structure to be freed
 */
void free_shdr_named(Elf32_Shdr_named *shdr_named);

//$ ----

/**
 * @brief Free the memory space used by the sym_named structure, to avoid memory leaks
 *
 * @param sym_named Structure to be freed
 */
void free_sym_named(Elf32_Sym_named *sym_named);

#endif
