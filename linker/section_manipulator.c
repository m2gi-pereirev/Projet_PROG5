#include "section_manipulator.h"

Elf32_stct_item *section_container_summoner(int size, char *name, char *content, bool strtab_type, uint32_t offset, uint32_t align)
{
  Elf32_stct_item *container = calloc(1, sizeof(Elf32_stct_item));

  //$ Allocation
  container->name = calloc(strlen(name) + 1, sizeof(char));
  container->content = calloc(size, sizeof(char));

  //$ Assignment
  container->strtab_type = strtab_type;
  container->size = size;
  container->offset = offset;
  container->align = align;
  container->next = NULL;
  strcpy(container->name, name);
  memcpy(container->content, content, size);

  return container;
}

void section_container_destroyer(Elf32_stct_item *container)
{
  free(container->name);
  free(container->content);
  free(container);
}

void sections_list_destroyer(Elf32_stct_item *cargo)
{
  if (cargo != NULL)
  {
    sections_list_destroyer(cargo->next);
    section_container_destroyer(cargo);
  }
}

void section_containers_display(Elf32_stct_item *cargo)
{
  if (cargo != NULL)
  {
    if (cargo->name != NULL)
      fprintf(stderr, "%s: 0x%hx\n", cargo->name, cargo->offset);
    else
      fprintf(stderr, "(null)\n");
    section_containers_display(cargo->next);
  }
}

Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int size, bool strtab_type, Elf32_Off offset, uint32_t align)
{
  if (cargo == NULL)
  {
    Elf32_stct_item *new_container = section_container_summoner(size, name, content, strtab_type, offset, align);
    return new_container;
  }
  else
  {
    if (offset >= cargo->offset)
    {
      cargo->next = section_container_adder(cargo->next, content, name, size, strtab_type, offset, align);
      return cargo;
    }
    else
    {
      Elf32_stct_item *new_container = section_container_summoner(size, name, content, strtab_type, offset, align);
      new_container->next = cargo;
      return new_container;
    }
  }
}

bool container_exist(Elf32_stct_list cargo, uint32_t offset)
{
  if (cargo == NULL)
    return false;
  if (cargo->offset == offset)
    return true;
  return container_exist(cargo->next, offset);
}

Elf32_stct_item *finder_prev(Elf32_stct_list cargo, Elf32_stct_item *prev, uint32_t offset)
{
  if (cargo == NULL)
    return NULL;
  if (cargo->offset == offset)
    return prev;
  return finder_prev(cargo->next, cargo, offset);
}

Elf32_stct_item *finder(Elf32_stct_list cargo, uint32_t offset)
{
  if (cargo == NULL)
    return NULL;
  if (cargo->offset == offset)
    return cargo;
  return finder(cargo->next, offset);
}

Elf32_stct_list swap_section(Elf32_stct_item *cargo, uint32_t off1, uint32_t off2)
{
  if (!container_exist(cargo, off1) && !container_exist(cargo, off2))
    return cargo;

  if (off1 == off2)
    return cargo;

  Elf32_stct_item *container1 = NULL, *container2 = NULL, *prev1 = NULL, *prev2 = NULL, *temp = NULL;

  container1 = finder(cargo, off1);
  prev1 = finder_prev(cargo, NULL, off1);
  container2 = finder(cargo, off2);
  prev2 = finder_prev(cargo, NULL, off2);

  if (container1 != NULL && container2 != NULL)
  {
    if (prev1 != NULL)
      prev1->next = container2;

    if (prev2 != NULL)
      prev2->next = container1;

    temp = container1->next;
    container1->next = container2->next;
    container2->next = temp;

    if (prev1 == NULL)
      cargo = container2;
    else if (prev2 == NULL)
      cargo = container1;
  }
  return cargo;
}

Elf32_stct_list remove_section(Elf32_stct_list cargo, uint32_t offset)
{
  Elf32_stct_item *container = NULL, *prev = NULL;

  container = finder(cargo, offset);
  prev = finder_prev(cargo, NULL, offset);

  if (container != NULL)
  {
    if (prev != NULL)
      prev->next = container->next;
    else
      cargo = container->next;

    section_container_destroyer(container);
  }
  return cargo;
}
