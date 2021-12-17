#include "bfile.h"

#define DEBUG

FILE *filename;

int bitread(size_t nb_bit)
{
  int current_bit;
  uint32_t byte = 0;

  current_bit = fgetc(filename);
  byte = byte | current_bit;

  for (size_t i = 0; i < nb_bit-1; i++)
  {
    current_bit = fgetc(filename);
    byte = (byte<<1) | current_bit;
  }
  return byte;
}

bool bitopen(char const *file)
{
  assert(file);
  filename = fopen(file, "r");
  assert(filename);
  return true;
}

bool bitclose(void)
{
  assert(filename);
  fclose(filename);
  return true;
}

bool bitopened(void)
{
  return filename != NULL;
}
