#ifndef IDT_H
#define IDT_H

#include "../../../libc/include/stdint.h"

// Segmentul de cod al Kernel-ului (Definit de Bootloader/GDT)
#define KERNEL_CS 0x08 

// Structura unei intrari in IDT (Interrupt Gate)
typedef struct {
    uint16_t low_offset;  // Primii 16 biti ai adresei functiei handler
    uint16_t sel;         // Selectorul de Segment Kernel (0x08)
    uint8_t always0;      // Acest byte trebuie sa fie mereu 0
    uint8_t flags;        // Proprietati (Prezenta, Privilegii, Tip)
                                // Bit 7: "Present"
                                // Bit 5-6: "Privilege" (0=Kernel, 3=User)
                                // Bit 0-4: "Type" (0xE = 32-bit Interrupt Gate)
    uint16_t high_offset; // Ultimii 16 biti ai adresei
} __attribute__((packed)) idt_gate_t;
// __attribute__((packed)) e CRUCIAL: Ii spune compilatorului sa NU adauge spatii goale intre variabile
// Hardware-ul citeste bit cu bit, daca avem spatii, crapa

// Structura Pointer-ului IDT
// Asta e structura pe care o dam procesorului ca sa stie unde e tabelul
typedef struct {
    uint16_t limit;         // Mărimea tabelului = (cati bytes are) - 1
    uint32_t base;          // Adresa de inceput a tabelului
} __attribute__((packed)) idt_register_t;

// Vectorul IDT (256 de intrari posibile)
#define IDT_ENTRIES 256

// Functii
void set_idt();
void set_idt_gate(int n, uint32_t handler);

#endif