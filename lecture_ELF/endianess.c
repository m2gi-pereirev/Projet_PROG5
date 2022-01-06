#include "endianess.h"

void header_endianess(Elf32_Ehdr *ehdr)
{
  ehdr->e_type = __bswap_16(ehdr->e_type);
  ehdr->e_machine = __bswap_16(ehdr->e_machine);
  ehdr->e_version = __bswap_32(ehdr->e_version);
  ehdr->e_entry = __bswap_32(ehdr->e_entry);
  ehdr->e_phoff = __bswap_32(ehdr->e_phoff);
  ehdr->e_shoff = __bswap_32(ehdr->e_shoff);
  ehdr->e_flags = __bswap_32(ehdr->e_flags);
  ehdr->e_ehsize = __bswap_16(ehdr->e_ehsize);
  ehdr->e_phentsize = __bswap_16(ehdr->e_phentsize);
  ehdr->e_phnum = __bswap_16(ehdr->e_phnum);
  ehdr->e_shentsize = __bswap_16(ehdr->e_shentsize);
  ehdr->e_shnum = __bswap_16(ehdr->e_shnum);
  ehdr->e_shstrndx = __bswap_16(ehdr->e_shstrndx);
}

void section_headers_endianess(Elf32_Shdr *shdr)
{
  shdr->sh_name = __bswap_32(shdr->sh_name);
  shdr->sh_type = __bswap_32(shdr->sh_type);
  shdr->sh_flags = __bswap_32(shdr->sh_flags);
  shdr->sh_addr = __bswap_32(shdr->sh_addr);
  shdr->sh_offset = __bswap_32(shdr->sh_offset);
	shdr->sh_size = __bswap_32(shdr->sh_size);
	shdr->sh_link = __bswap_32(shdr->sh_link);
	shdr->sh_info = __bswap_32(shdr->sh_info);
	shdr->sh_addralign = __bswap_32(shdr->sh_addralign);
	shdr->sh_entsize = __bswap_32(shdr->sh_entsize);
}

void section_content_endianess(char *content, Elf32_Shdr *shdr)
{
  // 2 by 2 because we invert by 16 bits and that a char contains 8 bits
  for (int i = 0; i < shdr->sh_size; i += 2)
    content[i] = __bswap_16(content[i]);
  shdr->sh_size = __bswap_32(shdr->sh_size);
  shdr->sh_link = __bswap_32(shdr->sh_link);
  shdr->sh_info = __bswap_32(shdr->sh_info);
  shdr->sh_addralign = __bswap_32(shdr->sh_addralign);
  shdr->sh_entsize = __bswap_32(shdr->sh_entsize);
}

void symbole_endianess(Elf32_Sym *sym)
{
  sym->st_name = __bswap_32(sym->st_name);
  sym->st_value = __bswap_32(sym->st_value);
  sym->st_size = __bswap_32(sym->st_size);
  sym->st_shndx = __bswap_16(sym->st_shndx);
}