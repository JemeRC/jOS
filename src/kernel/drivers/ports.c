#include "ports.h"

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;

    // Cod Complicat
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));          
    // in DE_UNDE, REZULTAT
    //  -> DE_UNDE este port-ul transmis in registrul DX
    //  -> REZULTAT este in ce registru se obtine rezultatul
    //
    // Valorile in Parantezele Rotunde () semnifica respectivele variabile unde se salveaza, sau se extrage valoarea
    
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
    // out CE, UNDE
    //  -> CE este ce valoare vom trimite
    //  -> UNDE este pe ce port vom trimite
}