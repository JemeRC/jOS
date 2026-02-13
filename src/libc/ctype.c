#include "include/ctype.h"

// Tabelul de proprietăți pentru fiecare caracter ASCII (0-255)
const unsigned char _ctype_table[256] = {
    _C, _C, _C, _C, _C, _C, _C, _C,             
    _C, _S|_C, _S|_C, _S|_C, _S|_C, _S|_C, _C, _C, 
    _C, _C, _C, _C, _C, _C, _C, _C,             
    _C, _C, _C, _C, _C, _C, _C, _C,            
    _S, _P, _P, _P, _P, _P, _P, _P,          
    _P, _P, _P, _P, _P, _P, _P, _P,             
    _D, _D, _D, _D, _D, _D, _D, _D,            
    _D|_D, _D, _P, _P, _P, _P, _P, _P,         
    _P, _U|_X, _U|_X, _U|_X, _U|_X, _U|_X, _U|_X, _U, 
    _U, _U, _U, _U, _U, _U, _U, _U,             
    _U, _U, _U, _U, _U, _U, _U, _U,             
    _U, _U, _U, _P, _P, _P, _P, _P,             
    _P, _L|_X, _L|_X, _L|_X, _L|_X, _L|_X, _L|_X, _L, 
    _L, _L, _L, _L, _L, _L, _L, _L,             
    _L, _L, _L, _L, _L, _L, _L, _L,             
    _L, _L, _L, _P, _P, _P, _P, _C,             

    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


int tolower(int c) {
    if (isupper(c)) return c + 32;
    return c;
}

int toupper(int c) {
    if (islower(c)) return c - 32;
    return c;
}