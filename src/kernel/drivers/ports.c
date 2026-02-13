#include "ports.h"

// Citim un byte de la un port (versiunea sigura cu inb)
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    // "Nd" permite portului sa fie o constanta (0-255) sau in registrul DX
    __asm__("inb %1, %0" : "=a" (result) : "Nd" (port));
    return result;
}

// Scriem un byte la un port (versiunea sigura cu outb)
void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("outb %0, %1" : : "a" (data), "Nd" (port));
}

// Scrie un WORD (16 biti) la un port
void port_word_out(unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}