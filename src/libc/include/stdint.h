#ifndef _STDINT_H
#define _STDINT_H

// ============================================================================
// 1. TIPURI CU LATIME EXACTA (Exact-width integer types)
// ============================================================================

// 8-bit: -128 la 127 sau 0 la 255
typedef __INT8_TYPE__   int8_t;
typedef __UINT8_TYPE__  uint8_t;

// 16-bit: -32.768 la 32.767 sau 0 la 65.535
typedef __INT16_TYPE__  int16_t;
typedef __UINT16_TYPE__ uint16_t;

// 32-bit: -2.147.483.648 la  2.147.483.647 sau 0 la 4.294.967.296
typedef __INT32_TYPE__  int32_t;
typedef __UINT32_TYPE__ uint32_t;

// 64-bit: -9.223.372.036.854.775.808 la 9.223.372.036.854.775.807 sau 0 la 18.446.744.073.709.551.616
typedef __INT64_TYPE__  int64_t;
typedef __UINT64_TYPE__ uint64_t;

// ============================================================================
// 2. TIPURI PENTRU POINTERI (Integer types capable of holding object pointers)
// Isi schimba marimea automat (32 biți pe i386, 64 pe x64).
// ============================================================================

typedef __INTPTR_TYPE__  intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

// ============================================================================
// 3. TIPURI MINIME RAPIDE (Fastest minimum-width integer types)
// ============================================================================

typedef __INT_FAST8_TYPE__   int_fast8_t;
typedef __UINT_FAST8_TYPE__  uint_fast8_t;
typedef __INT_FAST16_TYPE__  int_fast16_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __INT_FAST32_TYPE__  int_fast32_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __INT_FAST64_TYPE__  int_fast64_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;

// ============================================================================
// 4. TIPURI PENTRU MĂRIMI MAXIME (Greatest-width integer types)
// ============================================================================

typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

// ============================================================================
// 5. LIMITE (LIMITS)
// ============================================================================

#define INT8_MIN    (-__INT8_MAX__ - 1)
#define INT8_MAX    (__INT8_MAX__)
#define UINT8_MAX   (__UINT8_MAX__)

#define INT16_MIN   (-__INT16_MAX__ - 1)
#define INT16_MAX   (__INT16_MAX__)
#define UINT16_MAX  (__UINT16_MAX__)

#define INT32_MIN   (-__INT32_MAX__ - 1)
#define INT32_MAX   (__INT32_MAX__)
#define UINT32_MAX  (__UINT32_MAX__)

#define INT64_MIN   (-__INT64_MAX__ - 1)
#define INT64_MAX   (__INT64_MAX__)
#define UINT64_MAX  (__UINT64_MAX__)


#define INTPTR_MIN  (-__INTPTR_MAX__ - 1)
#define INTPTR_MAX  (__INTPTR_MAX__)
#define UINTPTR_MAX (__UINTPTR_MAX__)


#define INTMAX_MIN  (-__INTMAX_MAX__ - 1)
#define INTMAX_MAX  (__INTMAX_MAX__)
#define UINTMAX_MAX (__UINTMAX_MAX__)


#define INT8_C(c)    c
#define INT16_C(c)   c
#define INT32_C(c)   c
#define INT64_C(c)   c ## LL

#define UINT8_C(c)   c
#define UINT16_C(c)  c
#define UINT32_C(c)  c ## U
#define UINT64_C(c)  c ## ULL

#define INTMAX_C(c)  c ## LL
#define UINTMAX_C(c) c ## ULL

#endif