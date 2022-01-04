#include "display_section.h"

void section_print_number(int num)
{
    if (num < 10)
        printf("  [ %d]\t", num);
    else
        printf("  [%d]\t", num);
}

void section_print_display_header()
{
    printf("\nSection Headers:\n");
    printf("  [Nr] Name               Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
}

void section_print_name(char *name)
{
    if (!name)
    {
        printf("                  ");
    }
    else if (strlen(name) > 17)
    {
        for (int i = 0; i < 12; i++)
            printf("%c", name[i]);
        printf("[...] ");
    }
    else
    {
        printf("%s", name);
        for (int i = 0; i < 18 - strlen(name); i++)
            printf(" ");
    }
}

void section_print_type(Elf32_Word type)
{
    switch (type)
    {
    case SHT_NULL:
        printf("NULL            ");
        break;
    case SHT_PROGBITS:
        printf("PROGBITS        ");
        break;
    case SHT_SYMTAB:
        printf("SYMTAB          ");
        break;
    case SHT_STRTAB:
        printf("STRTAB          ");
        break;
    case SHT_RELA:
        printf("RELA            ");
        break;
    case SHT_HASH:
        printf("HASH            ");
        break;
    case SHT_DYNAMIC:
        printf("DYNAMIC         ");
        break;
    case SHT_NOTE:
        printf("NOTE            ");
        break;
    case SHT_NOBITS:
        printf("NOBITS          ");
        break;
    case SHT_REL:
        printf("REL             ");
        break;
    case SHT_SHLIB:
        printf("SHLIB           ");
        break;
    case SHT_DYNSYM:
        printf("DYNSYM          ");
        break;
    case SHT_INIT_ARRAY:
        printf("INIT ARRAY      ");
        break;
    case SHT_FINI_ARRAY:
        printf("FINI_ARRAY      ");
        break;
    case SHT_PREINIT_ARRAY:
        printf("PREINIT_ARRAY   ");
        break;
    case SHT_GROUP:
        printf("GROUP           ");
        break;
    case SHT_SYMTAB_SHNDX:
        printf("SYMTAB_SHNDX    ");
        break;
    case SHT_NUM:
        printf("NUM             ");
        break;
    case SHT_LOOS:
        printf("LOOS            ");
        break;
    case SHT_GNU_ATTRIBUTES:
        printf("GNU ATTRIBUTE   ");
        break;
    case SHT_GNU_HASH:
        printf("GNU HASH        ");
        break;
    case SHT_GNU_LIBLIST:
        printf("GNU LISTLIB     ");
        break;
    case SHT_CHECKSUM:
        printf("CHECKSUM        ");
        break;
    case SHT_LOSUNW:
        printf("LOSUW           ");
        break;
    case SHT_SUNW_COMDAT:
        printf("SUNW COMDAT     ");
        break;
    case SHT_SUNW_syminfo:
        printf("SUNW syminfo    ");
        break;
    case SHT_GNU_verdef:
        printf("FNU verdef      ");
        break;
    case SHT_GNU_verneed:
        printf("GNU verneed     ");
        break;
    case SHT_GNU_versym:
        printf("GNU versym      ");
        break;
    case SHT_LOPROC:
        printf("LOPROC          ");
        break;
    case SHT_HIPROC:
        printf("HIPROC          ");
        break;
    case SHT_LOUSER:
        printf("LOUSER          ");
        break;
    case SHT_HIUSER:
        printf("HIUSER          ");
        break;
    default:
        printf("NONE            ");
        break;
    }
}

void section_print_flags(Elf32_Word flags)
{
    printf("    ");
/*     switch (flags)
    {
    case SHF_WRITE:
        printf("  W  ");
        break;
    case SHF_ALLOC:
        printf("  A  ");
        break;
    case SHF_EXECINSTR:
        printf("  X  ");
        break;
    case SHF_MERGE:
        printf("  M  ");
        break;
    case SHF_STRINGS:
        printf("  S  ");
        break;
    case SHF_INFO_LINK:
        printf("  I  ");
        break;
    case SHF_LINK_ORDER:
        printf("  L  ");
        break;
    case SHF_ORDERED:
        printf("  O  ");
        break;
    case SHF_GROUP:
        printf("  G  ");
        break;
    case SHF_TLS:
        printf("  T  ");
        break;
    case SHF_COMPRESSED:
        printf("  C  ");
        break;
    case SHF_MASKOS:
        printf("  o  ");
        break;
    case SHF_EXCLUDE:
        printf("  E  ");
        break;
    case SHF_MASKPROC:
        printf("  p  ");
        break;

    default:
        printf("     ");
        break;
    } */
}

void section_print_decalage(Elf32_Off decalage)
{
    printf("%06" PRIx32 " ", decalage);
}

void section_print_address(Elf32_Addr address)
{
    printf("%08" PRIx32 " ", address);
}

void section_print_size(Elf32_Word size)
{
    printf("%06" PRIx32 " ", size);
}

void section_print_entrysize(Elf32_Word entrysize)
{
    printf("%02" PRIx32 " ", entrysize);
}

void section_print_link(Elf32_Word link)
{
    if (link < 10)
        printf(" %d  ", link);
    else
        printf("%d  ", link);
}

void section_print_info(Elf32_Word info)
{
    if (info < 10)
        printf(" %d ", info);
    else
        printf("%d ", info);
}

void section_print_alignement(Elf32_Word align)
{
    if (align < 10)
        printf(" %d ", align);
    else
        printf("%d ", align);
}

void section_print_flag_key_info()
{
    printf("Flag key:\n");
    printf("  W (write), A (allocation), X (execution), M (merge), S (strings), I (info),\n");
    printf("  L (order of the links), O (additional processing by the OS required), G (group),\n");
    printf("  T (TLS), C (compressed), x (unknown), o (OS specific), E (excluded),\n");
    printf("  y (purecode), p (processor specific)\n");
}

void print_section_headers(Elf32_Shdr_named *shdr_named)
{
    // INIT DISPLAY
    section_print_display_header();

    // DISPLAY
    for (int i = 0; i < shdr_named->shnum; i++)
    {
        section_print_number(i);
        section_print_name(shdr_named->names[i]);
        section_print_type(shdr_named->shdr[i].sh_type);
        section_print_address(shdr_named->shdr[i].sh_addr);
        section_print_decalage(shdr_named->shdr[i].sh_offset);
        section_print_size(shdr_named->shdr[i].sh_size);
        section_print_entrysize(shdr_named->shdr[i].sh_entsize);
        section_print_flags(shdr_named->shdr[i].sh_flags);
        section_print_link(shdr_named->shdr[i].sh_link);
        section_print_info(shdr_named->shdr[i].sh_info);
        section_print_alignement(shdr_named->shdr[i].sh_addralign);
        printf("\n");
    }
    section_print_flag_key_info();
}