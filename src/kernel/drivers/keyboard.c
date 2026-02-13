#include "keyboard.h"
#include "ports.h"
#include "../include/system_data.h"

// STATE VARIABILES
static int shift_active = 0;
static int caps_lock_active = 0;


char get_letter_case(char lowercase) {
    
    // XOR intre SHIFT si CAPS
    if (shift_active != caps_lock_active) {
        return lowercase - 32; // Conversie in litera mare (ASCII)
    }
    return lowercase;
}

char scancode_to_ascii(unsigned char scancode) {
    switch (scancode) {
        // Randul I
        case 0x02: return shift_active ? '!' : '1';
        case 0x03: return shift_active ? '@' : '2';
        case 0x04: return shift_active ? '#' : '3';
        case 0x05: return shift_active ? '$' : '4';
        case 0x06: return shift_active ? '%' : '5';
        case 0x07: return shift_active ? '^' : '6';
        case 0x08: return shift_active ? '&' : '7';
        case 0x09: return shift_active ? '*' : '8';
        case 0x0A: return shift_active ? '(' : '9';
        case 0x0B: return shift_active ? ')' : '0';
        case 0x0C: return shift_active ? '_' : '-';
        case 0x0D: return shift_active ? '+' : '=';
        case 0x0E: return '\b'; // Backspace

        // Randul II
        case 0x0F: return '\t'; // Tab
        case 0x10: return get_letter_case('q');
        case 0x11: return get_letter_case('w');
        case 0x12: return get_letter_case('e');
        case 0x13: return get_letter_case('r');
        case 0x14: return get_letter_case('t');
        case 0x15: return get_letter_case('y');
        case 0x16: return get_letter_case('u');
        case 0x17: return get_letter_case('i');
        case 0x18: return get_letter_case('o');
        case 0x19: return get_letter_case('p');
        
        case 0x1A: return shift_active ? '{' : '[';
        case 0x1B: return shift_active ? '}' : ']';
        case 0x1C: return '\n'; // Enter

        // Randul III
        case 0x1E: return get_letter_case('a');
        case 0x1F: return get_letter_case('s');
        case 0x20: return get_letter_case('d');
        case 0x21: return get_letter_case('f');
        case 0x22: return get_letter_case('g');
        case 0x23: return get_letter_case('h');
        case 0x24: return get_letter_case('j');
        case 0x25: return get_letter_case('k');
        case 0x26: return get_letter_case('l');
        
        case 0x27: return shift_active ? ':' : ';';
        case 0x28: return shift_active ? '"' : '\'';
        case 0x29: return shift_active ? '~' : '`';

        // Randul IV
        case 0x2B: return shift_active ? '|' : '\\';
        case 0x2C: return get_letter_case('z');
        case 0x2D: return get_letter_case('x');
        case 0x2E: return get_letter_case('c');
        case 0x2F: return get_letter_case('v');
        case 0x30: return get_letter_case('b');
        case 0x31: return get_letter_case('n');
        case 0x32: return get_letter_case('m');
        
        case 0x33: return shift_active ? '<' : ',';
        case 0x34: return shift_active ? '>' : '.';
        case 0x35: return shift_active ? '?' : '/';
        

        case 0x39: return ' '; // Space

        default: return 0;
    }
}

char get_input_char() {
    char c = 0;
    
    while(1) {
        unsigned char status = port_byte_in(KEYBOARD_STATUS_PORT);
        
        if (status & 0x01) {
            unsigned char scancode = port_byte_in(KEYBOARD_DATA_PORT);


            // SHIFT [pressed]
            if (scancode == 0x2A || scancode == 0x36) {
                shift_active = 1;
                continue;
            }
            // SHIFT [released]
            if (scancode == 0xAA || scancode == 0xB6) {
                shift_active = 0;
                continue;
            }

            // CAPSLOCK [toggle] 
            if (scancode == 0x3A) {
                caps_lock_active = !caps_lock_active;
                continue;
            }
            
            // Ignoram Key Release-urile
            if (scancode & 0x80) {
                continue;
            }

            c = scancode_to_ascii(scancode);

            if (c != 0) {
                return c;
            }
        }
    }
}