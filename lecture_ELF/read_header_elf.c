#include "read_header_elf.h"


void header_read(Elf32_Ehdr *ehdr)
{
  for (int i = 0; i < 16; i++)
    ehdr->e_ident[i] = octetread(sizeof(unsigned char));
  ehdr->e_type = octetread(sizeof(ehdr->e_type));
  ehdr->e_machine = octetread(sizeof(ehdr->e_machine));
  ehdr->e_version = octetread(sizeof(ehdr->e_version));
  ehdr->e_entry = octetread(sizeof(ehdr->e_entry));
  ehdr->e_phoff = octetread(sizeof(ehdr->e_phoff));
  ehdr->e_shoff = octetread(sizeof(ehdr->e_shoff));
  ehdr->e_flags = octetread(sizeof(ehdr->e_flags));
  ehdr->e_ehsize = octetread(sizeof(ehdr->e_ehsize));
  ehdr->e_phentsize = octetread(sizeof(ehdr->e_phentsize));
  ehdr->e_phnum = octetread(sizeof(ehdr->e_phnum));
  ehdr->e_shentsize = octetread(sizeof(ehdr->e_shentsize));
  ehdr->e_shnum = octetread(sizeof(ehdr->e_shnum));
  ehdr->e_shstrndx = octetread(sizeof(ehdr->e_shstrndx));
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

  affichage_entete(ehdr);

  bitclose() ? 0 : fprintf(stderr, "Cannot close file !\n");
  return 0;
}
