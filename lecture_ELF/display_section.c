#include "display_section.h"
#include "display_section_headers.h"

void print_section_content_header(char *name)
{
  printf("Hex dump of section '%s':\n", name);
}

void print_section(char *section_content, int size)
{
  int i = 0;
  int section;
  int len_text = 0;
  char text[20] = "";

  // Print hexa and human readable display
  while (i < size)
  {
    // Print adresse of the values
    if (i % 16 == 0)
      printf("  0x%08" PRIx32 " ", i);

    section = i + 4;
    // Print by section of four hexadecimal values
    while (i < section && i < size)
    {
      printf("%02hhx", section_content[i]);
      text[len_text] = section_content[i];
      ++len_text;
      ++i;
    }
    printf(" ");

    // If end of line
    if (i % 16 == 0)
    {
      for (int j = 0; j < len_text; j++)
      {
        if (text[j] >= 32 && text[j] <= 126)
        {
          printf("%c", text[j]);
        }
        else
        {
          printf(".");
        }
      }
      len_text = 0;
      printf("\n");
    }
  }

  // Correction for display
  while (i % 16 != 0)
  {
    if (i % 4 == 0)
      printf(" ");
    printf("  ");
    ++i;
  }

  // Print last human readable line
  for (int j = 0; j < len_text; j++)
  {
    if (text[j] >= 32 && text[j] <= 126)
      printf("%c", text[j]);
    else
      printf(".");
  }
  printf("\n");
}

void print_section_content(Elf32_Shdr_named *shdr_named, char *section_content, int idx)
{
  // INIT DISPLAY
  print_section_content_header(shdr_named->names[idx]);
  // DISPLAY
  print_section(section_content, shdr_named->shdr[idx].sh_size);
}