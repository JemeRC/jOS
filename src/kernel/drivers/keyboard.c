#include "keyboard.h"
#include "ports.h"
#include "../arch/i386/isr.h"
#include "../../libc/include/stdbool.h"
#include "screen.h"
#include <ctype.h>

// --- BUFFER CONFIGURATION ---
#define KEYBOARD_BUFFER_SIZE 256
char key_buffer[KEYBOARD_BUFFER_SIZE];
uint8_t buffer_write_ptr = 0;
uint8_t buffer_read_ptr = 0;

// --- STATE MANAGEMENT ---
bool shift_active = false;
bool caps_lock_active = false;

// Scan Codes Speciale
#define SC_LSHIFT       0x2A
#define SC_RSHIFT       0x36
#define SC_CAPSLOCK     0x3A
#define SC_ENTER        0x1C
#define SC_BACKSPACE    0x0E


// Tabelul 1: Taste Normale (Litere mici, Numere)
const char sc_ascii[] = {
    '0', '`', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\b', '\t',     
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',     
    'o', 'p', '[', ']', '\n', '\0', 'a', 's',     
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',     
    '\'', '`', '0', '\\', 'z', 'x', 'c', 'v',     
    'b', 'n', 'm', ',', '.', '/', '0', '0',    
    '0', ' '
};

static char get_shifted(char c) {
    switch(c) {
        case '1': return '!';
        case '2': return '@';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '^';
        case '7': return '&';
        case '8': return '*';
        case '9': return '(';
        case '0': return ')';
        case '-': return '_';
        case '=': return '+';
        case '[': return '{';
        case ']': return '}';
        case ';': return ':';
        case '\'': return '"';
        case '`': return '~';
        case '\\': return '|';
        case ',': return '<';
        case '.': return '>';
        case '/': return '?';
        default: return c;
    }
}


// Functia se apeleaza la apasarea unei taste
static void keyboard_callback(registers_t regs) {
    
    // Citim starea tastaturii, in cazul in care nici o tasta nu este apasata vom primi Scan Code-ul 0.
    uint8_t scancode = port_byte_in(0x60);
    
    if (scancode & 0x80) {
        // Scadem 0x80 ca sa vedem ce tasta a fost ridicata
        uint8_t released_key = scancode - 0x80;

        if (released_key == SC_LSHIFT || released_key == SC_RSHIFT) {
            shift_active = false;
        }
        return; 
    }

    // --- SHIFT ---
    if (scancode == SC_LSHIFT || scancode == SC_RSHIFT) {
        shift_active = true;
        return; // Nu punem shift in buffer
    }

    // --- CAPS LOCK ---
    if (scancode == SC_CAPSLOCK) {
        caps_lock_active = !caps_lock_active; // Toggle (On/Off)
        return;
    }

    if (scancode > 57) return; // Ignoram taste necunoscute

    char letter = sc_ascii[scancode];

    if(isalpha(letter) && (shift_active != caps_lock_active))
        letter = toupper(letter);
    else
        if(shift_active){
            if(isalpha(letter)) 
                letter = toupper(letter);
            else letter = get_shifted(letter);
        }
    
    kprint_char(letter);

    if (letter != 0) {
        key_buffer[buffer_write_ptr] = letter;
        buffer_write_ptr++; // Overflow natural la 256
    }

}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_callback); 
}

char keyboard_read_char() {

    // Buffer gol
    if (buffer_read_ptr == buffer_write_ptr) {
        return 0;
    }

    // Luam litera
    char c = key_buffer[buffer_read_ptr];
    
    // Incrementam pointerul de citire
    buffer_read_ptr++;

    return c;
}