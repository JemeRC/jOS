#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#define EOF (-1)

// -----------------
//      OUTPUT
// -----------------

// - Scrie un singur caracter pe ecran
// 
// - Primeste INT [ic]
// - Returneaza INT
int putchar(int iChar);

// - Afiseaza STRING [*string] pe ecran
//
// - Returneaza valoarea 1 daca a reusit
int puts(const char *string);

// - Printeaza STRING-ul [*format] avand posibilitatea de a adauga valorile variabilelor in afisare;
//
// - Returneaza numarul de caractere scrise
//
// - Suporta urmatoarele idenfiticatoare:
//      -> %c - CHAR
//      -> %s - STRING
//      -> %d - INT
//      -> %x - HEX
int printf(const char *format, ...);


// -----------------
//      INPUT
// -----------------


// - Citeste un CHAR de la tastatura
// 
// - Returneaza caracterul prin INT
int getchar(void);

// - Citeste o linie intreaga pana la enter si le salveaza intr-un STRING [*buffer]
//
// - Returneaza POINTER la STRING [*buffer]
char* gets(char *buffer);

// - Citeste STRING-ul [*format] avand posibilitatea de a citi mai multe variabile deodata
int scanf(const char *format, ...);

#endif