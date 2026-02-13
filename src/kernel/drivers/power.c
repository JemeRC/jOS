#include "power.h"
#include "ports.h"
#include "screen.h"

void shutdown() {
    kprint("Shutting down...\n");

    // QEMU modern
    port_word_out(0x604, 0x2000);
    
    // Bochs si QEMU vechi
    port_word_out(0xB004, 0x2000);
    
    // VirtualBox
    port_word_out(0x4004, 0x3400);

    // Daca suntem pe hardware real si codurile de mai sus nu merg:
    kprint("\nIt is now safe to turn off your computer.\n");
    asm("cli"); // Opreste intreruperile
    asm("hlt"); // Opreste CPU-ul
}

void reboot() {
    kprint("System is rebooting...\n");
    
    unsigned char good = 0x02;
    while (good & 0x02)
        good = port_byte_in(0x64);
        
    port_byte_out(0x64, 0xFE);
    
    // Daca nu merge, oprim procesorul
    asm("hlt");
}