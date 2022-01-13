#ifndef __SECTION_GENERATOR_H__
#define __SECTION_GENERATOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * @brief Allocate a new section container
 *
 * @param size size of section
 * @param name name of section
 * @param content binary content of the section (in char *array)
 * @param symtab boolen is true if its a symtab section
 * @param rel boolen is true if its a rel section
 * @param strtab boolen is true if its a strtab section
 * @param offset offset of the section
 * @param align alignement of the section
 * @param idx index of the section
 * @return Elf32_stct_item* pointer to the container
 */
Elf32_stct_item *section_container_summoner(int size, char *name, char *content, bool symtab, bool rel, bool strtab, uint32_t offset, uint32_t align, int idx);

/**
 * @brief Delete a container without memory leaks
 *
 * @param container pointer to a scetion container
 */
void section_container_destroyer(Elf32_stct_item *container);

/**
 * @brief Delete all the sections list without memory list
 *
 * @param cargo pointer to head of chained list
 */
void sections_list_destroyer(Elf32_stct_item *cargo);

/**
 * @brief Display informations contained in chained list
 *
 * @param cargo pointer to head of chained list
 */
void section_containers_display(Elf32_stct_item *cargo);

/**
 * @brief Add a new container in the chain list (ordered by increasing offset)
 *
 * @param cargo pointer to head of chained list
 * @param content binary content of the section (in char *array)
 * @param name name of section
 * @param size size of section
 * @param symtab boolen is true if its a symtab section
 * @param rel boolen is true if its a rel section
 * @param strtab boolen is true if its a strtab section
 * @param offset offset of the section
 * @param align alignement of the section
 * @param idx index of the section
 * @return Elf32_stct_list
 */
Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int size, bool symtab, bool rel, bool strtab, Elf32_Off offset, uint32_t align, int idx);

/**
 * @brief Return a true if the container with offset offset exist, else false
 *
 * @param cargo pointer to head of chained list
 * @param offset offset of the container
 * @return true container exist
 * @return false container doesn't exist
 */
bool container_exist(Elf32_stct_list cargo, uint32_t offset);

/**
 * @brief Returns a pointer to the previous container
 *
 * @param cargo pointer to head of chained list
 * @param prev pointer to the previous container
 * @param offset offset of the followinf container
 * @return Elf32_stct_item* pointer to the search container, else null
 */
Elf32_stct_item *finder_prev(Elf32_stct_list cargo, Elf32_stct_item *prev, uint32_t offset);

/**
 * @brief Returns pointer to the searched container
 *
 * @param cargo pointer to head of chained list
 * @param offset offset of the searched container
 * @return Elf32_stct_item* pointer to the search container, else null
 */
Elf32_stct_item *finder(Elf32_stct_list cargo, uint32_t offset);

/**
 * @brief Return a pointer to the index container idx
 *
 * @param cargo pointer to head of chained list
 * @param idx of the desire container
 * @return Elf32_stct_item* pointer to the search container, else null
 */
Elf32_stct_item *finder_realoc(Elf32_stct_list cargo, int idx);

/**
 * @brief Return pointer to the symtab container
 *
 * @param cargo pointer to head of chained list
 * @return Elf32_stct_item* pointer to the symtab container, else null
 */
Elf32_stct_item *symtab_finder(Elf32_stct_list cargo);

/**
 * @brief swap of places of the two containers d'offset off1 et off2
 *
 * @param cargo pointer to head of chained list
 * @param off1 offset of container one
 * @param off2 offset of container two
 * @return Elf32_stct_list modified chained list
 */
Elf32_stct_list swap_section(Elf32_stct_item *cargo, uint32_t off1, uint32_t off2);

/**
 * @brief Remove an container from the chained list
 *
 * @param cargo pointer to head of chained list
 * @param offset of the container to remove
 * @return Elf32_stct_list modified chained list
 */
Elf32_stct_list remove_section(Elf32_stct_list cargo, uint32_t offset);

/**
 * @brief Modify offset of the containers after the reorganization
 *
 * @param cargo pointer to head of chained list
 * @return Elf32_stct_list modified chained list
 */
Elf32_stct_list __section_offset_remappage(Elf32_stct_list cargo);

/**
 * @brief Initialization of the offset modification
 *
 * @param cargo pointer to head of chained list
 * @param header_size size of the header
 * @return Elf32_stct_list modified chained list
 */
Elf32_stct_list section_offset_remappage(Elf32_stct_list cargo, uint16_t header_size);

/**
 * @brief  Change the indexes of the sections after reorganization
 *
 * @param cargo pointer to head of chained list
 * @return Elf32_stct_list modified chained list
 */
Elf32_stct_list reindex(Elf32_stct_list cargo);

/**
 * @brief Returns a pointer to the last container in the chained list
 *
 * @param cargo pointer to head of chained list
 * @return Elf32_stct_item* Pointeur to the container, else null
 */
Elf32_stct_item *last_finder(Elf32_stct_list cargo);

#endif