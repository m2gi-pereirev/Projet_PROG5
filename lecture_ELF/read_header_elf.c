#include "read_header_elf.h"

// #define DEBUG

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

bool magic_number(Elf32_Ehdr *ehdr)
{
#ifdef DEBUG
  fprintf(stderr, "%s\n", ehdr->e_ident);
#endif
  return ehdr->e_ident[0] == ELFMAG0 || ehdr->e_ident[1] == ELFMAG1 || ehdr->e_ident[2] == ELFMAG2 || ehdr->e_ident[3] == ELFMAG3; // Check if the magic number of the file correponds to ELF identifier file
}

int main(int argc, char const *argv[])
{
  Elf32_Ehdr *ehdr = malloc(sizeof(Elf32_Ehdr));

  if (argc > 1)
  {
    bitopen(argv[1]);
  }

  header_read(ehdr); // Reading the header
  magic_number(ehdr) ? fprintf(stderr, "Magic number Correct, ELF file\n") : fprintf(stderr, "Error : Magique number incorrect, not ELF file\n"); // Display the output of the magic number check

  bitclose() ? 0 : fprintf(stderr, "Cannot close file !\n");
  return 0;
}
