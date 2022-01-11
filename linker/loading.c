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
  free(Section_names);
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
    free(Sym_names);
    return shdrn->shdr[sym_idx].sh_size;
  }
  return -1;
}

bool is_section_code(Elf32_Shdr_named *shdrn, int i)
{
  return (shdrn->shdr[i].sh_type != SHT_NULL && shdrn->shdr[i].sh_type != SHT_REL && shdrn->shdr[i].sh_type != SHT_SYMTAB && shdrn->shdr[i].sh_type != SHT_STRTAB);
}

Elf32_stct_list section_content_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_stct_list cargo)
{
  for (int i = 0; i < shdrn->shnum; i++)
  {
    if (is_section_code(shdrn, i))
    {
      cargo = section_container_adder(cargo, content + shdrn->shdr[(i)].sh_offset, shdrn->names[(i)], i, shdrn->shdr[(i)].sh_size);
    }
  }
  return cargo;
}

Elf32_Rel_named *rel_storage(char *content, Elf32_Shdr_named *shdrn, Elf32_Sym_named *symn, int *nb_rel, bool is_big_endian)
{
  Elf32_Rel_named *reln = NULL;
  *nb_rel = 0;
  int rel_idx = 0;

  // Get number of relocation section
  for (int i = 0; i < shdrn->shnum; i++)
  {
    if (shdrn->shdr[i].sh_type == SHT_REL)
      ++(*nb_rel);
  }

  if (*nb_rel > 0)
  {
    reln = calloc(*nb_rel, sizeof(Elf32_Rel_named));

    for (int i = 0; i < shdrn->shnum; i++)
    {
      if (shdrn->shdr[i].sh_type == SHT_REL)
      {
        reln[rel_idx].rel_num = shdrn->shdr[i].sh_size / sizeof(Elf32_Rel);

        //$ Allocation
        reln[rel_idx].names = calloc(reln[rel_idx].rel_num, sizeof(char *));
        reln[rel_idx].sym_val = calloc(reln[rel_idx].rel_num, sizeof(uint32_t));
        reln[rel_idx].rel = calloc(reln[rel_idx].rel_num, sizeof(Elf32_Rel));

        for (int j = 0; j < reln[rel_idx].rel_num; j++)
        {
          memcpy(&reln[rel_idx].rel[j], content + shdrn->shdr[i].sh_offset, sizeof(Elf32_Rel));

          if (is_big_endian)
            rel_section_endianess(&reln[rel_idx].rel[j]);

          unsigned rel_info = ELF32_R_SYM(reln[rel_idx].rel[j].r_info);

          //$ Name association
          reln[rel_idx].names[j] = calloc(strlen(symn->names[rel_info]) + 1, sizeof(char));
          strcpy(reln[rel_idx].names[j], symn->names[rel_info]);

          //$ Value association
          reln[rel_idx].sym_val[j] = symn->sym[rel_info].st_value;
        }
        ++rel_idx;
      }
    }
  }
  return reln;
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
  free(elf->shdrn);
  elf->sh_size = 0;

  //$ Table of Symbols
  for (int i = 0; i < elf->symn->sym_num; i++)
    free(elf->symn->names[i]);
  free(elf->symn->names);
  free(elf->symn->sym);
  free(elf->symn);

  //$ Relocation Tables
  for (int i = 0; i < elf->nb_rel; i++)
  {
    for (int j = 0; j < elf->reln[i].rel_num; j++)
      free(elf->reln[i].names[j]);
    free(elf->reln[i].sym_val);
    free(elf->reln[i].names);
    free(elf->reln[i].rel);
  }
  free(elf->reln);

  //$ Sections content
  sections_list_destroyer(elf->sections_array);
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

  if (!(memcmp(elf->ehdr->e_ident, ELFMAG, SELFMAG) == 0))
  {
    printf("Error: Not an ELF - it has the wrong magic bytes at the start\n");
  }
  else if (elf->ehdr->e_ident[EI_CLASS] != ELFCLASS32)
  {
    printf("Error: linker does not support 64-bit ELF files\n");
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

    //* SECTION CONTENT STORAGE
    elf->sections_array = NULL;
    elf->sections_array = section_content_storage(content, elf->shdrn, elf->sections_array);

    //* RELOCATION SECTION STORAGE
    elf->reln = rel_storage(content, elf->shdrn, elf->symn, &elf->nb_rel, elf->big_endian);

    //! Leaks of memory
    free_elf32_file(elf);
  }
  free(content);
}