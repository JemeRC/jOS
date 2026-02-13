#ifndef _STDARG_H
#define _STDARG_H

// Variable Arguments List
typedef __builtin_va_list va_list;


// * va_start(ap, last): Inițializează lista de argumente 'ap'. 
// 'last' este numele ultimului parametru fix al funcției.
#define va_start(ap, last) __builtin_va_start(ap, last)

// * va_arg(ap, type): Returnează următorul argument din listă, 
// considerând că are tipul 'type'.
#define va_arg(ap, type) __builtin_va_arg(ap, type)

/* * va_end(ap): Curăță lista de argumente. 
 * Pe unele arhitecturi e obligatoriu apelul acesta.
 */
#define va_end(ap) __builtin_va_end(ap)

/* * va_copy(dest, src): Copiază lista de argumente.
 * Util dacă vrei să parcurgi argumentele de două ori.
 */
#define va_copy(dest, src) __builtin_va_copy(dest, src)

#endif // _STDARG_H