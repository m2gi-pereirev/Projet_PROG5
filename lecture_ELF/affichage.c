#include "affichage.h"

void print_type_name(char *type)
{
  printf("%s:\t\t\t\t\t\t", type);
}

void print_magic(unsigned char *ident)
{
  print_isElfType(ident);
  printf("Magic:\t");
  for (int i = 0; i < 16; i++)
  {
    printf("%.2x ", ident[i]);
  }
  printf("\n");
}

void print_isElfType(unsigned char *ident)
{
  if (is_ELF_header(ident))
    printf("En-tête du fichier ELF : \n");
  else
  {
    printf("Erreur ce fichier n'est pas au format ELF\n");
    exit(EXIT_FAILURE);
  }
}

bool is_ELF_header(unsigned char *ident)
{
  // Check if the magic number of the file correponds to ELF identifier file
  return (ident[EI_MAG0] == ELFMAG0 && ident[EI_MAG1] == ELFMAG1 && ident[EI_MAG2] == ELFMAG2 && ident[EI_MAG3] == ELFMAG3);
}

void print_class(unsigned char *ident)
{
  switch (ident[EI_CLASS])
  {
  case ELFCLASS32:
    print_type_name("Class");
    printf("ELF32\n");
    break;

  case ELFCLASS64:
    print_type_name("Class");
    printf("ELF64\n");
    break;

  case ELFCLASSNONE:
    printf("Error: Invalid class\n");
    exit(EXIT_FAILURE);
    break;
  }
}

void print_data(unsigned char *ident)
{
  switch (ident[EI_DATA])
  {
  case ELFDATA2LSB:
    print_type_name("Data");
    printf("Little-Endian\n");
    break;

  case ELFDATA2MSB:
    print_type_name("Data");
    printf("Big-Endian\n");
    break;

  case ELFDATANONE:
    printf("Error: Unknown data format\n");
    exit(EXIT_FAILURE);
    break;
  }
}

void print_version_id(unsigned char *ident)
{
  switch (ident[EI_VERSION])
  {
  case EV_NONE:
    printf("Error : Invalid Version\n");
    exit(EXIT_FAILURE);
    break;

  case EV_CURRENT:
    print_type_name("Version");
    printf("1 (current)\n");
    break;
  }
}

void print_os(unsigned char *ident)
{
  print_type_name("OS/ABI");
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

void print_abi_version(unsigned char *ident)
{
  print_type_name("ABI Version");
  printf("%hx\n", ident[EI_ABIVERSION]);
}

void print_type(Elf32_Half type)
{
  print_type_name("Type");
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
  }
}

void print_machine(Elf32_Half machine)
{
  switch (machine)
  {
  case EM_M32:
    print_type_name("Machine");
    printf("AT&T WE 32100\n");
    break;

  case EM_SPARC:
    print_type_name("Machine");
    printf("Sun Microsystems SPARC\n");
    break;

  case EM_386:
    print_type_name("Machine");
    printf("Intel 80386\n");
    break;

  case EM_68K:
    print_type_name("Machine");
    printf("Motorola 68000\n");
    break;

  case EM_88K:
    print_type_name("Machine");
    printf("Motorola 88000\n");
    break;

  case EM_860:
    print_type_name("Machine");
    printf("Intel 80860\n");
    break;

  case EM_MIPS:
    print_type_name("Machine");
    printf("MIPS RS3000\n");
    break;

  case EM_PARISC:
    print_type_name("Machine");
    printf("HP/PA\n");
    break;

  case EM_SPARC32PLUS:
    print_type_name("Machine");
    printf("SPARC with enhanced instruction set\n");
    break;

  case EM_PPC:
    print_type_name("Machine");
    printf("PowerPC\n");
    break;

  case EM_PPC64:
    print_type_name("Machine");
    printf("PowerPC 64-bit\n");
    break;

  case EM_S390:
    print_type_name("Machine");
    printf("IBM S/390\n");
    break;

  case EM_ARM:
    print_type_name("Machine");
    printf("Advanced RISC Machines (ARM)\n");
    break;

  case EM_SH:
    print_type_name("Machine");
    printf("Renesas SuperH\n");
    break;

  case EM_SPARCV9:
    print_type_name("Machine");
    printf("SPARC v9 64-bit\n");
    break;

  case EM_IA_64:
    print_type_name("Machine");
    printf("Intel Itanium\n");
    break;

  case EM_X86_64:
    print_type_name("Machine");
    printf("AMD x86-64\n");
    break;

  case EM_VAX:
    print_type_name("Machine");
    printf("DEC Vax\n");
    break;

  case EM_NONE:
    printf("Error: An unknown machine\n");
    exit(EXIT_FAILURE);
    break;
  }
}

void print_version(Elf32_Word version)
{
  print_type_name("Version");
  switch (version)
  {
  case EV_NONE:
    printf("0x0\n");
    break;
  case EV_CURRENT:
    printf("0x1\n");
    break;
  }
}

void print_adresse_offset(Elf32_Ehdr *ehdr)
{
  print_type_name("Entry point adress");
  printf("0x%hx\n", ehdr->e_entry);

  print_type_name("Start of program headers");
  printf("%hx (bytes into file)\n", ehdr->e_phoff);

  print_type_name("Start of section headers");
  printf("%hx (bytes into file)\n", ehdr->e_shoff);

  print_type_name("Flags");
  printf("%hx\n", ehdr->e_flags);

  print_type_name("Size of this header");
  printf("%hx(bytes)\n", ehdr->e_ehsize);

  print_type_name("Size of program headers");
  printf("%hx (bytes)\n", ehdr->e_phentsize);

  print_type_name("Number of program headers");
  printf("%d\n", ehdr->e_phnum);

  print_type_name("Size of section headers");
  printf("%hx (bytes)\n", ehdr->e_shentsize);

  print_type_name("Number of section headers");
  printf("%d\n", ehdr->e_shnum);

  print_type_name("Section header string table index");
  printf("%d\n", ehdr->e_shstrndx);
}

void affichage_entete(Elf32_Ehdr *ehdr)
{
  print_magic(ehdr->e_ident);
  print_class(ehdr->e_ident);
  print_data(ehdr->e_ident);
  print_version_id(ehdr->e_ident);
  print_os(ehdr->e_ident);
  print_abi_version(ehdr->e_ident);
  print_type(ehdr->e_type);
  print_machine(ehdr->e_machine);
  print_version(ehdr->e_version);
  print_adresse_offset(ehdr);
}
