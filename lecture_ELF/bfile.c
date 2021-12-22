#include "bfile.h"

FILE *filename;
int bit_number = 0;

uint32_t octetread(size_t nb_octet)
{
  assert(filename != NULL); // check if file is oppened
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
  //fprintf(stderr, "%s", bin(byte)); // displays in stderr of the binary value read
  //fprintf(stderr, " = 0x%04" PRIx32 "\n", byte); // display in stderr of the hexadecimal value read
  return byte;
}

void octetread_section(void *shdr_adress, int nb_octet)
{ 
  assert(filename != NULL); // check if file is oppened
  int val , i;
  char tab[nb_octet];

    for(i=0; i<nb_octet; i++)
    {
      val = fgetc(filename);
      tab[i] = val;
    }

    for(i=nb_octet-1; i>=0; i--)
    {
      *((char *)shdr_adress++) = tab[i];
    }
}

// printf(" = 0x%08" PRIx32, sh->sh_addr);


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