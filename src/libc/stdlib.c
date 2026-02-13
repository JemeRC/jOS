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

char* itoa(int value, char *string, int base) {
    
    // Limitare Baze
    if (base < 2 || base > 36) {
        *string = '\0';
        return string;
    }

    char *ptr = string;
    char *start = string;
    
    unsigned int uValue;
    
    if (base == 10 && value < 0) {
        *ptr++ = '-';
        start++; 

        // Pentru cazul in care value este INT_MIN
        uValue = (unsigned int)(-(value + 1)) + 1;

    } else {
        uValue = (unsigned int)value;
    }

    do {
        unsigned char digit = uValue % base;
        *ptr++ = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        uValue /= base;
    } while (uValue != 0);

    *ptr = '\0';

    char *end = ptr - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    return string;
}

int abs(int x){
    return ( x < 0 ? -x : x);
}


int strtol(const char *str, char **endptr, int base) {
    
    // Validare baza
    if (base < 2 || base > 36) {
        return 0;
    }

    // Sarim peste spatii (whitespace)
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r') {
        str++;
    }

    // Verificam semnul
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Sarim peste prefixe

    // Binar
    if(base == 2 && str[0] == '0' && (str[1] == 'b' || str[1] == 'B')){
        str += 2;
    }

    // Octal
    if(base == 8 && str[0] == '0'){
        str++;
    }

    // Hexa
    if (base == 16 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str += 2;
    }


    int result = 0;
    
    while (*str) {
        int digit;
        char c = *str;

        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'a' && c <= 'z') {
            digit = c - 'a' + 10;
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            break; 
        }

        // Verificare daca cifra este valida pentru baza
        if (digit >= base) {
            break;
        }

        result = result * base + digit;
        str++;
    }

    if (endptr) {
        *endptr = (char *)str;
    }

    return result * sign;
}