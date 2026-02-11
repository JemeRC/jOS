#ifndef SCREEN_H
#define SCREEN_H

// Curata Ecranul de Textul anterior afisat
void clear_screen();

// Printarea pe Consola a unui String
void kprint(char* message);

// Printarea pe Consola la o anumita locatie
void kprint_at(char* message, int col, int row);

#endif