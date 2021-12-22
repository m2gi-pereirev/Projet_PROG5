#include "display_section.h"

void section_print_number(int num)
{
    if(num < 10)
        printf("  [ %d]\t", num);
    else
        printf("  [%d]\t", num);
}

void section_print_display_header()
{   
    printf("\n");
    printf("\nSection Headers:\n");
    printf("  [Nr]\tName\t\tType\t\tAddr\toff\tSize\tES Flg\tLk Inf Al\n");
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
    case SHT_LOOS:
        printf("LOOS\t\t");
        break;
    case SHT_GNU_ATTRIBUTES:
        printf("GNU ATTRIBUTE\t");
        break;
    case SHT_GNU_HASH:
        printf("GNU HASH\t\t");
        break;
    case SHT_GNU_LIBLIST:
        printf("GNU LISTLIB\t");
        break;
    case SHT_CHECKSUM:
        printf("CHECKSUM\t\t");
        break;
    case SHT_LOSUNW:
        printf("LOSUW\t\t");
        break;
    case SHT_SUNW_COMDAT:
        printf("SUNW COMDAT\t\t");
        break;
    case SHT_SUNW_syminfo:
        printf("SUNW syminfo\t");
        break;
    case SHT_GNU_verdef:
        printf("FNU verdef\t");
        break;
    case SHT_GNU_verneed:
        printf("GNU verneed\t");
        break;
    case SHT_GNU_versym:
        printf("GNU versym\t");
        break;
    case SHT_LOPROC:
        printf("LOPROC\t\t");
        break;
    case SHT_HIPROC:
        printf("HIPROC\t\t");
        break;
    case SHT_LOUSER:
        printf("LOUSER\t\t");
        break;
    case SHT_HIUSER:
        printf("HIUSER\t\t");
        break;

    default:
        break;
    }
}

void section_print_flags(Elf32_Word flags)
{
    switch (flags)
    {
    case SHF_WRITE:
        printf("WRITE");
        break;
    case SHF_ALLOC:
        printf("ALLOC\t");
        break;
    case SHF_EXECINSTR:
        printf("INSTR\t");
        break;
    case SHF_MERGE:
        printf("MERGE\t");
        break;
    case SHF_STRINGS:
        printf("STR\t");
        break;
    case SHF_INFO_LINK:
        printf("IFLK\t");
        break;
    case SHF_LINK_ORDER:
        printf("LKO\t");
        break;
    case SHF_OS_NONCONFORMING:
        printf("N_OS\t");
        break;
    case SHF_GROUP:
        printf("GRP\t");
        break;
    case SHF_TLS:
        printf("TLS\t");
        break;
    case SHF_COMPRESSED:
        printf("COMP\t");
        break;
    case SHF_MASKOS:
        printf("MSKOS\t");
        break;
    case SHF_MASKPROC:
        printf("MSKPROC\t");
        break;
    /*case SHF_GNU_RETAIN:
        printf("RETAIN\t");
        break;*/
    case SHF_ORDERED:
        printf("ORD\t");
        break;
    case SHF_EXCLUDE:
        printf("EXCLD\t");
        break;

    default:
        break;
    }
}

void section_print_decalage(Elf32_Off decalage)
{
    printf("%06" PRIX32 "\t", decalage);
}

void section_print_address(Elf32_Addr address)
{
    printf("%06" PRIX32 "\t", address);
}

void section_print_size(Elf32_Word size)
{
    printf("%06" PRIX32 "\t", size);
}

void section_print_entrysize(Elf32_Word entrysize)
{
    printf("%02" PRIX32 "\t", entrysize);
}

void section_print_link(Elf32_Word link)
{
    printf("%hx", link);
}

void section_print_info(Elf32_Word info)
{
    printf("%hx", info);
}

void section_print_alignement(Elf32_Word align)
{
    printf("%hx", align);
}

void section_print_flag_key_info()
{
    printf("\nFlag key:\n"); 
    printf("  W (write), A (allocation), X (execution), M (merge), S (strings), I (info),\n");
    printf("  L (order of the links), O (additional processing by the OS required), G (group),\n");
    printf("  T (TLS), C (compressed), x (unknown), o (OS specific), E (excluded),\n");
    printf("  y (purecode), p (processor specific)\n");
}

void print_section(Elf32_Shdr *shdr, int shnum)
{
    section_print_number(shnum);
    section_print_name(shdr[shnum].sh_name);
    section_print_type(shdr[shnum].sh_type);
    section_print_address(shdr[shnum].sh_addr);
    section_print_decalage(shdr[shnum].sh_offset);
    section_print_size(shdr[shnum].sh_size);
    section_print_entrysize(shdr[shnum].sh_entsize);
    section_print_flags(shdr[shnum].sh_flags);
    section_print_link(shdr[shnum].sh_link);
    section_print_info(shdr[shnum].sh_info);
    section_print_alignement(shdr[shnum].sh_addralign);
    printf("\n");
}