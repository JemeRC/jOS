#ifndef PORTS_H
#define PORTS_H

// Extragerea Input-ului de la un respectiv Port
unsigned char port_byte_in(unsigned short port);

// Transmiterea Data-ului pe un respectiv Port
void port_byte_out(unsigned short port, unsigned char data);

void port_word_out(unsigned short port, unsigned short data);

#endif