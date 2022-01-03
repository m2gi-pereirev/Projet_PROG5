#include "read_ELF.h"

void options_read(int argc, char **argv, Exec_options *exec_op, char *files[])
{
  const char *const short_options = "vhaHS";
  // Lecture des arguments
  while (1)
  {
    static struct option long_options[] = {
        {"verbose", no_argument, 0, 'v'},
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
    case 'v':
      exec_op->verbose = true;
      break;

    case 'h':
      print_usage(stdout, EXIT_SUCCESS, argv[0]);

    case 'a':
      break;

    case 'H': // Header display
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
    files[0] = malloc(100 * sizeof(char));
    strcpy(files[0], argv[optind]);
  }
  else
  {
    exec_op->nb_files = argc - optind;
    files = realloc(files, exec_op->nb_files * sizeof(char*));
    for (int i = 0; i < exec_op->nb_files; i++)
    {
      files[i] = malloc(sizeof(char) * strlen(argv[optind + i]));
      strcpy(files[i], argv[optind + i]);
    }
    fprintf(stderr, "\n\n");
  }
}

void init_execution(int argc, char **argv, Exec_options *exec_op, char **files)
{
  exec_op->all = true;
  exec_op->header = false;
  exec_op->section_headers = false;
  exec_op->verbose = false;
  exec_op->big_endian_file = false;

  options_read(argc, argv, exec_op, files);
}

void header_read(Elf32_Ehdr *ehdr, FILE *filename)
{
  fread(ehdr, 1, sizeof(Elf32_Ehdr), filename);
}

void section_headers_read(Elf32_Shdr *shdr)
{
  // shdr->sh_name = octetread(sizeof(shdr->sh_name));
  // shdr->sh_type = octetread(sizeof(shdr->sh_type));
  // shdr->sh_flags = octetread(sizeof(shdr->sh_flags));
  // shdr->sh_addr = octetread(sizeof(shdr->sh_addr));
  // shdr->sh_offset = octetread(sizeof(shdr->sh_offset));
  // shdr->sh_size = octetread(sizeof(shdr->sh_size));
  // shdr->sh_link = octetread(sizeof(shdr->sh_link));
  // shdr->sh_info = octetread(sizeof(shdr->sh_info));
  // shdr->sh_addralign = octetread(sizeof(shdr->sh_addralign));
  // shdr->sh_entsize = octetread(sizeof(shdr->sh_entsize));
}

void run(Exec_options *exec_op, char *files[])
{
  FILE *filename;
  Elf32_Ehdr ehdr;
  Elf32_Shdr shdr;

  for (int i = 0; i < exec_op->nb_files; i++)
  {
    filename = fopen(files[i], "rb"); // opening the file for binary read
    // Checking file openned
    if (filename == NULL)
    {
      if(exec_op->nb_files == 1) // if only one file
      {
        printf("read-elf: Error: '%s': No such file\n", files[i]);
        exit(EXIT_FAILURE);
      }
      else // if there are multiple files
      {
        printf("read-elf: Error: '%s': No such file\n", files[i]);
      }
    }

    // if there are several files to read
    if (exec_op->nb_files > 1)
      printf("File: %s\n", files[i]);

    (exec_op->verbose) ? fprintf(stderr, "\033[36mReading the file header\033[37m\n") : 0;
    // READING HEADER
    header_read(&ehdr, filename);

    // Detection of big or little endian
    if (ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
    {
      (exec_op->verbose) ? fprintf(stderr, "\033[36mFile is in big endian, switch to little endian\033[37m\n") : 0;
      exec_op->big_endian_file = true;
      header_endianess(&ehdr);
    }


    if (exec_op->all) // display all of the elf file
    {
      print_entete(&ehdr); // display header's file

      (exec_op->verbose) ? fprintf(stderr, "\033[36mReading section header's\n") : 0;
      // Reading section headers
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
      else if (exec_op->section_headers && ehdr.e_shnum == 0)
      {
        printf("There is no section in this file !\n");
      }
    }
    fclose(filename);

    // Conditions for displaying multiple files
    if (exec_op->nb_files > 1)
      printf("\n");

    (exec_op->verbose) ? fprintf(stderr, "\033[36mEnd of file reading\033[37m\n") : 0;

    free(files[i]); // We release the entries because we don't need them anymore
  }
}

int main(int argc, char *argv[])
{
  char **files = malloc(sizeof(char *)); // At least one file must be entered
  Exec_options exec_op;

  // Checking the minimum number of arguments
  if (argc < 2)
    print_usage(stderr, EXIT_FAILURE, argv[0]);

  // Input detections
  init_execution(argc, argv, &exec_op, files);
  (exec_op.verbose) ? fprintf(stderr, "\033[36mInitialisation succeed !\033[37m\n") : 0;

  // Execution
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
  free(files);
  return 0;
}
