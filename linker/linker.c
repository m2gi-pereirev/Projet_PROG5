#include "linker.h"

int main(int argc, char **argv)
{
  if (argc < 3)
    printf("Usage: %s elf_file file_out\n", argv[0]);
  else
  {
    char *file_content = NULL;
    Elf32_file elf;

    file_content = load_file_content(argv[1]);
    storage_elf_content(file_content, &elf);
    relocations_execution(&elf);
    elf_reorganization(&elf);
    FILE *file_out = load_elf_output(argv[2]);
    write_elf_content(&elf, file_out);
    free_elf32_file(&elf);
  }
}