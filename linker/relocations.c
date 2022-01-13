#include "relocations.h"

int rel_link_section_finder(Elf32_Shdr_named *shdrn, int *offset)
{
  for (int i = *offset; i < shdrn->shnum; i++)
  {
    if (shdrn->shdr[i].sh_type == SHT_REL)
    {
      *offset = i;
      return shdrn->shdr[i].sh_info;
    }
  }
  return 0;
}

void relocations_execution(Elf32_file *elf)
{
  int rel_prev_header_index = 0, to_realoc = 0;
  uint32_t rel_offset, S, T;
  Elf32_stct_item *section;
  for (int i = 0; i < elf->nb_rel; i++)
  {
    rel_prev_header_index++;
    to_realoc = rel_link_section_finder(elf->shdrn, &rel_prev_header_index);
    for (int j = 0; j < elf->reln[i].rel_num; j++)
    {
      rel_offset = elf->reln[i].rel[j].r_offset;

      //$ S
      S = elf->reln[i].sym_val[j];

      //$ Section content
      section = finder_realoc(elf->sections_array, to_realoc);

      if (ELF32_R_TYPE(elf->reln[i].rel[j].r_info) == R_ARM_ABS32)
      {
        //$ T
        T = 0;
        if (ELF32_ST_TYPE(elf->symn->sym[ELF32_R_SYM(elf->reln[i].rel[j].r_info)].st_info) == STT_FUNC)
          T = 1;

        //$ Modification
        for (int k = 0; k < 4; k++)
          section->content[rel_offset + k] = (S | T) >> (4 * ((3 - k) * 2));
      }
      else if (ELF32_R_TYPE(elf->reln[i].rel[j].r_info) == R_ARM_JUMP24 || ELF32_R_TYPE(elf->reln[i].rel[j].r_info) == R_ARM_CALL)
      {
        //$ T
        T = 0;
        if (ELF32_ST_TYPE(elf->symn->sym[ELF32_R_SYM(elf->reln[i].rel[j].r_info)].st_info) == STT_FUNC)
          T = 1;

        //$ P
        uint32_t P = section->offset + rel_offset;

        //$ Modification
        for (int k = 0; k < 4; k++)
          section->content[rel_offset + k] = ((S | T) - P) >> (4 * ((3 - k) * 2));
      }
      else if (ELF32_R_TYPE(elf->reln[i].rel[j].r_info) == R_ARM_ABS16 || ELF32_R_TYPE(elf->reln[i].rel[j].r_info) == R_ARM_ABS8)
      {
        //$ Modification
        for (int k = 0; k < 4; k++)
          section->content[rel_offset + k] = S >> (4 * ((3 - k) * 2));
      }
    }
  }
}
