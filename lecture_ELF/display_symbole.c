#include "display_symbole.h"

void symb_print_name(char *name)
{
    if (name == NULL)
        printf("\n");
    else
        printf("%s\n", name);
}

void symb_print_value(Elf32_Addr st_value)
{
    printf("%08x  ", st_value);
}

void symb_print_size(uint32_t st_size)
{
    if (st_size < 10)
        printf("   %d ", st_size);
    else if (st_size < 100)
        printf("    %d ", st_size);
    else
        printf("   %d ", st_size);
}

void symb_print_info(unsigned char st_info)
{
    // TYPE
    switch (ELF32_ST_TYPE(st_info))
    {
    case STT_NOTYPE:
        printf("NOTYPE  ");
        break;
    case STT_OBJECT:
        printf("OBJECT  ");
        break;
    case STT_FUNC:
        printf("FUNC    ");
        break;
    case STT_SECTION:
        printf("SECTION ");
        break;
    case STT_FILE:
        printf("FILE    ");
        break;
    case STT_LOPROC:
        printf("LOPROC  ");
        break;
    case STT_HIPROC:
        printf("HIPROC  ");
        break;
    default:
        printf("NONE    ");
        break;
    }
    // BIND
    switch (ELF32_ST_BIND(st_info))
    {
    case STB_LOCAL:
        printf("LOCAL  ");
        break;
    case STB_GLOBAL:
        printf("GLOBAL ");
        break;
    case STB_WEAK:
        printf("WEAK   ");
        break;
    case STB_NUM:
        printf("NUM    ");
        break;
    case STB_LOOS:
        printf("LOOS   ");
        break;
    case STB_HIOS:
        printf("HIOS   ");
        break;
    case STB_LOPROC:
        printf("LOPROC ");
        break;
    case STB_HIPROC:
        printf("HIPROC");
        break;

    default:
        break;
    }
}

void symb_print_other(unsigned char st_other)
{
    switch (ELF32_ST_VISIBILITY(st_other))
    {
    case STV_DEFAULT:
        printf("DEFAULT  ");
        break;
    case STV_INTERNAL:
        printf("INTERNAL ");
        break;
    case STV_HIDDEN:
        printf("HIDDEN   ");
        break;
    case STV_PROTECTED:
        printf("PROTECTED");
        break;

    default:
        break;
    }
}

void symb_print_shndx(uint16_t st_shndx)
{
    if (st_shndx == 0)
        printf("UND ");
    else if (st_shndx < 10)
        printf("  %d ", st_shndx);
    else if (st_shndx < 100)
        printf(" %d ", st_shndx);
    else if (st_shndx < 1000)
        printf("%d ", st_shndx);
}

void print_symb_tab_Sym_head()
{
    printf("   Num:    Value  Size Type    Bind   Vis      Ndx Name\n");
}

void symbole_print_number(int i)
{
    if (i < 10)
    {
        printf("     %d: ", i);
    }
    else if (i < 100)
    {
        printf("    %d: ", i);
    }
    else
    {
        printf("   %d: ", i);
    }
}

void print_table_sym(Elf32_Sym_named *sym_named)
{
    // INIT DISPLAY
    print_symb_tab_Sym_head();

    // DISPLAY
    for (int i = 0; i < sym_named->sym_num; i++)
    {
        symbole_print_number(i);
        symb_print_value(sym_named->sym[i].st_value);
        symb_print_size(sym_named->sym[i].st_size);
        symb_print_info(sym_named->sym[i].st_info);
        symb_print_other(sym_named->sym[i].st_other);
        symb_print_shndx(sym_named->sym[i].st_shndx);
        symb_print_name(sym_named->names[i]);
    }
}