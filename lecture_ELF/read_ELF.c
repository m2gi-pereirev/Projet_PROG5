#include "read_ELF.h"

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

// void section_read(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr)
// {
//   for (int i = 0; i < ehdr->e_shnum; i++)
//   {
//     octetread_section(&shdr[i].sh_name, sizeof(shdr[i].sh_name));
//     octetread_section(&shdr[i].sh_type, sizeof(shdr[i].sh_type));
//     octetread_section(&shdr[i].sh_flags, sizeof(shdr[i].sh_flags));
//     octetread_section(&shdr[i].sh_addr, sizeof(shdr[i].sh_addr));
//     octetread_section(&shdr[i].sh_offset, sizeof(shdr[i].sh_offset));
//     octetread_section(&shdr[i].sh_size, sizeof(shdr[i].sh_size));
//     octetread_section(&shdr[i].sh_link, sizeof(shdr[i].sh_link));
//     octetread_section(&shdr[i].sh_info, sizeof(shdr[i].sh_info));
//     octetread_section(&shdr[i].sh_addralign, sizeof(shdr[i].sh_addralign));
//     octetread_section(&shdr[i].sh_entsize, sizeof(shdr[i].sh_entsize));
//   }
// }

void section_read(Elf32_Shdr *shdr)
{
  shdr->sh_name = octetread(sizeof(shdr->sh_name));
  shdr->sh_type = octetread(sizeof(shdr->sh_type));
  shdr->sh_flags = octetread(sizeof(shdr->sh_flags));
  shdr->sh_addr = octetread(sizeof(shdr->sh_addr));
  shdr->sh_offset = octetread(sizeof(shdr->sh_offset));
  shdr->sh_size = octetread(sizeof(shdr->sh_size));
  shdr->sh_link = octetread(sizeof(shdr->sh_link));
  shdr->sh_info = octetread(sizeof(shdr->sh_info));
  shdr->sh_addralign = octetread(sizeof(shdr->sh_addralign));
  shdr->sh_entsize = octetread(sizeof(shdr->sh_entsize));
}

int main(int argc, char const *argv[])
{
  Elf32_Ehdr ehdr;

  Elf32_Shdr *shdr = malloc(sizeof(Elf32_Shdr));
  assert(shdr != NULL);

  if (argc > 1)
  {
    bitopen(argv[1]);
  }
  else
  {
    fprintf(stderr, "Error : only one possible argument\n");
    return -1;
  }

  // header_read(ehdr); // Reading the header
  read(&ehdr);
  print_entete(&ehdr);

  // if (ehdr->e_shnum > 0)
  // {
  //   printf("\n");
  //   printf("There are %d section header, starting at offset 0x%x", ehdr->e_shnum, ehdr->e_shoff);

  //   section_print_display_header();
  //   section_headers_start(ehdr->e_shoff, ehdr->e_shstrndx);
  //   for (int i = 0; i < ehdr->e_shnum; i++)
  //   {
  //     section_read(shdr);
  //     print_section(shdr, i);
  //   }
  //   section_print_flag_key_info();
  // }

  // else
  // {
  //   printf("There is no section in this file !\n");
  //   return -1;
  // }

  bitclose() ? 0 : fprintf(stderr, "Cannot close file !\n");
  return 0;
}
