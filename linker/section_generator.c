#include "section_generator.h"

Elf32_stct_item *section_container_summoner(int size, int idx, char *name, char *content)
{
  Elf32_stct_item *container = calloc(1, sizeof(Elf32_stct_item));

  //$ Allocation
  container->name = calloc(strlen(name) + 1, sizeof(char));
  container->content = calloc(size, sizeof(char));

  //$ Assignment
  container->size = size;
  container->idx = idx;
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
      printf("%s\n", cargo->name);
    section_containers_display(cargo->next);
  }
}

Elf32_stct_list section_container_adder(Elf32_stct_item *cargo, char *content, char *name, int idx, int size)
{
  if (cargo == NULL)
  {
    Elf32_stct_item *new_container = section_container_summoner(size, idx, name, content);
    return new_container;
  }
  else
  {
    cargo->next = section_container_adder(cargo->next, content, name, idx, size);
    return cargo;
  }
}