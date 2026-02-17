#include "isr.h"
#include "../../drivers/screen.h"
#include "../../drivers/ports.h"
#include "../../../libc/include/stdlib.h"

// Lista care leaga fiecare intrerupere de procesor primita, cu Handler-ul respectiv 
isr_t interrupt_handlers[256];

// Functie cu care vom lega o Intrerupere cu un Handler
void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

// Handler pentru Errori CPU (Impartire la zero, Page Fault, etc)
void isr_handler(registers_t r) {
    kprint("INT ERR: ");
    char s[3];
    itoa(r.int_no, s, 10);
    kprint(s);
    kprint("\n");
}

// PIC = Programmable Interrupt Controller

// Handler pentru Hardware (Timer, Tastatura)
void irq_handler(registers_t r) {
    // PASUL 1: Notificam PIC-ul ca am primit mesajul (End of Interrupt - EOI)
    // Daca nu facem asta, PIC-ul se blocheaza si nu mai trimite nimic.

    // Daca a venit de la Slave PIC (intreruperi > 40), ii zicem si lui "Gata".
    if (r.int_no >= 40) {
        port_byte_out(0xA0, 0x20);
    }

    // Master PIC primeste mereu "Gata" (0x20 e comanda EOI).
    port_byte_out(0x20, 0x20);

    // PASUL 2: Cautam in lista cine se ocupa de asta
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r); // Executam functia
    }
}