#ifndef STRING_H_
#define STRING_H_

#include "stddef.h"


// - Calculeaza lungimea unui STRING dat [*string]
//
// - Returneaza lungimea ca un INT
size_t strlen(const char *string);


// - Copiaza intr-un STRING [*destinationString], toate elementele dintr-un alt STRING [*copyString]
//
// - Returneaza POINTER la STRING-ul modificat [*destinationString]
//
// - Se vor pierde valorile suprapuse in primul STRING [*destinationString]
char* strcpy(char *destinationString, const char *copyString);


// - Copiaza intr-un STRING [*destinationString], primele elemente [*numberOfElements] dintr-un alt STRING [*copyString]
// 
// - Returneaza POINTER la STRING-ul modificat [*destinationString]
//
// - Se vor pierde valorile suprapuse in primul STRING [*destinationString]
char* strncpy(char *destinationString, const char *copyString, size_t numberOfElements);



// - Concateneaza la sfarsitului primului STRING [*firstString], al doilea STRING [*secondString]
//
// - Returneaza POINTER la STRING-ul modificat [*firstString]
//
// - Va adauga NULL la final pentru siguranta
char* strcat(char *firstString, const char *secondString);


// - Concateneaza la sfarsitului primului STRING [*firstString], primele elemente [numberOfElements] al celui de al doilea STRING [*secondString]
//
// - Returneaza POINTER la STRING-ul modificat [*firstString]
//
// - Va adauga NULL la final pentru siguranta
char* strncat(char *firstString, const char *secondString, size_t numberOfElements);

// - Compara primul STRING [*firstString], cu al doilea STRING [*secondString]
//
// - Valoarea returnata este de tip INT si va respecta urmatoarele conditii:
//      -> (> 0), daca primul STRING [*firstString] este mai mare lexicografic;
//      -> (< 0), daca al doilea STRING [*secondString] este mai mare lexicografic;
//      -> (= 0), daca STRING-urile sunt egale.
int strcmp(const char *firstString, const char *secondString);

// - Compara primele elemente [numberOfElements] ale primului STRING [*firstString], cu elementele celui de al doilea STRING [*secondString]
//
// - Valoarea returnata este de tip INT si va respecta urmatoarele conditii:
//      -> (> 0), daca primul STRING [*firstString] este mai mare lexicografic;
//      -> (< 0), daca al doilea STRING [*secondString] este mai mare lexicografic;
//      -> (= 0), daca STRING-urile sunt egale.
int strncmp(const char *firstString, const char *secondString, size_t numberOfElements);



// - Cauta CHAR-ul [caracter] in STRING-ul [*string] dat
//
// - Returneaza un POINTER la locatia unde a fost gasit CHAR-ul [caracter] in STRING [*string]
// 
// - In cazul in care nu se afla CHAR-ul [caracter] in STRING [*string], functia va returna NULL
// 
// - Cautarea se face de la stanga la dreapta ( --> )
char* strchr(const char *string, char caracter);



// - Cauta CHAR-ul [caracter] in STRING-ul [*string] dat
//
// - Returneaza un POINTER la locatia unde a fost gasit CHAR-ul [caracter] in STRING [*string]
// 
// - In cazul in care nu se afla CHAR-ul [caracter] in STRING [*string], functia va returna NULL
// 
// - Cautarea se face de la dreapta la stanga ( <-- )
char* strrchr(const char *string, char caracter);       // De la dreapta


// - Cauta STRING-ul [*searchedString] in STRING-ul [*searchLocationString] dat
//
// - Returneaza un POINTER la locatia unde a fost gasit al doilea STRING [*searchedString] in primul STRING [*searchLocationString]
// 
// - In cazul in care nu se afla STRING-ul [*searchedString] in STRING-ul [*searchLocationString], functia va returna NULL
// 
// - Cautarea se face de la stanga la dreapta ( --> )
char* strstr(const char *searchLocationString,const char *searchedString);

// - Inverseasa ordinea caracterelor din STRING [*string]
//
// - Returneaza POINTER la STRING-ul [*string] modificat
char* strrev(char *string);


#endif