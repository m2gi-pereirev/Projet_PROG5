#include "loading.h"
#include <sys/stat.h>

char *load_file_content(char *filename)
{
  FILE *file;
  char *content;
  int size = 0;

  if (filename != NULL)
  {
    file = fopen(filename, "rb");
    if (file != NULL)
    {
      fseek(file, 0L, SEEK_END);
      size = ftell(file);
      fseek(file, 0L, SEEK_SET);

      //
      content = calloc(size, sizeof(char));
      fread(content, sizeof(char), size, file);

      fclose(file);
      return content;
    }
    else
    {
      printf("linker: Error: file '%s', didn't exist", filename);
    }
  }
  else
  {
    printf("linker: Error: enter a file\n");
  }
  return NULL;
}

void header_storage(char *content, Elf32_Ehdr *header)
{
  memcpy(header, content, sizeof(Elf32_Ehdr));
}

void section_headers_storage(char *content, Elf32_Shdr_named *shdrn, unsigned long offset, Elf32_Half shstrndx, bool is_big_endian)
{
  // Allocation
  shdrn->names = calloc(shdrn->shnum, sizeof(char *));
  shdrn->shdr = calloc(shdrn->shnum, sizeof(Elf32_Shdr));

  // Get section names
  memcpy(&shdrn->shdr[shstrndx], content + offset + shstrndx * sizeof(Elf32_Shdr), sizeof(Elf32_Shdr));

  if (is_big_endian)
    section_headers_endianess(&shdrn->shdr[shstrndx]);

  char *Section_names = calloc(shdrn->shdr[shstrndx].sh_size, sizeof(char));
  memcpy(Section_names, content + shdrn->shdr[shstrndx].sh_offset, shdrn->shdr[shstrndx].sh_size * sizeof(char));

  for (int i = 0; i < shdrn->shnum; i++)
  {
    memcpy(&shdrn->shdr[i], content + offset + i * sizeof(Elf32_Shdr), sizeof(Elf32_Shdr));

    if (is_big_endian)
      section_headers_endianess(&shdrn->shdr[i]);

    if (shdrn->shdr[i].sh_name)
    {
      char *name = "";
      name = Section_names + shdrn->shdr[i].sh_name;
      shdrn->names[i] = calloc(strlen(name) + 1, sizeof(char));
      strcpy(shdrn->names[i], name);
    }
  }
}

int sym_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, bool is_big_endian)
{
  int sym_idx = 0;
  while (shdrn->shdr[sym_idx].sh_type != SHT_SYMTAB)
    ++sym_idx;

  if (sym_idx < shdrn->shnum)
  {
    int sym_offset = shdrn->shdr[sym_idx].sh_offset;                       // offset of symbols table
    int sym_num = (int)(shdrn->shdr[sym_idx].sh_size / sizeof(Elf32_Sym)); // Number of entries in symbols table
    int str_sym_idx = shdrn->shdr[sym_idx].sh_link;                        // index of strings names of symbols
    int str_sym_offset = shdrn->shdr[str_sym_idx].sh_offset;               // offset for the symbol string names

    symn->sym_num = sym_num;

    // Allocation
    symn->names = calloc(sym_num, sizeof(char *));
    symn->sym = calloc(sym_num, sizeof(Elf32_Sym));

    // Get symbol names
    char *Sym_names = calloc(shdrn->shdr[str_sym_idx].sh_size, sizeof(char));
    memcpy(Sym_names, content + str_sym_offset, shdrn->shdr[str_sym_idx].sh_size);

    // Get table of symbols
    for (int i = 0; i < sym_num; i++)
    {
      memcpy(&symn->sym[i], content + sym_offset + i * sizeof(Elf32_Sym), sizeof(Elf32_Sym));

      if (is_big_endian)
        symbole_endianess(&symn->sym[i]);

      if ((ELF32_ST_TYPE(symn->sym[i].st_info) == STT_NOTYPE) && symn->sym[i].st_name)
      {
        char *name = "";
        name = Sym_names + symn->sym[i].st_name;
        symn->names[i] = calloc(strlen(name) + 1, sizeof(char));
        strcpy(symn->names[i], name);
      }
      if (ELF32_ST_TYPE(symn->sym[i].st_info) == STT_SECTION && symn->sym[i].st_shndx)
      {
        symn->names[i] = calloc(strlen(shdrn->names[symn->sym[i].st_shndx]) + 1, sizeof(char));
        strcpy(symn->names[i], shdrn->names[symn->sym[i].st_shndx]);
      }
    }
    return shdrn->shdr[sym_idx].sh_size;
  }
  return -1;
}

bool is_section_code(Elf32_Shdr_named *shdrn, int i)
{
  return (shdrn->shdr[i].sh_type != SHT_NULL && shdrn->shdr[i].sh_type != SHT_REL && shdrn->shdr[i].sh_type != SHT_SYMTAB && shdrn->shdr[i].sh_type != SHT_STRTAB);
}

void section_content_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_stct *head, int *i)
{
  if (*i < shdrn->shnum)
  {
    if (is_section_code(shdrn, *i))
    {
      section_container_adder(head, content + shdrn->shdr[(*i)].sh_offset, shdrn->names[(*i)], *i, shdrn->shdr[(*i)].sh_size);
      ++(*i);
      section_content_storage(content, shdrn, head, i);
    }
    else
    {
      ++(*i);
      section_content_storage(content, shdrn, head, i);
    }
  }
}

void init_section_content_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_stct *head)
{
  int i = 0;
  head = NULL;
  section_content_storage(content, shdrn, head, &i);
}

int rel_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, Elf32_Rel_named *reln, int nb_rel, bool is_big_endian)
{
  reln = NULL;
  nb_rel = 0;

  // Get number of relocation section
  for (int i = 0; i < shdrn->shnum; i++)
  {
    if (shdrn->shdr[i].sh_type == SHT_REL)
      ++nb_rel;
  }

  reln = calloc(nb_rel, sizeof(Elf32_Rel_named));

  int rel_idx = 0;
  for (int i = 0; i < shdrn->shnum; i++)
  {
    if (shdrn->shdr[i].sh_type == SHT_REL && rel_idx < nb_rel)
    {
      reln[rel_idx].rel_num = shdrn->shdr[i].sh_size / sizeof(Elf32_Rel);
      reln[rel_idx].info = shdrn->shdr[i].sh_info;

      //$ Allocation
      reln[rel_idx].names = calloc(reln[rel_idx].rel_num, sizeof(char *));
      reln[rel_idx].sym_val = calloc(reln[rel_idx].rel_num, sizeof(uint32_t));
      reln[rel_idx].rel = calloc(reln[rel_idx].rel_num, sizeof(Elf32_Rel));

      for (int j = 0; j < reln[rel_idx].rel_num; j++)
      {
        memcpy(&reln[rel_idx].rel[j], content + shdrn->shdr[i].sh_offset, sizeof(Elf32_Rel));

        //? endianess
        if (is_big_endian)
          rel_section_endianess(&reln[rel_idx].rel[j]);

        //$ Name association
        reln[rel_idx].names[j] = calloc(strlen(symn->names[ELF32_R_SYM(reln[rel_idx].rel[j].r_info)]) + 1, sizeof(char));
        strcpy(reln[rel_idx].names[j], symn->names[ELF32_R_SYM(reln[rel_idx].rel[j].r_info)]);

        //$ Value association
        reln[rel_idx].sym_val[j] = symn->sym[ELF32_R_SYM(reln[rel_idx].rel[j].r_info)].st_value;
      }
      ++rel_idx;
    }
  }
  return nb_rel;
}

void free_elf32_file(Elf32_file *elf)
{
  //$ Header
  free(elf->ehdr);
  elf->eh_size = 0;

  //$ Section headers
  for (int i = 0; i < elf->shdrn->shnum; i++)
    free(elf->shdrn->names[i]);
  free(elf->shdrn->names);
  free(elf->shdrn->shdr);
  elf->sh_size = 0;

  //$ Table of Symbols
  for (int i = 0; i < elf->symn->sym_num; i++)
    free(elf->symn->names[i]);
  free(elf->symn->names);
  free(elf->symn->sym);

  //$ Relocation Tables
  for (int i = 0; i < elf->nb_rel; i++)
  {
    for (int j = 0; j < elf->reln->rel_num; j++)
      free(elf->reln[i].names[j]);
    free(elf->reln[i].sym_val);
    free(elf->reln[i].names);
    free(elf->reln[i].rel);
  }

  // sections_list_destroyer(elf->section);
}

void storage_elf_content(char *content, Elf32_file *elf)
{
  //* HEADER STORAGE
  elf->ehdr = calloc(1, sizeof(Elf32_Ehdr));
  header_storage(content, elf->ehdr);

  if (elf->ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
    elf->big_endian = true;
  else
    elf->big_endian = false;

  header_endianess(elf->ehdr);
  elf->eh_size = elf->ehdr->e_ehsize;

  //* Not ELF file and only 32-bits

  if (memcmp(elf->ehdr->e_ident, ELFMAG, SELFMAG) != 0 || elf->ehdr->e_ident[EI_VERSION] != ELFCLASS32)
  {
    printf("Error: Not an ELF - it has the wrong magic bytes at the start\n");

    if (elf->ehdr->e_ident[EI_VERSION] != ELFCLASS32)
    {
      printf("Error: Invalid class\n");
    }
  }
  else
  {
    //* SECTION HEADER STORAGE
    elf->shdrn = calloc(1, sizeof(Elf32_Shdr_named));
    elf->shdrn->shnum = elf->ehdr->e_shnum;
    elf->sh_size = elf->ehdr->e_shentsize * elf->shdrn->shnum;
    section_headers_storage(content, elf->shdrn, elf->ehdr->e_shoff, elf->ehdr->e_shstrndx, elf->big_endian);

    //* SYMBOLS TABLE STORAGE
    elf->symn = calloc(1, sizeof(Elf32_Sym_named));
    elf->sym_size = sym_storage(content, elf->shdrn, elf->symn, elf->big_endian);

    init_section_content_storage(content, elf->shdrn, elf->section);

    elf->nb_rel = rel_storage(content, elf->shdrn, elf->symn, elf->reln, elf->nb_rel, elf->big_endian);

    free_elf32_file(elf);
  }
  free(content);
  free(elf->ehdr);
}