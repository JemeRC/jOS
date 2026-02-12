#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "shell/shell.h"

__attribute__((section(".text.entry")))
void kmain() {
    clear_screen();
    kprint("                                                                 Version: [0.2] \n");
    kprint("jOS> ");

    char buffer[255];
    int index = 0;

    while (1) {
        
        char c = get_input_char();
        
        char entry_str[2] = {c, '\0'};
        kprint(entry_str);

        if (c == '\n') {
            buffer[index] = '\0';
            
            execute_command(buffer);
            index = 0;
            kprint("jOS> ");
        } else if ( c == '\b' ){
            if( index > 0 ) index--;
        } else{
            if (index < 254) {
                buffer[index] = c;
                index++;
            }
        }
    }
}
