#ifndef _SETJMP_H
#define _SETJMP_H

#include "stdint.h"

// -------------------------------------------------------------------------
// 1. x86 (32-bit)
// ------------------------------------------------------------------------- 
#if defined(__i386__)

    // Context:
    // - EBX, ESI, EDI, EBP, ESP, EIP (6 regiștri)

    typedef struct {
        uint32_t __regs[6]; 
    } jmp_buf[1];

// -------------------------------------------------------------------------
// 2. x86_64 (64-bit) 
// ------------------------------------------------------------------------- 
#elif defined(__x86_64__)

    // Context System V ABI:
    // - RBX, RBP, R12, R13, R14, R15, RSP, RIP (8 regiștri)
    
    typedef struct {
        uint64_t __regs[8];
    } jmp_buf[1];

/* -------------------------------------------------------------------------
   3. ARM (32-bit)
   ------------------------------------------------------------------------- */
#elif defined(__arm__)
    
    // Context ARM standard:
    // - R4-R11 (General Purpose)
    // - SP (Stack Pointer), LR (Link Register - adresa de retur)
    // - De multe ori se rezerva spatiu si pentru registre VFP (Floating Point) D8-D15.
    // Alocam un buffer generos de 64 uint32 pentru siguranta (inclusiv FPU).

    typedef struct {
        uint32_t __regs[64];
    } jmp_buf[1];

/* -------------------------------------------------------------------------
   4. ARM64 (64-bit)
   ------------------------------------------------------------------------- */
#elif defined(__aarch64__)

    // Context ARM64:
    // - X19-X29 (Callee-saved registers)
    // - SP, LR
    // - D8-D15 (FPU callee-saved)
    // Alocam spatiu pentru 32 de uint64 (acopera tot + aliniere).

    typedef struct {
        uint64_t __regs[32];
    } jmp_buf[1];

/* -------------------------------------------------------------------------
   5. RISC-V (32-bit si 64-bit)
   ------------------------------------------------------------------------- */
#elif defined(__riscv)
    
    // Context RISC-V:
    // - s0-s11 (Callee saved)
    // - ra (Return address), sp (Stack pointer)
    // - fs0-fs11 (Floating point callee saved)
    // Total cam 26-28 registre.
     
    #if __riscv_xlen == 64
        typedef struct { uint64_t __regs[32]; } jmp_buf[1];
    #else
        typedef struct { uint32_t __regs[32]; } jmp_buf[1];
    #endif

/* -------------------------------------------------------------------------
   6. Fallback 
   ------------------------------------------------------------------------- */
#else
    #error "Arhitectura procesorului nu este suportata momentan in setjmp.h"
#endif


/* Salveaza starea procesorului. Returneaza 0 direct. */
int setjmp(jmp_buf env);

/* Restaureaza starea. Returneaza val != 0 la locul apelului setjmp. */
void longjmp(jmp_buf env, int val) __attribute__((noreturn));

#endif