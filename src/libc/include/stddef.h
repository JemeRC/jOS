#ifndef _STDDEF_H
#define _STDDEF_H

// NULL pointer
#ifndef NULL
#define NULL ((void*)0)
#endif

// Rezultatul scaderii a doi pointeri (signed)
#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef int ptrdiff_t;
#endif

// Rezultatul operatorului sizeof (unsigned)
#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

// Wide Character Type
#ifndef _WCHAR_T
#define _WCHAR_T
typedef int wchar_t;
#endif

// Offset-ul unui membru într-o structură
#define offsetof(type, member) ((size_t) &((type *)0)->member)

#endif