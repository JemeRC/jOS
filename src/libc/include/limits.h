#ifndef _LIMITS_H
#define _LIMITS_H

// Versiunea standardului C23 pentru limits.h 
#define __STDC_VERSION_LIMITS_H__ 202311L

// Numarul de biti intr-un 'char' (byte)
#define CHAR_BIT    __CHAR_BIT__

// =========================================================================
// 1. CARACTERE (char, signed char, unsigned char)
// ========================================================================= 

// Latimea in biti
#define CHAR_WIDTH  CHAR_BIT
#define SCHAR_WIDTH CHAR_BIT
#define UCHAR_WIDTH CHAR_BIT

// Valori minime si maxime
#define SCHAR_MAX   __SCHAR_MAX__
#define SCHAR_MIN   (-SCHAR_MAX - 1)
#define UCHAR_MAX   (SCHAR_MAX * 2 + 1)

#ifdef __CHAR_UNSIGNED__
    #define CHAR_MAX UCHAR_MAX
    #define CHAR_MIN 0
#else
    #define CHAR_MAX SCHAR_MAX
    #define CHAR_MIN SCHAR_MIN
#endif

// Numarul maxim de bytes intr-un caracter multibyte (pentru locale)
#define MB_LEN_MAX  16 

// =========================================================================
// 2. SHORT (short int)
// =========================================================================

#define SHRT_WIDTH  __SHRT_WIDTH__

#define SHRT_MAX    __SHRT_MAX__
#define SHRT_MIN    (-SHRT_MAX - 1)
#define USHRT_MAX   (SHRT_MAX * 2U + 1U)
#define USHRT_WIDTH __SHRT_WIDTH__

// =========================================================================
// 3. INT (int)
// ========================================================================= 

#define INT_WIDTH   __INT_WIDTH__

#define INT_MAX     __INT_MAX__
#define INT_MIN     (-INT_MAX - 1)
#define UINT_MAX    (INT_MAX * 2U + 1U)
#define UINT_WIDTH  __INT_WIDTH__

// =========================================================================
// 4. LONG (long int)
// ========================================================================= 

#define LONG_WIDTH  __LONG_WIDTH__

#define LONG_MAX    __LONG_MAX__
#define LONG_MIN    (-LONG_MAX - 1L)
#define ULONG_MAX   (LONG_MAX * 2UL + 1UL)
#define ULONG_WIDTH __LONG_WIDTH__

// =========================================================================
// 5. LONG LONG (long long int)
// =========================================================================

#define LLONG_WIDTH  __LLONG_WIDTH__

#define LLONG_MAX    __LONG_LONG_MAX__
#define LLONG_MIN    (-LLONG_MAX - 1LL)
#define ULLONG_MAX   (LLONG_MAX * 2ULL + 1ULL)
#define ULLONG_WIDTH __LLONG_WIDTH__

// =========================================================================
// 6. TIPURI C23 (_Bool, _BitInt)
// ========================================================================= 

// _Bool
#define BOOL_MAX    1
#define BOOL_WIDTH  1

// _BitInt
#ifdef __BITINT_MAXWIDTH__
    #define BITINT_MAXWIDTH __BITINT_MAXWIDTH__
#else
    #define BITINT_MAXWIDTH LLONG_WIDTH
#endif

#endif