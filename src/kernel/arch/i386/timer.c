#include "isr.h"
#include "../../drivers/ports.h"
#include "../../drivers/screen.h"
#include "../../../libc/include/stdlib.h"

// Variabila globala care tine timpul
uint32_t tick = 0;

// Functie pentru IRQ 0 (Int 32)
static void timer_callback(registers_t regs) {
    tick++;


    // Afisam un mesaj la fiecare secunda (aprox)
    // Presupunand 50Hz, 50 tick-uri = 1 secunda
    if (tick % 50 == 0) {
        kprint("Tick: ");
        char tick_ascii[256];
        itoa(tick, tick_ascii, 10);
        kprint(tick_ascii);
        kprint("\n");
    }
}

// Functia de initializare (se apeleaza o singura data in kernel.c)
void init_timer(uint32_t freq) {
    // Ne inregistram handler-ul la intreruperea 32 (IRQ0)
    register_interrupt_handler(32, timer_callback);

    // Programam cipul PIT

    // Ceasul intern bate la 1.193180 Mhz. Impartim la cat vrem noi.
    uint32_t divisor = 1193180 / freq;
    
    // Trimitem comenzile la porturile hardware
    port_byte_out(0x43, 0x36); 

    // Trebuie sa despartim numarul (divisor) in doi bytes (Low si High)
    uint8_t low  = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}