#ifndef __BFILE_H__
#define __BFILE_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <elf.h>

#include <inttypes.h>

/**
 * @brief Read the current bit of the file.
 * You need to open the file before reading use bitopen
 * @param nb_octet number of bytes to be read
 * @return uint32_t the bits of the file demanded
 */
uint32_t octetread(size_t nb_octet);

/**
 * @brief Read the current bit of the file.
 * You need to open the file before reading use bitopen
 * @param shdr_adress the adress where the value read is stored
 *        nb_octet number of bytes to be read
 * @return nothing
 */
void octetread_section(void *shdr_adress, int nb_octet);

/**
 * @brief Open a file to read it bit per bit
 *
 * @param file name of the file as to be defined
 * @return true if the file correctly opened
 * @return false if cannont opened the file
 */
bool bitopen(char const *file);

/**
 * @brief Close the file \n The file as to be opened before, by using bitopen
 *
 * @return true if the file correctly close
 * @return false if cannot close the file
 */
bool bitclose(void);

/**
 * @brief Return the current status of the file
 *
 * @return true if the file is openned
 * @return false if the file isn't oppend
 */
bool bitopened(void);

/**
 * @brief returns the binary string corresponding to the parameter
 *
 * @param i value to be transformed
 * @return char* the biannual string corresponding to the value i
 */
char *bin(unsigned int i);

#endif