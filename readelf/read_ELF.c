#include "read_ELF.h"

//* ------------------------------------------------
//!             DETECTION OF ARGUMENTS
//* ------------------------------------------------

char **options_read(int argc, char **argv, Exec_options *exec_op, hexdump_option *hexdump)
{
  char **files = NULL;
  const char *const short_options = "haHSsx:r";
  // Lecture des arguments
  while (1)
  {
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"all", no_argument, 0, 'a'},
        {"file-header", no_argument, 0, 'H'},
        {"section-headers", no_argument, 0, 'S'},
        {"sections", no_argument, 0, 'S'},
        {"syms", no_argument, 0, 's'},
        {"symbols", no_argument, 0, 's'},
        {"hex-dump", required_argument, 0, 'x'},
        {"test", no_argument, 0, 't'},
        {"relocs", no_argument, 0, 'r'},
        {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, short_options, long_options, &option_index);

    if (c == -1)
      break;

    switch (c)
    {
    case 'h': // help display
      free(files);
      print_usage(stdout, EXIT_SUCCESS, argv[0]);

    case 'a': // all informations display
      exec_op->header = true;
      exec_op->section_headers = true;
      exec_op->symb = true;
      exec_op->rel = true;
      break;

    case 'H': // Header display
      exec_op->header = true;
      break;

    case 'S': // Section headers display
      exec_op->section_headers = true;
      break;

    case 'x':; // display a section
      int tmp;
      if (sscanf(optarg, "%d", &tmp) == 1) // it's integer
      {
        hexdump->is_string = false;
        hexdump->section_number = atoi(optarg);
      }
      else // it's string
      {
        hexdump->is_string = true;
        hexdump->section_name = calloc(strlen(optarg) + 1, sizeof(char));
        strcpy(hexdump->section_name, optarg);
      }
      exec_op->hexdump = true;
      break;

    case 's':
      exec_op->symb = true;
      break;

    case 'r':
      exec_op->rel = true;
      break;

    case '?': // error usage
      print_usage(stderr, EXIT_FAILURE, argv[0]);

    default: // Error
      exit(EXIT_FAILURE);
    }
  }

  if (optind == argc) // If there are no given files
  {
    print_usage(stderr, EXIT_FAILURE, argv[0]);
  }
  else if (!exec_op->header && !exec_op->section_headers && !exec_op->symb && !exec_op->hexdump && !exec_op->rel)
  {
    print_usage(stderr, EXIT_FAILURE, argv[0]);
  }
  else if (optind == argc - 1) // If there is only one file given
  {
    exec_op->nb_files = 1;
    files = calloc(1, sizeof(char *));                         // Allocation of the array to a single element to store the file name
    files[0] = calloc(strlen(argv[optind]) + 1, sizeof(char)); // Allocation to store the file path
    strcpy(files[0], argv[optind]);                            // Storing the file path
  }
  else // if there are several files given
  {
    exec_op->nb_files = argc - optind;                 // Number of file paths given
    files = calloc(exec_op->nb_files, sizeof(char *)); // Multi-element array allocation to store file paths.
    for (int i = 0; i < exec_op->nb_files; i++)
    {
      files[i] = calloc(strlen(argv[optind + i]) + 1, sizeof(char)); // Allocation to store the file path
      strcpy(files[i], argv[optind + i]);                            // Storing the file path
    }
  }
  return files;
}

char **init_execution(int argc, char **argv, Exec_options *exec_op, hexdump_option *hexdump)
{
  exec_op->header = false;
  exec_op->section_headers = false;
  exec_op->big_endian_file = false;
  exec_op->hexdump = false;
  exec_op->symb = false;
  exec_op->rel = false;

  hexdump->is_string = false;

  return options_read(argc, argv, exec_op, hexdump);
}

//* ------------------------------------------------
//!                 ELF DETECTION
//* ------------------------------------------------

bool is_ELF_file(unsigned char *ident)
{
  // Check if the magic number of the file correponds to ELF identifier file
  return memcmp(ident, ELFMAG, SELFMAG) == 0;
}

bool is_ELF32(unsigned char *ident)
{
  // Check if the file is an ELF32 or not
  return ident[EI_CLASS] == ELFCLASS32;
}

//* ------------------------------------------------
//!            ELF READING AUXILIARIES
//* ------------------------------------------------

int section_index_finder(hexdump_option *hexdump, Elf32_Shdr_named *shdr_named)
{
  int idx = 0;
  //? Recovering the section index if it exists
  if (hexdump->is_string) // if string is passed in argument
  {
    // Search for the header index
    while (idx < shdr_named->shnum && strcmp(hexdump->section_name, shdr_named->names[idx]) != 0)
      idx++;
  }
  else // if int is passed in argument
  {
    idx = hexdump->section_number;
  }
  return idx;
}

void relocation_name_value_association(Elf32_Rel_named *rel_named, Elf32_Sym_named *sym_named)
{
  if (rel_named->rel_type)
  {
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      //$ Name association
      rel_named->names[i] = calloc(strlen(sym_named->names[ELF32_R_SYM(rel_named->rel[i].r_info)]) + 1, sizeof(char));
      strcpy(rel_named->names[i], sym_named->names[ELF32_R_SYM(rel_named->rel[i].r_info)]);

      //$ Value association
      rel_named->sym_val[i] = sym_named->sym[ELF32_R_SYM(rel_named->rel[i].r_info)].st_value;
    }
  }
  else
  {
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      //$ Name association
      rel_named->names[i] = calloc(strlen(sym_named->names[ELF32_R_SYM(rel_named->rela[i].r_info)]) + 1, sizeof(char));
      strcpy(rel_named->names[i], sym_named->names[ELF32_R_SYM(rel_named->rela[i].r_info)]);

      //$ Value association
      rel_named->sym_val[i] = sym_named->sym[ELF32_R_SYM(rel_named->rela[i].r_info)].st_value;
    }
  }

}

//* ------------------------------------------------
//!                  ELF READING
//* ------------------------------------------------

//? HEADER
void header_read(Elf32_Ehdr *ehdr, FILE *filename)
{
  fread(ehdr, 1, sizeof(Elf32_Ehdr), filename);
}

//? SECTION HEADERS
void section_headers_read(Exec_options *exec_op, FILE *filename, Elf32_Ehdr *ehdr, Elf32_Shdr_named *shdr_named)
{
  shdr_named->shnum = ehdr->e_shnum;
  int last_entry = ehdr->e_shnum - 1;
  char *Section_Names;

  // Allocation
  shdr_named->shdr = calloc(shdr_named->shnum, sizeof(Elf32_Shdr));
  shdr_named->names = calloc(shdr_named->shnum, sizeof(char *));

  // Reading of the last entry
  fseek(filename, ehdr->e_shoff + last_entry * sizeof(Elf32_Shdr), SEEK_SET);
  fread(&shdr_named->shdr[last_entry], sizeof(Elf32_Shdr), 1, filename);

  // endianess
  if (exec_op->big_endian_file)
    section_headers_endianess(&shdr_named->shdr[last_entry]);

  // Allocation
  Section_Names = calloc(1, shdr_named->shdr[last_entry].sh_size);

  // Recovering the names of the section headers
  fseek(filename, shdr_named->shdr[last_entry].sh_offset, SEEK_SET);
  fread(Section_Names, sizeof(char), shdr_named->shdr[last_entry].sh_size, filename);

  // Reading section headers
  for (int i = 0; i < shdr_named->shnum; i++)
  {
    fseek(filename, ehdr->e_shoff + i * sizeof(Elf32_Shdr), SEEK_SET);
    fread(&shdr_named->shdr[i], 1, sizeof(Elf32_Shdr), filename);

    if (exec_op->big_endian_file)
      section_headers_endianess(&shdr_named->shdr[i]);

    // Association of the name with the header
    if (shdr_named->shdr[i].sh_name)
    {
      char *name = "";
      name = Section_Names + shdr_named->shdr[i].sh_name;
      shdr_named->names[i] = calloc(strlen(name) + 1, sizeof(char));
      strcpy(shdr_named->names[i], name);
    }
  }
  free(Section_Names);
}

//? SYMBOLS TABLE
void symbole_table_elf(Exec_options *exec_op, FILE *filename, Elf32_Shdr_named *shdr_named, Elf32_Sym_named *sym_named)
{
  int idx = 0;
  char *Symbole_names;
  int idx_sym_names;

  while (idx < shdr_named->shnum && shdr_named->shdr[idx].sh_type != SHT_SYMTAB)
    ++idx;

  if (idx < shdr_named->shnum)
  {
    //$ Allocation
    sym_named->sym_num = (int)(shdr_named->shdr[idx].sh_size / sizeof(Elf32_Sym));
    sym_named->sym = calloc(sym_named->sym_num, sizeof(Elf32_Sym));
    sym_named->names = calloc(sym_named->sym_num, sizeof(char *));

    idx_sym_names = shdr_named->shdr[idx].sh_link;

    Symbole_names = calloc(1, shdr_named->shdr[idx_sym_names].sh_size);

    fseek(filename, shdr_named->shdr[idx_sym_names].sh_offset, SEEK_SET);
    fread(Symbole_names, 1, shdr_named->shdr[idx_sym_names].sh_size, filename);

    for (int i = 0; i < sym_named->sym_num; i++)
    {
      fseek(filename, shdr_named->shdr[idx].sh_offset + i * sizeof(Elf32_Sym), SEEK_SET);
      fread(&sym_named->sym[i], 1, sizeof(Elf32_Sym), filename);

      //? Endianess
      if (exec_op->big_endian_file)
        symbole_endianess(&sym_named->sym[i]);

      //? Association of the name with the header
      if ((ELF32_ST_TYPE(sym_named->sym[i].st_info) == STT_NOTYPE) && sym_named->sym[i].st_name)
      {
        char *name = "";
        name = Symbole_names + sym_named->sym[i].st_name;
        sym_named->names[i] = calloc(strlen(name) + 1, sizeof(char));
        strcpy(sym_named->names[i], name);
      }
      if (ELF32_ST_TYPE(sym_named->sym[i].st_info) == STT_SECTION && sym_named->sym[i].st_shndx)
      {
        sym_named->names[i] = calloc(strlen(shdr_named->names[sym_named->sym[i].st_shndx]) + 1, sizeof(char));
        strcpy(sym_named->names[i], shdr_named->names[sym_named->sym[i].st_shndx]);
      }
    }
    free(Symbole_names);
  }
  else
    printf("No symbols table!\n");
}

//? SECTION CONTENT
int section_content_read(Exec_options *exec_op, FILE *filename, hexdump_option *hexdump, Elf32_Shdr_named *shdr_named, char *section_content)
{
  int idx = section_index_finder(hexdump, shdr_named);

  //? Reading section content if had data
  if (idx > 0 && idx < shdr_named->shnum && shdr_named->shdr[idx].sh_size > 0)
  {
    // Allocation
    section_content = calloc(1, shdr_named->shdr[idx].sh_size);

    //$ Read section
    fseek(filename, shdr_named->shdr[idx].sh_offset, SEEK_SET);
    fread(section_content, 1, shdr_named->shdr[idx].sh_size, filename);
  }
  else if (shdr_named->shdr[idx].sh_size == 0) //! No data
  {
    if (shdr_named->names[idx])
      printf("Section '%s' has no data to dump.\n", shdr_named->names[idx]);
    else
      printf("Section '' has no data to dump.\n");
  }
  //? Section doesn't exist
  else if (idx >= shdr_named->shnum && hexdump->is_string)
    printf("readelf: Warning: Section '%s' was not dump because it doesn't exist!\n", hexdump->section_name);
  else if ((idx >= shdr_named->shnum || idx < 0) && !hexdump->is_string)
    printf("readelf: Warning: Section %d was not dump because it doesn't exist!\n", hexdump->section_number);

  return idx;
}

//? RELOCATION TABLE
void relocation_sections_read(Exec_options *exec_op, FILE *filename, Elf32_Shdr *shdr, Elf32_Rel_named *rel_named)
{
  //$ REL section
  if (shdr->sh_type == SHT_REL)
  {
    rel_named->rel_type = true;
    rel_named->rel_num = shdr->sh_size / sizeof(Elf32_Rel);

    //$ Allocation
    rel_named->names = calloc(rel_named->rel_num, sizeof(char *));
    rel_named->sym_val = calloc(rel_named->rel_num, sizeof(uint32_t));
    rel_named->rel = calloc(rel_named->rel_num, sizeof(Elf32_Rel));

    fseek(filename, shdr->sh_offset, SEEK_SET);
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      //$ Reading sym entries
      fread(&rel_named->rel[i], sizeof(Elf32_Rel), 1, filename);

      //$ Endianess
      if (exec_op->big_endian_file)
        rel_section_endianess(&rel_named->rel[i]);
    }
  }

  //$ RELA section
  if (shdr->sh_type == SHT_RELA)
  {
    rel_named->rel_type = false;
    rel_named->rel_num = shdr->sh_size - sizeof(Elf32_Rela);

    //$ Allocation
    rel_named->names = calloc(rel_named->rel_num, sizeof(char *));
    rel_named->sym_val = calloc(rel_named->rel_num, sizeof(uint32_t));
    rel_named->rel = calloc(rel_named->rel_num, sizeof(Elf32_Rela));

    fseek(filename, shdr->sh_offset, SEEK_SET);
    for (int i = 0; i < rel_named->rel_num; i++)
    {
      //$ Reading sym entries
      fread(&rel_named->rela[i], sizeof(Elf32_Rela), 1, filename);

      //$ Endianess
      if (exec_op->big_endian_file)
        rela_section_endianess(&rel_named->rela[i]);
    }
  }
}

//* ------------------------------------------------
//!              FREE'D ALLOCATION
//* ------------------------------------------------

void free_shdr_named(Elf32_Shdr_named *shdr_named)
{
  // Free'd all inside allocation of the structure
  for (int i = 0; i < shdr_named->shnum; i++)
  {
    free(shdr_named->names[i]);
  }
  free(shdr_named->names);
  free(shdr_named->shdr);
}

void free_sym_named(Elf32_Sym_named *sym_named)
{
  for (int i = 0; i < sym_named->sym_num; i++)
  {
    free(sym_named->names[i]);
  }
  free(sym_named->names);
  free(sym_named->sym);
}

void free_rel_named(Elf32_Rel_named *rel_named)
{
  for (int i = 0; i < rel_named->rel_num; i++)
  {
    free(rel_named->names[i]);
  }
  free(rel_named->sym_val);
  free(rel_named->names);
  if (rel_named->rel_type)
    free(rel_named->rel);
  else
    free(rel_named->rela);
}

//* ------------------------------------------------
//!                    RUN
//* ------------------------------------------------

void run(Exec_options *exec_op, char *files[], hexdump_option *hexdump)
{
  //? STATEMENTS
  FILE *filename = NULL;
  Elf32_Ehdr ehdr;             // File header informations structure
  Elf32_Shdr_named shdr_named; // Section headers with names informations structure
  Elf32_Sym_named sym_named;   // Symbols table informations structure
  Elf32_Rel_named rel_named;   // Relocation section informations structure

  //? EXECUTION
  for (int i = 0; i < exec_op->nb_files; i++)
  {
    filename = fopen(files[i], "rb"); // Opening the file for binary read
    // Checking file openned
    //! File not opened
    if (filename == NULL)
    {
      if (exec_op->nb_files == 1) // if only one file
      {
        printf("read-elf: Error: '%s': No such file\n", files[0]);
        free(files[i]);
        free(files);
        exit(EXIT_FAILURE);
      }
      else // if there are several files
      {
        printf("read-elf: Error: '%s': No such file\n", files[i]);
      }
    }
    //! if file openned
    else
    {
      //$ if there are several files to read
      if (exec_op->nb_files > 1)
        printf("\nFile: %s\n", files[i]);

      //* READING HEADER
      header_read(&ehdr, filename);

      //? Detection of big or little endian
      if (ehdr.e_ident[EI_DATA] == ELFDATA2MSB)
      {
        exec_op->big_endian_file = true;
        header_endianess(&ehdr);
      }

      ////===========================================================================
      // NOT ELF FILE
      if (!is_ELF_file(ehdr.e_ident))
      {
        printf("Error: Not an ELF - it has the wrong magic bytes at the start\n");
      }
      else if (!is_ELF32(ehdr.e_ident))
      {
        printf("Error: readl-elf does not support 64-bit ELF files\n");
      }
      ////===========================================================================

      //? 32-bit ELF file
      if (is_ELF_file(ehdr.e_ident) && is_ELF32(ehdr.e_ident))
      {
        //* READING SECTION HEADERS
        section_headers_read(exec_op, filename, &ehdr, &shdr_named);

        //* READING SYMBOLS TABLE
        symbole_table_elf(exec_op, filename, &shdr_named, &sym_named);

        //* Display File header
        if (exec_op->header)
        {
          print_entete(&ehdr);
        }

        //* Section header
        if (exec_op->section_headers && ehdr.e_shnum > 0)
        {
          //! Information if the file header is not displayed
          if (!exec_op->header)
            printf("There are %d section header, starting at offset 0x%x:\n", ehdr.e_shnum, ehdr.e_shoff);

          print_section_headers(&shdr_named);
        }
        // If no section in the files
        else if (exec_op->section_headers && ehdr.e_shnum == 0)
        {
          printf("There is no section in this file !\n");
        }

        //* Relocation Section
        if (exec_op->rel)
        {
          if (shdr_named.shnum > 0)
          {
            bool rel_section_detected = false;
            for (int idx = 0; idx < shdr_named.shnum; idx++)
            {
              //$ Reading
              relocation_sections_read(exec_op, filename, &shdr_named.shdr[idx], &rel_named);

              if (shdr_named.shdr[idx].sh_type == SHT_REL || shdr_named.shdr[idx].sh_type == SHT_RELA)
              {
                //$ Sym name and value association for rel
                relocation_name_value_association(&rel_named, &sym_named);

                //$ Display
                print_relocation_section(&rel_named, shdr_named.shdr[idx].sh_offset, shdr_named.names[idx]);

                //$ Free allocation
                free_rel_named(&rel_named);

                rel_section_detected = true;
              }
            }
            if (!rel_section_detected)
            {
              printf("readelf: There is no relocation section in this file!\n");
            }
          }
          else
          {
            printf("readelf: There is no relocation section in this file!\n");
          }
        }

        //* Symbols Table
        if (exec_op->symb)
        {
          //$ Display
          print_table_sym(&sym_named);
        }

        //* Section display
        if (exec_op->hexdump && shdr_named.shnum > 0)
        {
          char *section_content = NULL;
          int idx = section_content_read(exec_op, filename, hexdump, &shdr_named, section_content);

          if (section_content) //  Display section content
          {
            print_section_content(&shdr_named, section_content, idx);
          }

          //$ Free allocation
          free(section_content);
        }
        else if (exec_op->hexdump && shdr_named.shnum == 0)
        {
          printf("There is no section in this file !\n");
        }

        //! END OF READING

        //* free allocation
        free_sym_named(&sym_named);
        free_shdr_named(&shdr_named);
      }
      // Closing file
      fclose(filename);

      printf("\n");
    }

    free(files[i]);
  }
}

//* ------------------------------------------------
//!                    MAIN
//* ------------------------------------------------

int main(int argc, char *argv[])
{
  Exec_options exec_op;
  hexdump_option hexdump;

  // Checking the minimum number of arguments
  if (argc < 2)
    print_usage(stderr, EXIT_FAILURE, argv[0]);

  // Input detections
  char **files = init_execution(argc, argv, &exec_op, &hexdump);

  // Execution
  run(&exec_op, files, &hexdump);

  if (hexdump.is_string)
    free(hexdump.section_name);
  free(files);
  return 0;
}
