#include "read_ELF.h"

void init_execution(int argc, char **argv, Exec_options *exec_op, char **files)
{
  exec_op->all = true;
  exec_op->header = false;
  exec_op->section_headers = false;

  options_read(argc, argv, exec_op, files);
}

void header_read(Elf32_Ehdr *ehdr, FILE *filename)
{
  fread(ehdr, 1, sizeof(Elf32_Ehdr), filename);
}

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

void run(Exec_options *exec_op, char **files)
{
  FILE *filename;
  Elf32_Ehdr ehdr;
  Elf32_Shdr shdr;

  for (int i = 0; i < exec_op->nb_files; i++)
  {
    filename = fopen(files[i], "rb");
    assert(filename != NULL);

    if (exec_op->nb_files > 1)
      printf("File: %s\n", files[i]);

    // READING
    header_read(&ehdr, filename);
    if (ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
    {
      exec_op->big_endian_file = true;
      header_endianess(&ehdr);
    }

    // DISPLAY
    if (exec_op->all)
    {
      section_headers_read(&shdr);
    }
    else
    {
      if (exec_op->header)
      {
        print_entete(&ehdr);
      }

      if (exec_op->section_headers && ehdr.e_shnum > 0)
      {
        // print_section();
      }
      else
      {
        printf("There is no section in this file !\n");
      }
    }
    free(filename);
  }
}

void options_read(int argc, char **argv, Exec_options *exec_op, char **files)
{
  const char *const short_options = "haHS";
  // Lecture des arguments
  while (1)
  {
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"all", no_argument, 0, 'a'},
        {"file-header", no_argument, 0, 'H'},
        {"section-headers", no_argument, 0, 'S'},
        {"sections", no_argument, 0, 'S'},
        {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, short_options, long_options, &option_index);

    if (c == -1)
      break;

    switch (c)
    {
    case 'h':
      print_usage(stdout, EXIT_SUCCESS, argv[0]);

    case 'a':
      break;

    case 'H':
      exec_op->all = false;
      exec_op->header = true;
      break;

    case 'S':
      exec_op->all = false;
      exec_op->section_headers = true;
      break;

    case '?':
      print_usage(stderr, EXIT_FAILURE, argv[0]);

    default:
      exit(EXIT_FAILURE);
    }
  }

  if (optind == argc)
    print_usage(stderr, EXIT_FAILURE, argv[0]);
  else if (optind == argc - 1)
  {
    exec_op->nb_files = 1;
    files[0] = argv[++optind];
  }
  else
  {
    exec_op->nb_files = argc - optind;
    files = malloc(sizeof(char *) * exec_op->nb_files);
    for (int i = 0; i < argc - optind; i++)
    {
      files[i] = argv[optind + i];
    }
  }
}

int main(int argc, char *argv[])
{
  char **files = NULL;
  Exec_options exec_op;

  if (argc < 2)
    print_usage(stderr, EXIT_FAILURE, argv[0]);

  init_execution(argc, argv, &exec_op, &files);

  run(&exec_op, files);

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
  return 0;
}
