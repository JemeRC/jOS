#include "shell.h"
#include "../../libc/include/string.h"
#include "../../libc/include/stdlib.h"
#include "../drivers/screen.h"

void execute_command(char *input) {
    if (strcmp(input, "help") == 0) {
        kprint("Comenzi disponibile:\n");
        kprint("  help       - Afiseaza acest mesaj\n");
        kprint("  clear      - Curata ecranul\n");
        kprint("  hex <num>  - Converteste decimal in hex\n");
        kprint("  rev <txt>  - Inverseaza un text\n");
        return;
    } 
    if (strcmp(input, "clear") == 0) {
        clear_screen();
        kprint("                                                                 Version: [0.2] \n");
        return;
    }
    if (strncmp(input, "hex", 3) == 0) {
        char *num_str = input + 3;
        if(*num_str == 0){
            kprint("ERROR: No number\n");
            return;
        }
        if(*num_str != ' '){
            kprint("Comanda necunoscuta: '"); kprint(input); kprint("'\n");
            return;
        }
        num_str++;
        if(*num_str == 0){
            kprint("ERROR: No number\n");
            return;
        }
        
        int val = atoi(num_str);
        char hex_buffer[32];
        itoa(val, hex_buffer, 16);
        kprint("Decimal: "); kprint(num_str);
        kprint(" -> Hex: 0x"); kprint(hex_buffer);
        kprint("\n");
        return;
    }
    if (strncmp(input, "rev", 3) == 0) {
        char *text = input + 3;
        if(*text == 0) {
            kprint("ERROR: No text\n");
            return;
        } 
        if(*text != ' '){
            kprint("Comanda necunoscuta: '"); kprint(input); kprint("'\n");
            return;
        }
        text++;
        if(*text == 0) {
            kprint("ERROR: No text\n");
            return;
        } 

        strrev(text);
        kprint("Revesed: "); kprint(text); kprint("\n");
        return;
    }


    if (strlen(input) > 0) {
        kprint("Comanda necunoscuta: '"); kprint(input); kprint("'\n");
        return;
    }
}