#ifndef __DISPLAY_SECTION_H__
#define __DISPLAY_SECTION_H__

#include <stdlib.h>
#include <stdio.h>
#include <elf.h>

/**
 * @brief Print the header of the display
 *
 * @param name of the section
 */
void print_section_content_header(char *name);

/**
 * @brief Print Section content
 *
 * @param section_content Content of the section
 * @param size Size of the section in bytes
 */
void print_section(char *section_content, int size);

    /**
     * @brief
     *
     * @param
     */
    void print_section_content();

#endif