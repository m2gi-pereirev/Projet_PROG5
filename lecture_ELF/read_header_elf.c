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
