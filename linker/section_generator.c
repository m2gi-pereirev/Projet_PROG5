#include "section_generator.h"

Elf32_stct *section_container_summoner(void)
{
  Elf32_stct *container = calloc(1, sizeof(Elf32_stct));
  return container;
}

void section_container_destroyer(Elf32_stct *container)
{
  free(container->name);
  free(container->content);
  free(container);
}

void sections_list_destroyer(Elf32_stct *head)
{
  if (head->next != NULL)
  {
    sections_list_destroyer(head->next);
    section_container_destroyer(head);
  }
}

void section_containers_display(Elf32_stct *sections)
{
  if (sections != NULL)
  {
    if (sections->name != NULL)
      printf("%s\n", sections->name);
    section_containers_display(sections->next);
  }
}

void section_container_adder(Elf32_stct *head, char *content, char *name, int idx, int size)
{
  if (head != NULL)
  {
    if (head->next != NULL)
    {
      section_container_adder(head->next, content, name, idx, size);
    }
    else
    {
      Elf32_stct *new_container = section_container_summoner();

      new_container->name = calloc(strlen(name) + 1, sizeof(char));
      new_container->content = calloc(size, sizeof(char));
      new_container->size = size;
      new_container->idx = idx;

      strcpy(new_container->name, name);
      memcpy(new_container->content, content, size);
      head->next = new_container;
    }
  }
  else
  {
    Elf32_stct *new_container = section_container_summoner();
    new_container->name = calloc(strlen(name), sizeof(char));
    new_container->content = calloc(size, sizeof(char));
    new_container->size = size;
    new_container->idx = idx;
    strcpy(new_container->name, name);
    memcpy(new_container->content, content, size);
    head = new_container;
  }
}