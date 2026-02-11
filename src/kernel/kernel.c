#include "drivers/screen.h"
#include "drivers/keyboard.h"

__attribute__((section(".text.entry")))
void kmain() {
    clear_screen();
    kprint("| jOS | Version: 0.1 \n\n");
    kprint("Test Input: ");

    // Buffer
    char buffer[255];
    int index = 0;

    while (1) {
        
        // Asteptam primirea unui caracter de la tastatura
        char c = get_input_char();
        
        // Il vom afisa pe ecran
        char str[2] = {c, '\0'};
        kprint(str);

        // Dacă e Enter, trecem la rând nou și resetăm bufferul (aici vei procesa comanda)
        if (c == '\n') {
            kprint("Final String: ");
            buffer[index] = '\0';
            kprint(buffer);
            kprint("\nTest Input: ");
            index = 0;
        } else {
            // Il salvam in buffer
            buffer[index] = c;
            index++;
        }
    }
}