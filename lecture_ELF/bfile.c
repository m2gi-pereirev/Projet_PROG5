#include "bfile.h"

FILE *filename;
int bit_number = 0;
fpos_t end_header_file;

uint32_t octetread(size_t nb_octet)
{
  assert(filename != NULL); // check if file is oppened
  uint32_t byte = 0;
  unsigned tmp;
  int count = 0;
  do
  {
    tmp = fgetc(filename);
    if (tmp == EOF) // if end of file return -1
      return -1;
    else
    {
      byte = (byte << 8) | tmp; // left shift of the old byte read to make room for the new byte
    }
    ++count; // counting of a number of bytes remaining to be read
  } while (count < nb_octet);
  // fprintf(stderr, "%s", bin(byte)); // displays in stderr of the binary value read
  // fprintf(stderr, " = 0x%04" PRIx32 "\n", byte); // display in stderr of the hexadecimal value read
  return byte;
}

void read(Elf32_Ehdr *ehdr)
{
  fread(ehdr, 1, sizeof(Elf32_Ehdr), filename);
}

void octetread_section(void *shdr_adress, size_t nb_octet)
{
  assert(filename != NULL); // check if file is oppened
  int val, i;
  char tab[nb_octet];

  for (i = 0; i < nb_octet; i++)
  {
    val = fgetc(filename);
    tab[i] = val;
  }

  for (i = nb_octet - 1; i >= 0; i--)
  {
    *((char *)shdr_adress++) = tab[i];
  }
}

bool bitopen(char const *file)
{
  assert(file);
  filename = fopen(file, "rb");
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

void section_headers_start(Elf32_Off offset, Elf32_Half shstrndx)
{
  assert(filename != NULL);
  fgetpos(filename, &end_header_file);          // Save the ending of the header file for later
  fseek(filename, offset + shstrndx, SEEK_CUR); // We start the read at the start of the section header table
}