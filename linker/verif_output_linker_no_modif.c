#include "verif_output_linker_no_modif.h"

void bab(FILE *f1, FILE *f2)
{
  int error = 0;
  char c1, c2;
  long int bit_number = 0;

  while (!feof(f1) && !feof(f2))
  {
    ++bit_number;
    fread(&c1, sizeof(char), 1, f1);
    fread(&c2, sizeof(char), 1, f2);

    if (c1 != c2)
    {
      fprintf(stderr, "  erreur au bit numéro: %ld: 0x%lx | %02hhx | %02hhx\n", bit_number, bit_number, c1, c2);
      error = 1;
    }
  }
  if (!error)
    fprintf(stderr, "  les deux fichiers sont parfaitement identique au bit près !\n");
}

void verif(char *file1, char *file2)
{
  FILE *f1, *f2;

  f1 = fopen(file1, "rb");
  f2 = fopen(file2, "rb");

  fprintf(stderr, "Comparaison des fichiers %s et %s:\n", "test.o", "test/example1.o");

  // Comparaison des fichiers bits à bits
  bab(f1, f2);

  fclose(f1);
  fclose(f2);
}