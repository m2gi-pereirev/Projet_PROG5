#include "linker.h"

int main(int argc, char **argv)
{
  if (argc < 2)
    printf("Usage: %s elf_file [file_out]\n", argv[0]);
  else
  {
    char *output_filename = "out.o";
    if (argc == 3)
      output_filename = argv[2];

    char *file_content = NULL;
    Elf32_file elf;
    elf.shdrn = NULL;

    file_content = load_file_content(argv[1]);
    storage_elf_content(file_content, &elf);
    if (elf.shdrn != NULL)
    {
      relocations_execution(&elf);
      elf_reorganization(&elf);
      FILE *file_out = load_elf_output(output_filename);
      write_elf_content(&elf, file_out);
      free_elf32_file(&elf);
    }
  }
}