#ifndef ISR_H
#define ISR_H

#include "../../../libc/include/stdint.h"

// Asta este "poza" procesorului salvată pe stiva.
// Ordinea este CRITICA. Corespunde cu instrucțiunea 'pusha' din Assembly.
typedef struct {
    uint32_t ds;                                     // Data Segment (memoria de date)
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Regiștrii generali (salvați de pusha)
    uint32_t int_no, err_code;                       // Numărul întreruperii (ex: 32) și codul de eroare
    uint32_t eip, cs, eflags, useresp, ss;           // Salvați automat de procesor când apare întreruperea
} registers_t;

// [isr_t] este un pointer catre o functie care primește registers_t si nu returneaza nimic.
typedef void (*isr_t)(registers_t);

// Funcția prin care un driver (Timer, Keyboard) se "inscrie" pe lista
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif