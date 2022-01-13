#include "saving.h"

FILE *load_elf_output(char *filename)
{
  FILE *file;
  if (filename != NULL)
  {
    file = fopen(filename, "wb");
    if (file != NULL)
      return file;
  }
  return NULL;
}

void write_file_header(FILE *file, Elf32_Ehdr *ehdr, bool big_endian)
{
  if (big_endian)
    header_endianess(ehdr);
  fwrite(ehdr, sizeof(Elf32_Ehdr), 1, file);
}

void write_sections(FILE *file, Elf32_stct_list sections_array)
{
  if (sections_array != NULL)
  {
    if (!sections_array->symtab && !sections_array->strtab)
    {
      if (sections_array->align > 1)
      {
        int byte_index = ftell(file);
        char null = 0;
        while (byte_index % sections_array->align != 0)
        {
          fwrite(&null, sizeof(char), 1, file);
          ++byte_index;
        }
      }
      fwrite(sections_array->content, sizeof(char), sections_array->size, file);
    }

    write_sections(file, sections_array->next);
  }
}

void write_strtab_sections(FILE *file, Elf32_stct_list sections_array)
{
  if (sections_array != NULL)
  {
    if (sections_array->strtab)
    {
      fwrite(sections_array->content, sizeof(char), sections_array->size, file);
    }
    write_strtab_sections(file, sections_array->next);
  }
}

void write_section_headers(FILE *file, Elf32_Shdr_named *shdrn, bool big_endian)
{
  for (int i = 0; i < shdrn->shnum; i++)
  {
    if (big_endian)
      section_headers_endianess(&shdrn->shdr[i]);

    fwrite(&shdrn->shdr[i], sizeof(Elf32_Shdr), 1, file);
  }
}

void write_symbols(FILE *file, Elf32_Sym_named *symn, Elf32_Shdr_named *shdrn, int nb_rel, bool big_endian)
{
  int byte_index = ftell(file);
  char null = 0x00;
  while (byte_index % 4 != 0)
  {
    fwrite(&null, sizeof(char), 1, file);
    ++byte_index;
  }
  for (size_t i = 0; i < symn->sym_num; i++)
  {
    if (big_endian)
      symbole_endianess(&symn->sym[i]);
    fwrite(&symn->sym[i], sizeof(Elf32_Sym), 1, file);
  }
}

void write_elf_content(Elf32_file *elf, FILE *file)
{
  write_file_header(file, elf->ehdr, elf->big_endian);
  write_sections(file, elf->sections_array);
  write_symbols(file, elf->symn, elf->shdrn, elf->nb_rel, elf->big_endian);
  write_strtab_sections(file, elf->sections_array);
  write_section_headers(file, elf->shdrn, elf->big_endian);
  fclose(file);
}