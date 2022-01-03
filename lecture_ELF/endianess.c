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

}