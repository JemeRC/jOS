#include "drivers/screen.h"
#include "shell/shell.h"
#include "../libc/include/stdio.h"

__attribute__((section(".text.entry")))
void kmain() {
    clear_screen();
    char buffer[255];
    int index = 0;

    while (1) {
        printf("jOS> ");
        gets(buffer);
        execute_command(buffer);
    }
}
