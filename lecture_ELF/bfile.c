#include "bfile.h"

FILE *filename;
int bit_number = 0;

uint32_t octetread(size_t nb_octet)
{
  assert(filename != NULL); // check is file is oppened
  uint32_t byte = 0;
  unsigned tmp;
  int count = 0;
  do
  {
    tmp = fgetc(filename);
    if(tmp == EOF) // if end of file return -1
      return -1;
    else
    {
      byte = (byte << 8) | tmp; // left shift of the old byte read to make room for the new byte
    }
    ++count; // counting of a number of bytes remaining to be read
  } while(count < nb_octet);
  fprintf(stderr, "%s", bin(byte)); // displays in stderr of the binary value read
  fprintf(stderr, " = 0x%04" PRIx32 "\n", byte); // display in stderr of the hexadecimal value read
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

char *bin(unsigned int i)
{
  static char buffer[1 + sizeof(unsigned int) * 8] = {0};
  char *p = buffer - 1 + sizeof(unsigned int) * 8;
  do
  {
    *--p = '0' + (i & 1);
    i >>= 1;
  } while (i);
  return p;
}