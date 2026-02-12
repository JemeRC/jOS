#include "include/stdlib.h"
#include "include/string.h"

int atoi(const char *string){
    int number = 0;
    char isNegative = 0;
    if( *string == '-' ){
        isNegative = 1;
        string++;
    } 
    while( '0' <= *string && *string <= '9' ){
        number = number * 10 + (*string - '0');
        string++;
    }
    return number * (isNegative == 1 ? -1 : 1);
}

char* itoa(int value, char *string, int base){
    
    // Limitare Baze
    if ( base < 2 || base > 36 ){
        *string = '\0';
        return string; 
    }

    // Valoarea 0
    if( value == 0 ){
        string[0] = '0';
        string[1] = '\0';
        return string;
    }
    
    char *start = string;
    char isNegative = 0;

    // Daca avem baza 10, ii vom pune -
    if( value < 0 && base == 10 ){
        isNegative = 1;
        value = -value;
    } 

    unsigned int uValue = (unsigned int) value;

    while( uValue != 0 ){
        char result = uValue % base;
        
        if( result > 9 )
            *string++ = (result - 10) + 'a';
        else
            *string++ = result + '0';
        
        uValue /= base;
    }

    if( isNegative ) *string++ = '-';

    *string = '\0';

    return strrev(start);
}

int abs(int x){
    return ( x < 0 ? -x : x);
}
