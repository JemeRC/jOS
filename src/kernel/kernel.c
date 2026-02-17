#include "drivers/screen.h"
#include "arch/i386/idt.h"
#include "drivers/keyboard.h"
#include "shell/shell.h"
#include "../libc/include/stdio.h"

void kmain() {

    // Initializare Hardware
    clear_screen();
    set_idt();
    init_keyboard();
    
    // Activam intreruperile
    __asm__ __volatile__("sti");


    char input_buffer[256];


    while(1) {

        kprint("jOS> ");

        gets(input_buffer);        
        
        // Daca a dat enter gol
        if (input_buffer[0] == '\0') {
            continue;
        }
        execute_command(input_buffer);
    }
}