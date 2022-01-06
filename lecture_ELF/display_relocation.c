#include "display_relocation.h"

void print_relocation_header(char *name, Elf32_Off offset, int nb_entry)
{
  if (nb_entry == 1)
    printf("Relocation section '%s' at offset 0x%hx contains %d entry:\n", name, offset, nb_entry);
  else
    printf("Relocation section '%s' at offset 0x%hx contains %d entries:\n", name, offset, nb_entry);

  printf("  Offset      Info    Type            Sym.Value  Sym. Name\n");
}

void print_relocation_section(Elf32_Rel *rel_section, Elf32_Shdr *shdr, char *shdr_name)
{
  print_relocation_header(shdr_name, shdr->sh_offset);
}