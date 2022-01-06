#include "display.h"

void print_usage(FILE *stream, int exit_code, char *program_name)
{
  fprintf(stream, "Usage: %s <option(s)> elf-file(s)\n", program_name);
  fprintf(stream, " Display information about the contents of ELF format files\n Options are:\n");
  fprintf(stream,
          "  -a  --all              Equivalent to: -H -S\n"
          "  -H  --file-header      Display the ELF file header\n"
          "  -S  --section-headers  Display the sections' header\n"
          "      --sections         An alias for --section-headers\n"
          " -x --hex-dump=<number|name>\n"
          "                         Dump the contents of section <number|name> as bytes\n"
          "\n"
          "  -h  --help             Display this information\n");
  exit(exit_code);
}
