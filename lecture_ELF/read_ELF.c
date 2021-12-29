#include "read_ELF.h"

const char* program_name;
static int verbose_flags;

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

void header_endianess(Elf32_Ehdr *ehdr)
{
  if (ehdr->e_ident[EI_DATA] == ELFDATA2MSB)
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
}

void print_usage(FILE* stream, int exit_code)
{
  fprintf(stream, "Usage: %s <option(s)> elf-file(s)\n", program_name);
  fprintf(stream, " Display information about the contents of ELF format files\n Options are:\n");
  fprintf(stream,
  "  -a  --all              Equivalent to: -H -S\n"
  "  -H  --file-header      Display the ELF file header\n"
  "  -S  --section-headers  Display the sections' header\n"
  "      --sections         An alias for --section-headers\n"
  "  -h  --help             Display this information\n");
  exit(exit_code);
}

int main(int argc, char *argv[])
{
  FILE *file = NULL;
  bool read_all = true, only_file_header = false, only_section_headers = false;
  const char* const short_options = "haHS";

  program_name = argv[0];

  if (argc < 2)
    print_usage(stderr, EXIT_FAILURE);

  // Lecture des arguments
  while (1)
  {
    static struct option long_options[] = {
      {"help", no_argument, 0, 'h'},
      {"all", no_argument, 0, 'a'},
      {"file-header", no_argument, 0, 'H'},
      {"section-headers", no_argument, 0, 'S'},
      {"sections", no_argument, 0, 'S'},
      {0, 0, 0, 0}
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, short_options, long_options, &option_index);

    if (c == -1)
      break;

    switch (c)
    {
    // case 0:
    //   if (long_options[option_index].flag != 0)
    //     break;
    //   printf("option %s", long_options[option_index].name);
    //   if (optarg)
    //     printf("with arg %s", optarg);
    //   printf("\n");
    //   break;

    case 'h':
      print_usage(stdout, EXIT_SUCCESS);

    case 'a':
      read_all = true;
      break;

    case 'H':
      read_all = false;

      break;

    case 'S':
      printf("option -S\n");
      break;

    case '?':
      print_usage(stderr, EXIT_FAILURE);

    default:
      exit(EXIT_FAILURE);
    }
  }

  if (verbose_flags)
    puts("verbose flag is set");

  if (optind < argc)
  {
    printf("non-option ARGV-element: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
  }
  else
    print_usage(stderr, EXIT_FAILURE);


  return 0;

  // Elf32_Ehdr ehdr;
  // Elf32_Shdr shdr;
  // else
  // {
  //   fprintf(stderr, "Usage:\n%s <option(s)> elf-file(s)\n", argv[0]);
  //   // help();
  //   return -1;
  // }

  // read(&ehdr);
  // endianess(&ehdr);
  // print_entete(&ehdr);

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
  // int i;
  // long x = 0x112A380;
  // unsigned char *ptr = (unsigned char *)&x;
  // printf("x in hex: %lx\n", x);
  // printf("x by bytes: ");
  // for (i = 0; i < sizeof(long); i++)
  //   printf("%x\t", ptr[i]);
  // printf("\n");

  bitclose() ? 0 : fprintf(stderr, "Cannot close file !\n");
  return 0;
}
