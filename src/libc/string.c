#include "include/string.h"

size_t strlen(const char *string){
    const char *save = string;
    while( *string ) string++ ;
    return string - save;
}



char* strcpy(char *destinationString, const char *copyString){
    char *start = destinationString;
    while( (*destinationString++ = *copyString++) );
    return start; 
}


char* strncpy(char *destinationString, const char *copyString, size_t numberOfElements){
    size_t i;
    for( i = 0; i < numberOfElements && copyString[i] != '\0'; i++){
        destinationString[i] = copyString[i];
    }
    while( i < numberOfElements ){
        destinationString[i] = '\0';
        i++;
    }
    return destinationString;
}



char* strcat(char *firstString, const char *secondString){
    char *save = firstString;
    while(*firstString) firstString++;
    while((*firstString++ = *secondString++));
    return save;
}


char* strncat(char *firstString, const char *secondString, size_t numberOfElements){
    char *save = firstString;
    while(*firstString) firstString++;
    while( numberOfElements-- && *secondString ) *firstString++ = *secondString++;
    *firstString = '\0';
    return save;
}



int strcmp(const char *firstString, const char *secondString){
    while( *firstString != 0 && (*firstString == *secondString) ){
        firstString++; secondString++;  
    }
    return (unsigned char) *firstString - (unsigned char) *secondString;
}


int strncmp(const char *firstString,const char *secondString, size_t numberOfElements){
    while( *firstString != 0 && (*firstString == *secondString) && numberOfElements){
        firstString++; secondString++;  numberOfElements--;
    }
    if( numberOfElements == 0 ) return 0;
    return (const unsigned char) *firstString - (const unsigned char) *secondString;
}



char* strchr(const char *string, const char caracter){
    while( *string != caracter ){
        if( *string == 0 ) return NULL;
        string++;
    }
    return (char*) string;
}


char* strrchr(const char *string, int caracter){
    const char *last = NULL;
    do{
        if( *string == caracter ) last = string;
        string++;
    }while(*string);

    return (char*) last;
}



char* strstr(const char *searchLocationString, const char *searchedString){
    if(!*searchedString) return (char*) searchLocationString;

    while( *searchLocationString ){
        const char *firstPointer = searchLocationString,
                   *secondPointer = searchedString;
        while( *firstPointer && *secondPointer && ( *firstPointer == *secondPointer )){
            firstPointer++; secondPointer++;
        }
        if( *secondPointer == 0 ) return (char*)searchLocationString;  
        searchLocationString++;
    }

    return NULL;
}

char* strrev(char *string){
    if(!string) return NULL;

    size_t i = 0;
    size_t j = strlen(string) - 1;
    while( i < j ){
        char aux = string[i];
        string[i] = string[j];
        string[j] = aux;
        i++; j--;
    }

    return string;
}
