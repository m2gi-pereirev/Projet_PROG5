#include "linker.h"

int main(int argc, char **argv)
{
  char *file_content = NULL;
  Elf32_file elf;

  char *filename1 = "test/example1.o";
  char *filename2 = "test.o";

  file_content = load_file_content(filename1);
  storage_elf_content(file_content, &elf);
  relocations_execution(&elf);
  elf_reorganization(&elf);
  FILE *file_out = load_elf_output(filename2);
  write_elf_content(&elf, file_out);
  free_elf32_file(&elf);
}