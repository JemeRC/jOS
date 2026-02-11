#include "keyboard.h"
#include "ports.h"
#include "../include/system_data.h"

unsigned char keyboard_map[128] = {

    [0x02] = '1', [0x03] = '2', [0x04] = '3', [0x05] = '4',
    [0x06] = '5', [0x07] = '6', [0x08] = '7', [0x09] = '8',
    [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=',

    [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r',
    [0x14] = 't', [0x15] = 'y', [0x16] = 'u', [0x17] = 'i',
    [0x18] = 'o', [0x19] = 'p', [0x1A] = '[', [0x1B] = ']',

    [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f',
    [0x22] = 'g', [0x23] = 'h', [0x24] = 'j', [0x25] = 'k',
    [0x26] = 'l', [0x27] = ';', [0x28] = '\'', [0x29] = '`',

    [0x2B] = '\\', [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c',
    [0x2F] = 'v',  [0x30] = 'b', [0x31] = 'n', [0x32] = 'm',
    [0x33] = ',',  [0x34] = '.', [0x35] = '/',

    [0x39] = ' ',  // Space
    

    // Taste Speciale
    [0x01] = 0x1B, // ESC (ASCII Escape)
    [0x0E] = '\b', // Backspace
    [0x0F] = '\t', // TAB
    [0x1C] = '\n', // ENTER

    // Numpad
    [0x37] = '*',
    [0x47] = '7', [0x48] = '8', [0x49] = '9', [0x4A] = '-',
    [0x4B] = '4', [0x4C] = '5', [0x4D] = '6', [0x4E] = '+',
    [0x4F] = '1', [0x50] = '2', [0x51] = '3',
    [0x52] = '0', [0x53] = '.',

    // F_ Keys
    [0x3B] =  0 , [0x3C] =  0 , [0x3D] =  0 , [0x3E] = 0,
    [0x3F] =  0 , [0x40] =  0 , [0x41] =  0 , [0x42] = 0,
    [0x43] =  0 , [0x44] =  0 , [0x57] =  0 , [0x58] = 0,

    // Modificatori
    [0x2A] =  0 ,       // Shift Stânga
    [0x36] =  0 ,       // Shift Dreapta
    [0x1D] =  0 ,       // Control Stânga
    [0x38] =  0 ,       // Alt Stânga
    [0x3A] =  0 ,       // Caps Lock
    
    //Locks
    [0x45] =  0 ,       // Num Lock
    [0x46] =  0         // Scroll Lock
};

char get_input_char() {
    unsigned char scancode;
    
    while (1) {
        if (port_byte_in(KEYBOARD_STATUS_PORT) & 1) {
            scancode = port_byte_in(KEYBOARD_DATA_PORT);
            
            // Tasta nu mai este apasata daca apare 1 la bitul 8 ( mai exact & 0x80 este adevarat)
            if (scancode & 0x80) continue;

            // Daca cumva dam pe afara din tabel
            if (scancode > 58) continue; 

            char c = keyboard_map[scancode];
            if (c != 0) return c;
        }
    }
}