#include "display_header.h"

void header_print_magic(unsigned char *ident)
{
  header_print_isElfType(ident);
  printf("  Magic:\t");
  for (int i = 0; i < 16; i++)
  {
    printf("%.2x ", ident[i]);
  }
  printf("\n");
}

void header_print_isElfType(unsigned char *ident)
{
  if (is_ELF_header(ident))
    printf("ELF Header:\n");
  else
  {
    printf("Error: Not an ELF - it has the wrong magic bytes at the start\n");
    exit(EXIT_FAILURE);
  }
}

bool is_ELF_header(unsigned char *ident)
{
  // Check if the magic number of the file correponds to ELF identifier file
  return memcmp(ident, ELFMAG, SELFMAG) == 0;
}

void header_print_class(unsigned char *ident)
{
  switch (ident[EI_CLASS])
  {
  case ELFCLASS32:
    printf("  Class:\t\t\t\t");
    printf("ELF32\n");
    break;

  case ELFCLASS64:
    printf("  Class:\t\t\t\t");
    printf("ELF64\n");
    break;

  case ELFCLASSNONE:
    printf("Error: Invalid class\n");
    exit(EXIT_FAILURE);
    break;
  }
}

void header_print_data(unsigned char *ident)
{
  switch (ident[EI_DATA])
  {
  case ELFDATA2LSB:
    printf("  Data:\t\t\t\t\t");
    printf("Little-Endian\n");
    break;

  case ELFDATA2MSB:
    printf("  Data:\t\t\t\t\t");
    printf("Big-Endian\n");
    break;

  case ELFDATANONE:
    printf("Error: Unknown data format\n");
    exit(EXIT_FAILURE);
    break;
  }
}

void header_print_version_id(unsigned char *ident)
{
  switch (ident[EI_VERSION])
  {
  case EV_NONE:
    printf("Error : Invalid Version\n");
    exit(EXIT_FAILURE);
    break;

  case EV_CURRENT:
    printf("  Version:\t\t\t\t");
    printf("1 (current)\n");
    break;
  }
}

void header_print_os(unsigned char *ident)
{
  printf("  OS/ABI:\t\t\t\t");
  switch (ident[EI_OSABI])
  {
  case ELFOSABI_NONE | ELFOSABI_SYSV:
    printf("UNIX System V ABI\n");
    break;

  case ELFOSABI_HPUX:
    printf("HP-UX ABI\n");
    break;

  case ELFOSABI_NETBSD:
    printf("NetBSD ABI\n");
    break;

  case ELFOSABI_LINUX:
    printf("Linux ABI\n");
    break;

  case ELFOSABI_SOLARIS:
    printf("Solaris ABI\n");
    break;

  case ELFOSABI_IRIX:
    printf("IRIX ABI\n");
    break;

  case ELFOSABI_FREEBSD:
    printf("FreeBSD ABI\n");
    break;

  case ELFOSABI_TRU64:
    printf("TRU64 UNIX ABI\n");
    break;

  case ELFOSABI_ARM:
    printf("ARM architecture ABI\n");
    break;

  case ELFOSABI_STANDALONE:
    printf("Stand-alone (embedded) ABI\n");
    break;
  }
}

void header_print_abi_version(unsigned char *ident)
{
  printf("  ABI Version:\t\t\t\t");
  printf("%hx\n", ident[EI_ABIVERSION]);
}

void header_print_type(Elf32_Half type)
{
  printf("  Type:\t\t\t\t\t");
  switch (type)
  {
  case ET_REL:
    printf("A relocatable file\n");
    break;
  case ET_EXEC:
    printf("An executable file\n");
    break;
  case ET_DYN:
    printf("A shared object\n");
    break;
  case ET_CORE:
    printf("A core file\n");
    break;
  case ET_NONE:
    printf("An unknown type\n");
    break;

  default:
    printf("%01" PRIx32 "\n", type);
    break;
  }
}

void header_print_machine(Elf32_Half machine)
{
  printf("%hx", machine);
  printf("  Machine:\t\t\t\t");
  switch (machine)
  {
  case EM_M32:
    printf("AT&T WE 32100\n");
    break;

  case EM_SPARC:
    printf("Sun Microsystems SPARC\n");
    break;

  case EM_386:
    printf("Intel 80386\n");
    break;

  case EM_68K:
    printf("Motorola 68000\n");
    break;

  case EM_88K:
    printf("Motorola 88000\n");
    break;

  case EM_860:
    printf("Intel 80860\n");
    break;

  case EM_MIPS:
    printf("MIPS RS3000\n");
    break;

  case EM_PARISC:
    printf("HP/PA\n");
    break;

  case EM_SPARC32PLUS:
    printf("SPARC with enhanced instruction set\n");
    break;

  case EM_PPC:
    printf("PowerPC\n");
    break;

  case EM_PPC64:
    printf("PowerPC 64-bit\n");
    break;

  case EM_S390:
    printf("IBM S/390\n");
    break;

  case EM_ARM:
    printf("Advanced RISC Machines (ARM)\n");
    break;

  case EM_SH:
    printf("Renesas SuperH\n");
    break;

  case EM_SPARCV9:
    printf("SPARC v9 64-bit\n");
    break;

  case EM_IA_64:
    printf("Intel Itanium\n");
    break;

  case EM_X86_64:
    printf("AMD x86-64\n");
    break;

  case EM_VAX:
    printf("DEC Vax\n");
    break;

  case EM_NONE:
    printf("unknown machine\n");
    break;
  }
}

void header_print_version(Elf32_Word version)
{
  printf("  Version:\t\t\t\t");
  switch (version)
  {
  case EV_NONE:
    printf("0x0\n");
    break;
  case EV_CURRENT:
    printf("0x1\n");
    break;

  default:
    printf("%02" PRIx32 "\n", version);
    break;
  }
}

void header_print_adresse_offset(Elf32_Ehdr *ehdr)
{
  printf("  Entry point adress:\t\t\t");
  printf("0x%hx\n", ehdr->e_entry);

  printf("  Start of program headers:\t\t");
  printf("%d (bytes into file)\n", ehdr->e_phoff);

  printf("  Start of section headers:\t\t");
  printf("%hx (bytes into file)\n", ehdr->e_shoff);

  // print_flags(ehdr->e_flags);
  printf("  Flags: \t\t\t\t");
  printf("0x%x\n", ehdr->e_flags);

  printf("  Size of this header:\t\t\t");
  printf("%hx (bytes)\n", ehdr->e_ehsize);

  printf("  Size of program headers:\t\t");
  printf("%d (bytes)\n", ehdr->e_phentsize);

  printf("  Number of program headers:\t\t");
  printf("%d\n", ehdr->e_phnum);

  printf("  Size of section headers:\t\t");
  printf("%d (bytes)\n", ehdr->e_shentsize);

  printf("  Number of section headers:\t\t");
  printf("%hx\n", ehdr->e_shnum);

  printf("  Section header string table index:\t");
  printf("%hx\n", ehdr->e_shstrndx);
}

void print_entete(Elf32_Ehdr *ehdr)
{
  header_print_magic(ehdr->e_ident);
  header_print_class(ehdr->e_ident);
  header_print_data(ehdr->e_ident);
  header_print_version_id(ehdr->e_ident);
  header_print_os(ehdr->e_ident);
  header_print_abi_version(ehdr->e_ident);
  header_print_type(ehdr->e_type);
  header_print_machine(ehdr->e_machine);
  header_print_version(ehdr->e_version);
  header_print_adresse_offset(ehdr);
}