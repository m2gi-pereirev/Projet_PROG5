#include "display_section.h"

void section_print_number(int num)
{
    if(num < 10)
        printf(" [ %d]\t");
    else
        printf("[%d]\t");
}

void section_print_display_header()
{
    printf("\nSection Headers:\n");
    printf("  [Nr]\tName\t\tType\t\tAddr\toff\tSize\tES Flg Lk Inf Al\n");
}

void section_print_name(Elf32_Word name)
{
    printf("%d\t", name);
    // printf("%c\n", name);
}

void section_print_type(Elf32_Word type)
{
    switch (type)
    {
    case SHT_NULL:
        printf("NULL\t\t");
        break;
    case SHT_PROGBITS:
        printf("PROGBITS\t\t");
        break;
    case SHT_SYMTAB:
        printf("SYMTAB\t\t");
        break;
    case SHT_STRTAB:
        printf("STRTAB\t\t");
        break;
    case SHT_RELA:
        printf("RELA\t\t");
        break;
    case SHT_HASH:
        printf("HASH\t\t");
        break;
    case SHT_DYNAMIC:
        printf("DYNAMIC\t\t");
        break;
    case SHT_NOTE:
        printf("NOTE\t\t");
        break;
    case SHT_NOBITS:
        printf("NOBITS");
        break;
    case SHT_REL:
        printf("REL\t");
        break;
    case SHT_SHLIB:
        printf("SHLIB\t\t");
        break;
    case SHT_DYNSYM:
        printf("DYNSYM\t\t");
        break;
    case SHT_INIT_ARRAY:
        printf("INIT ARRAY\t");
        break;
    case SHT_FINI_ARRAY:
        printf("FINI_ARRAY\t");
        break;
    case SHT_PREINIT_ARRAY:
        printf("PREINIT_ARRAY\t");
        break;
    case SHT_GROUP:
        printf("GROUP\t\t");
        break;
    case SHT_SYMTAB_SHNDX:
        printf("SYMTAB_SHNDX");
        break;
    case SHT_NUM:
        printf("NUM\t\t");
        break;
    //! not finish

    default:
        break;
    }
}

void section_print_flags(Elf32_Word flags)
{
    printf("  Flags:\t");
    printf("%d\n", flags);
}

void section_print_decalage(Elf32_Off decalage)
{
    printf("  Décalage:\t");
    printf("0x%hx\n", decalage);
}

void affichage_section(Elf32_Shdr *shdr, int shnum)
{
    section_print_number(shnum);
    section_print_name(shdr->sh_name);
    section_print_type(shdr->sh_type);
    section_print_flags(shdr->sh_flags);
    section_print_decalage(shdr->sh_offset);
}