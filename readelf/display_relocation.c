#include "display_relocation.h"

void print_relocation_header(char *name, Elf32_Off offset, int nb_entry)
{
  if (nb_entry == 1)
    printf("\nRelocation section '%s' at offset 0x%hx contains %d entry:\n", name, offset, nb_entry);
  else
    printf("\nRelocation section '%s' at offset 0x%hx contains %d entries:\n", name, offset, nb_entry);

}

void print_relocation_table_header(bool rel)
{
  if (rel)
    printf(" Offset      Info    Type            Sym.Value  Sym. Name\n");
  else
    printf(" Offset      Info    Type            Sym.Value  Sym. Name + Addend\n");
}

void print_rel_offset(Elf32_Addr offset)
{
  printf("%08x  ", offset);
}

void print_rel_info(Elf32_Word info)
{
  printf("%08x ", info);
}

void print_rel_type(Elf32_Word info)
{
  switch (ELF32_R_TYPE(info))
  {
  case R_ARM_NONE:
    printf("R_ARM_NONE         ");
    break;
  case R_ARM_PC24:
    printf("R_ARM_PC24         ");
    break;
  case R_ARM_ABS32:
    printf("R_ARM_ABS32        ");
    break;
  case R_ARM_REL32:
    printf("R_ARM_REL32        ");
    break;
  case R_ARM_PC13:
    printf("R_ARM_PC13         ");
    break;
  case R_ARM_ABS16:
    printf("R_ARM_ABS16        ");
    break;
  case R_ARM_ABS12:
    printf("R_ARM_ABS12        ");
    break;
  case R_ARM_THM_ABS5:
    printf("R_ARM_THM_ABS5     ");
    break;
  case R_ARM_ABS8:
    printf("R_ARM_ABS8         ");
    break;
  case R_ARM_SBREL32:
    printf("R_ARM_SBREL32      ");
    break;
  case R_ARM_THM_PC22:
    printf("R_ARM_THM_PC22     ");
    break;
  case R_ARM_THM_PC8:
    printf("R_ARM_THM_PC8      ");
    break;
  case R_ARM_AMP_VCALL9:
    printf("R_ARM_AMP_VCALL9   ");
    break;
  case R_ARM_SWI24:
    printf("R_ARM_SWI24        ");
    break;
  case R_ARM_THM_SWI8:
    printf("R_ARM_THM_SWI8     ");
    break;
  case R_ARM_XPC25:
    printf("R_ARM_XPC25        ");
    break;
  case R_ARM_THM_XPC22:
    printf("R_ARM_THM_XPC22    ");
    break;
  case R_ARM_COPY:
    printf("R_ARM_COPY         ");
    break;
  case R_ARM_GLOB_DAT:
    printf("R_ARM_GLOB_DAT     ");
    break;
  case R_ARM_JUMP_SLOT:
    printf("R_ARM_JUMP_SLOT    ");
    break;
  case R_ARM_RELATIVE:
    printf("R_ARM_RELATIVE     ");
    break;
  case R_ARM_GOTOFF:
    printf("R_ARM_GOTOFF       ");
    break;
  case R_ARM_GOTPC:
    printf("R_ARM_GOTPC        ");
    break;
  case R_ARM_GOT32:
    printf("R_ARM_GOT32        ");
    break;
  case R_ARM_PLT32:
    printf("R_ARM_PLT32        ");
    break;
  case R_ARM_CALL:
    printf("R_ARM_CALL         ");
    break;
  case R_ARM_JUMP24:
    printf("R_ARM_JUMP24       ");
    break;
  case R_ARM_THM_JUMP24:
    printf("R_ARM_THM_JUMP24   ");
    break;
  case R_ARM_BASE_ABS:
    printf("R_ARM_BASE_ABS     ");
    break;
  case R_ARM_TARGET1:
    printf("R_ARM_TARGET1      ");
    break;
  case R_ARM_SBREL31:
    printf("R_ARM_SBREL31      ");
    break;
  case R_ARM_V4BX:
    printf("R_ARM_V4BX         ");
    break;
  case R_ARM_TARGET2:
    printf("R_ARM_TARGET2      ");
    break;
  case R_ARM_PREL31:
    printf("R_ARM_PREL31       ");
    break;
  case R_ARM_MOVT_ABS:
    printf("R_ARM_MOVT_ABS     ");
    break;
  case R_ARM_MOVT_PREL:
    printf("R_ARM_MOVT_PREL    ");
    break;
  case R_ARM_THM_JUMP19:
    printf("R_ARM_THM_JUMP19   ");
    break;
  case R_ARM_THM_JUMP6:
    printf("R_ARM_THM_JUMP6    ");
    break;
  case R_ARM_THM_PC12:
    printf("R_ARM_THM_PC12     ");
    break;
  case R_ARM_ABS32_NOI:
    printf("R_ARM_ABS32_NOI    ");
    break;
  case R_ARM_REL32_NOI:
    printf("R_ARM_REL32_NOI    ");
    break;
  case R_ARM_ALU_PC_G0:
    printf("R_ARM_ALU_PC_G0    ");
    break;
  case R_ARM_ALU_PC_G1:
    printf("R_ARM_ALU_PC_G1    ");
    break;
  case R_ARM_ALU_PC_G2:
    printf("R_ARM_ALU_PC_G2    ");
    break;
  case R_ARM_LDR_PC_G1:
    printf("R_ARM_LDR_PC_G1    ");
    break;
  case R_ARM_LDR_PC_G2:
    printf("R_ARM_LDR_PC_G2    ");
    break;
  case R_ARM_LDRS_PC_G0:
    printf("R_ARM_LDRS_PC_G0   ");
    break;
  case R_ARM_LDRS_PC_G1:
    printf("R_ARM_LDRS_PC_G1   ");
    break;
  case R_ARM_LDRS_PC_G2:
    printf("R_ARM_LDRS_PC_G2   ");
    break;
  case R_ARM_LDC_PC_G0:
    printf("R_ARM_LDC_PC_G0    ");
    break;
  case R_ARM_LDC_PC_G1:
    printf("R_ARM_LDC_PC_G1    ");
    break;
  case R_ARM_LDC_PC_G2:
    printf("R_ARM_LDC_PC_G2    ");
    break;
  case R_ARM_ALU_SB_G0:
    printf("R_ARM_ALU_SB_G0    ");
    break;
  case R_ARM_ALU_SB_G1:
    printf("R_ARM_ALU_SB_G1    ");
    break;
  case R_ARM_ALU_SB_G2:
    printf("R_ARM_ALU_SB_G2    ");
    break;
  case R_ARM_LDR_SB_G0:
    printf("R_ARM_LDR_SB_G0    ");
    break;
  case R_ARM_LDR_SB_G1:
    printf("R_ARM_LDR_SB_G1    ");
    break;
  case R_ARM_LDR_SB_G2:
    printf("R_ARM_LDR_SB_G2    ");
    break;
  case R_ARM_LDRS_SB_G0:
    printf("R_ARM_LDRS_SB_G0   ");
    break;
  case R_ARM_LDRS_SB_G1:
    printf("R_ARM_LDRS_SB_G1   ");
    break;
  case R_ARM_LDRS_SB_G2:
    printf("R_ARM_LDRS_SB_G2   ");
    break;
  case R_ARM_LDC_SB_G0:
    printf("R_ARM_LDC_SB_G0    ");
    break;
  case R_ARM_LDC_SB_G1:
    printf("R_ARM_LDC_SB_G1    ");
    break;
  case R_ARM_LDC_SB_G2:
    printf("R_ARM_LDC_SB_G2    ");
    break;
  case R_ARM_MOVT_BREL:
    printf("R_ARM_MOVT_BREL    ");
    break;
  case R_ARM_MOVW_BREL:
    printf("R_ARM_MOVW_BREL    ");
    break;
  case R_ARM_TLS_CALL:
    printf("R_ARM_TLS_CALL     ");
    break;
  case R_ARM_PLT32_ABS:
    printf("R_ARM_PLT32_ABS    ");
    break;
  case R_ARM_GOT_ABS:
    printf("R_ARM_GOT_ABS      ");
    break;
  case R_ARM_GOT_PREL:
    printf("R_ARM_GOT_PREL     ");
    break;
  case R_ARM_GOT_BREL12:
    printf("R_ARM_GOT_BREL12   ");
    break;
  case R_ARM_GOTOFF12:
    printf("R_ARM_GOTOFF12     ");
    break;
  case R_ARM_GOTRELAX:
    printf("R_ARM_GOTRELAX     ");
    break;
  case R_ARM_THM_PC11:
    printf("R_ARM_THM_PC11     ");
    break;
  case R_ARM_THM_PC9:
    printf("R_ARM_THM_PC9      ");
    break;
  case R_ARM_TLS_GD32:
    printf("R_ARM_TLS_GD32     ");
    break;
  case R_ARM_TLS_LDM32:
    printf("R_ARM_TLS_LDM32    ");
    break;
  case R_ARM_TLS_LDO32:
    printf("R_ARM_TLS_LDO32    ");
    break;
  case R_ARM_TLS_IE32:
    printf("R_ARM_TLS_IE32     ");
    break;
  case R_ARM_TLS_LE32:
    printf("R_ARM_TLS_LE32     ");
    break;
  case R_ARM_TLS_LDO12:
    printf("R_ARM_TLS_LDO12    ");
    break;
  case R_ARM_TLS_LE12:
    printf("R_ARM_TLS_LE12     ");
    break;
  case R_ARM_TLS_IE12GP:
    printf("R_ARM_TLS_IE12GP   ");
    break;
  case R_ARM_ME_TOO:
    printf("R_ARM_ME_TOO       ");
    break;
  case R_ARM_IRELATIVE:
    printf("R_ARM_IRELATIVE    ");
    break;
  case R_ARM_RXPC25:
    printf("R_ARM_RXPC25       ");
    break;
  case R_ARM_RSBREL32:
    printf("R_ARM_RSBREL32     ");
    break;
  case R_ARM_THM_RPC22:
    printf("R_ARM_THM_RPC22    ");
    break;
  case R_ARM_RREL32:
    printf("R_ARM_RREL32       ");
    break;
  case R_ARM_RABS22:
    printf("R_ARM_RABS22       ");
    break;
  case R_ARM_RPC24:
    printf("R_ARM_RPC24        ");
    break;
  case R_ARM_RBASE:
    printf("R_ARM_RBASE        ");
    break;
  case R_ARM_NUM:
    printf("R_ARM_NUM          ");
    break;

  default:
    break;
  }
}

void print_rel_sym_value(uint32_t val)
{
  printf("%08x   ", val);
}

void print_rel_sym_name(char *name)
{
  printf("%s\n", name);
}

void print_rela_sym_name(char *name, Elf32_Sword addend)
{
  printf("%s ", name);
  if (addend >=0)
    printf("+ %" PRId32 "\n", addend);
  else
    printf("- %" PRId32 "\n", addend);
}

void print_relocation_section(Elf32_Rel_named *rel_named, Elf32_Off offset, char *rel_name)
{
  print_relocation_header(rel_name, offset, rel_named->rel_num);
  print_relocation_table_header(rel_named->rel_type);
  if (rel_named->rel_type)
  {
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      print_rel_offset(rel_named->rel[i].r_offset);
      print_rel_info(rel_named->rel[i].r_info);
      print_rel_type(rel_named->rel[i].r_info);
      print_rel_sym_value(rel_named->sym_val[i]);
      print_rel_sym_name(rel_named->names[i]);
    }
  }
  else
  {
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      print_rel_offset(rel_named->rela[i].r_offset);
      print_rel_info(rel_named->rela[i].r_info);
      print_rel_type(rel_named->rela[i].r_info);
      print_rel_sym_value(rel_named->sym_val[i]);
      print_rela_sym_name(rel_named->names[i], rel_named->rela[i].r_addend);
    }
  }
}