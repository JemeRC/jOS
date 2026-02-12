#ifndef STDLIB_H
#define STDLIB_H

#include "stddef.h"

// - ASCII to INT
// 
// - Conversteste un STRING [*string] intr-un INT si il returneaza
int atoi(const char *string);

// - INT to ASCII
//
// - Converteste un INT [value] intr-o baza [base], si il pune intr-un STRING [*str]
//
// - Retureaza POINTER la STRING-ul [*string] modificat
char* itoa(int value, char *string, int base);

// - Partea intreaga a numarului x
int abs(int x);

#endif