#include "display_section.h"
#include "display_section_headers.h"

void print_section_hexa(Elf32_Shdr_named *shdr_named, char *section_content, int idx){
    int pos = 0;
    int ind = 0;
    uint32_t bloc;
    while(pos < shdr_named->shdr[idx].sh_size){
        
        //First colon and line change
        if(pos%256 == 0)
          printf("\n 0x%.8x ", ind*10); 
        
        if (pos%8 == 0) //Space for each 8 bytes bloc
            printf(" ");
        
        printf("%.4x", section_content[pos*4]); //Print 4 bytes

        //Last text colon
        if(pos%256 == 255){  
          int j = pos-255;
          printf(" ");
          while (j < pos+1) {
            if (section_content[j] >= 32 && section_content[j] <= 126) { //ascii table [32;126]
              printf("%c", section_content[j]);
            }
            else{
              printf(".");
            }
            j+=8;
          }
        }
        pos+=32;
        ind++;
    }
    printf("\n");
    printf("\n");
}

void print_section_text(Elf32_Shdr_named *shdr_named, int idx)
{
    printf("\n");
  // INIT DISPLAY
    section_print_display_header_bis();

  // DISPLAY
    section_print_number(idx);
    section_print_name(shdr_named->names[idx]);
    section_print_type(shdr_named->shdr[idx].sh_type);
    section_print_address(shdr_named->shdr[idx].sh_addr);
    section_print_decalage(shdr_named->shdr[idx].sh_offset);
    section_print_size(shdr_named->shdr[idx].sh_size);
    section_print_entrysize(shdr_named->shdr[idx].sh_entsize);
    section_print_flags(shdr_named->shdr[idx].sh_flags);
    section_print_link(shdr_named->shdr[idx].sh_link);
    section_print_info(shdr_named->shdr[idx].sh_info);
    section_print_alignement(shdr_named->shdr[idx].sh_addralign);
    printf("\n");
    section_print_flag_key_info();
}