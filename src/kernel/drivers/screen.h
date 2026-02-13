#ifndef SCREEN_H
#define SCREEN_H

// Curata Ecranul de Textul anterior afisat
void clear_screen();

void kprint_char(char caracter);

// - Printeaza pe consola un STRING [*message]
//
// - Returneaza numarul de caractere vizibile (ignora \n, scade \b)
int kprint(char* message);

// Printarea pe Consola la o anumita locatie
void kprint_at(char* message, int col, int row);

#endif