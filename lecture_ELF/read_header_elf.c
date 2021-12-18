#include "read_header_elf.h"

// #define DEBUG

//Header Filling
void header_read(Elf32_Ehdr *ehdr)
{
  for (int i = 0; i < 16; i++)
    ehdr->e_ident[i] = bitread(sizeof(unsigned char));
  ehdr->e_type = bitread(sizeof(ehdr->e_type));
  ehdr->e_machine = bitread(sizeof(ehdr->e_machine));
  ehdr->e_version = bitread(sizeof(ehdr->e_version));
  ehdr->e_entry = bitread(sizeof(ehdr->e_entry));
  ehdr->e_phoff = bitread(sizeof(ehdr->e_phoff));
  ehdr->e_shoff = bitread(sizeof(ehdr->e_shoff));
  ehdr->e_flags = bitread(sizeof(ehdr->e_flags));
  ehdr->e_ehsize = bitread(sizeof(ehdr->e_ehsize));
  ehdr->e_phentsize = bitread(sizeof(ehdr->e_phentsize));
  ehdr->e_phnum = bitread(sizeof(ehdr->e_phnum));
  ehdr->e_shentsize = bitread(sizeof(ehdr->e_shentsize));
  ehdr->e_shnum = bitread(sizeof(ehdr->e_shnum));
  ehdr->e_shstrndx = bitread(sizeof(ehdr->e_shstrndx));
}


// Return if the file is ELF or not
bool is_magic_number(Elf32_Ehdr *ehdr)
{
#ifdef DEBUG
  fprintf(stderr, "%s\n", ehdr->e_ident);
#endif
  return ehdr->e_ident[0] == ELFMAG0 || ehdr->e_ident[1] == ELFMAG1 || ehdr->e_ident[2] == ELFMAG2 || ehdr->e_ident[3] == ELFMAG3; // Check if the magic number of the file correponds to ELF identifier file
}




int main(int argc, char const *argv[])
{
  Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));

  if (argc > 1){
    bitopen(argv[1]);
  } else{
    fprintf(stderr, "Error : only one possible argument\n");
    return -1;
  }

  header_read(ehdr); // Reading the header

//Affichage de l'entete ELF complete

  if (is_magic_number(ehdr)){
    printf("Entete du fichier ELF : \n");

//--------------------------MAGIC-----------------------------//
   
   printf(" Magic:\t");
   for(int i=0; i<16; i++){
     printf("%.2x ", ehdr->e_ident[i]);
   }

//--------------------------CLASS-----------------------------//
   
   printf("\n Class :\t");
   switch(ehdr->e_ident[EI_CLASS]){
    case ELFCLASS32:
       printf("ELF32");
       break;
    case ELFCLASS64:
       printf("ELF64");
       break;
    case ELFCLASSNONE:
       printf("Invalid class");
       break;
   }

//--------------------------DATA------------------------------//
   
   printf("\n Data :\t");
   switch(ehdr->e_ident[EI_DATA]){
    case ELFDATA2LSB:
       printf("Little-Endian");
       break;
    case ELFDATA2MSB:
       printf("Big-Endian");
       break;
    case ELFDATANONE:
       printf("Unknown data format");
       break;
   }

//--------------------------Version------------------------------//
   
   printf("\n Data :\t");
   switch(ehdr->e_ident[EI_VERSION]){
    case EV_NONE:
       printf("0 (Invalid Version)");
       break;
    case EV_CURRENT:
       printf("1 (current)");
       break;
   }

//--------------------------OS/ABI------------------------------//
   
   printf("\n OS/ABI :\t");
   switch(ehdr->e_ident[EI_OSABI]){
    case ELFOSABI_NONE | ELFOSABI_SYSV:
       printf("UNIX System V ABI");
       break;
    case ELFOSABI_HPUX:
       printf("HP-UX ABI");
       break;
    case ELFOSABI_NETBSD:
       printf("NetBSD ABI");
       break;
    case ELFOSABI_LINUX:
       printf("Linux ABI");
       break;
    case ELFOSABI_SOLARIS:
       printf("Solaris ABI");
       break;
    case ELFOSABI_IRIX:
       printf("IRIX ABI");
       break;
    case ELFOSABI_FREEBSD:
       printf("FreeBSD ABI");
       break;
    case ELFOSABI_TRU64:
       printf("TRU64 UNIX ABI");
       break;
    case ELFOSABI_ARM:
       printf("ARM architecture ABI");
       break;
    case ELFOSABI_STANDALONE:
       printf("Stand-alone (embedded) ABI");
       break;
   }

//--------------------------ABI VERSION-----------------------//
   
   printf("\n ABI Version :\t");
   printf("%hx",ehdr->e_ident[EI_ABIVERSION]);

//--------------------------TYPE------------------------------//

   printf("\n Type :\t");
    switch(ehdr->e_type){
      case ET_REL :
        printf("A relocatable file ");
        break;
      case ET_EXEC :
        printf("An executable file ");
        break;
      case ET_DYN :
        printf("A shared object ");
        break;
      case ET_CORE :
        printf("A core file ");
        break;
      case ET_NONE :
        printf("An unknown type ");
        break;
    }

//--------------------------MACHINE----------------------------//

  printf("\n Machine :\t");
    switch(ehdr->e_machine){
      case EM_M32 :
        printf("AT&T WE 32100 ");
        break;
      case EM_SPARC :
        printf("Sun Microsystems SPARC ");
        break;
      case EM_386 :
        printf("Intel 80386 ");
        break;
      case EM_68K :
        printf("Motorola 68000 ");
        break;
      case EM_88K :
        printf("Motorola 88000 ");
        break;
      case EM_860 :
        printf("Intel 80860 ");
        break;
      case EM_MIPS :
        printf("MIPS RS3000 ");
        break;
      case EM_PARISC :
        printf("HP/PA ");
        break;
      case EM_SPARC32PLUS :
        printf("SPARC with enhanced instruction set ");
        break;
      case EM_PPC :
        printf("PowerPC ");
        break;
      case EM_PPC64 :
        printf("PowerPC 64-bit ");
        break;
      case EM_S390 :
        printf("IBM S/390 ");
        break;
      case EM_ARM :
        printf("Advanced RISC Machines (ARM) ");
        break;
      case EM_SH :
        printf("Renesas SuperH ");
        break;
      case EM_SPARCV9 :
        printf("SPARC v9 64-bit ");
        break;
      case EM_IA_64:
        printf("Intel Itanium ");
        break;
      case EM_X86_64 :
        printf("AMD x86-64 ");
        break;
      case EM_VAX:
        printf("DEC Vax ");
        break;
      case EM_NONE:
        printf("An unknown machine");
        break;
    }

//--------------------------VERSION------------------------------//

   printf("\n Version :\t");
    switch(ehdr->e_version){
      case EV_NONE :
        printf("0x0 ");
        break;
      case EV_CURRENT :
        printf("0x1 ");
        break;
    }

//--------------------------ADRESS AND OFFSET--------------------//
    
    printf("\n Entry point adress :\t");
    printf("0x%hx",ehdr->e_entry);

    printf("\n Start of program headers :\t");
    printf("%hx (bytes into file)",ehdr->e_phoff);

    printf("\n Start of section headers :\t");
    printf("%hx (bytes into file)",ehdr->e_shoff);

    printf("\n Flags :\t");
    printf("%hx",ehdr->e_flags);

    printf("\n Size of this header :\t");
    printf("%hx (bytes)",ehdr->e_ehsize);

    printf("\n Size of program headers :\t");
    printf("%hx (bytes)",ehdr->e_phentsize);

    printf("\n Number of program headers :\t");
    printf("%d",ehdr->e_phnum);

    printf("\n Size of section headers :\t");
    printf("%hx (bytes)",ehdr->e_shentsize);

    printf("\n Number of section headers :\t");
    printf("%d",ehdr->e_shnum);

    printf("\n Section header string table index :\t");
    printf("%d\n",ehdr->e_shstrndx);


  }else{
    fprintf(stderr, "Error : Magic number incorrect, not ELF file\n"); // Display the output of the magic number check
    return -1;
  }

  bitclose() ? 0 : fprintf(stderr, "Cannot close file !\n");
  return 0;
}
