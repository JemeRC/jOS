#ifndef _CTYPE_H
#define _CTYPE_H

// Definim biții pentru fiecare proprietate
#define _U  0x01    // Upper case (A-Z)             00000001
#define _L  0x02    // Lower case (a-z)             00000010
#define _D  0x04    // Digit (0-9)                  00000100
#define _S  0x08    // Space (space, tab, newline)  00001000
#define _P  0x10    // Punctuation                  00010000
#define _C  0x20    // Control characters           00100000
#define _X  0x40    // Hex digit (A-F, a-f)         01000000

extern const unsigned char _ctype_table[256];

#define isalpha(c)  (_ctype_table[(unsigned char)(c)] & (_U|_L))
#define isupper(c)  (_ctype_table[(unsigned char)(c)] & _U)
#define islower(c)  (_ctype_table[(unsigned char)(c)] & _L)
#define isdigit(c)  (_ctype_table[(unsigned char)(c)] & _D)
#define isxdigit(c) (_ctype_table[(unsigned char)(c)] & (_D|_X))
#define isspace(c)  (_ctype_table[(unsigned char)(c)] & _S)
#define ispunct(c)  (_ctype_table[(unsigned char)(c)] & _P)
#define isalnum(c)  (_ctype_table[(unsigned char)(c)] & (_U|_L|_D))
#define isprint(c)  (!(_ctype_table[(unsigned char)(c)] & _C))
#define iscntrl(c)  (_ctype_table[(unsigned char)(c)] & _C)

int tolower(int c);
int toupper(int c);

#endif