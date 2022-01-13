#include "freed.h"

void free_elf32_ehdr(Elf32_Ehdr *ehdr)
{
  free(ehdr);
}

void free_elf32_shdrn(Elf32_Shdr_named *shdrn)
{
  for (int i = 0; i < shdrn->shnum; i++)
    free(shdrn->names[i]);
  free(shdrn->names);
  free(shdrn->shdr);
  free(shdrn);
}

void free_elf32_symn(Elf32_Sym_named *symn)
{
  for (int i = 0; i < symn->sym_num; i++)
    free(symn->names[i]);
  free(symn->names);
  free(symn->sym);
  free(symn);
}

void free_elf32_reln(Elf32_Rel_named *reln, int nb_rel)
{
  for (int i = 0; i < nb_rel; i++)
  {
    for (int j = 0; j < reln[i].rel_num; j++)
      free(reln[i].names[j]);
    free(reln[i].sym_val);
    free(reln[i].names);
    free(reln[i].rel);
  }
  free(reln);
}

void free_elf32_file(Elf32_file *elf)
{
  //$ Header
  free_elf32_ehdr(elf->ehdr);
  elf->eh_size = 0;

  //$ Section headers
  free_elf32_shdrn(elf->shdrn);
  elf->sh_size = 0;

  //$ Table of Symbols
  free_elf32_symn(elf->symn);

  //$ Sections content
  sections_list_destroyer(elf->sections_array);

  //$ Relocation tables
  free_elf32_reln(elf->reln, elf->nb_rel);
}
