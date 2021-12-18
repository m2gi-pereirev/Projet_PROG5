// #ifndef __READ_HEADER_ELF_H__
// #define __READ_HEADER_ELF_H__

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <elf.h>

/**
 * @brief Read the current bit of the file.
 * You need to open the file before reading use bitopen
 * @param nb_bit number of bits to be read
 * @return ** int the bit of the file
 */
uint32_t bitread(size_t nb_bit);

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

// #endif