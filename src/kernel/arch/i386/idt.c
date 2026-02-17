#include "idt.h"
#include "../../drivers/ports.h"

// IDT = Interrupt Descriptor Table

// Declaram ISR-urile
// ISR = Interrupt Service Routine
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Declaram IRQ-urile 
// IRQ = Interrupt Request
extern void irq0();
extern void irq1();

// Tabelul propriu-zis
idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;


// Functie ajutatoare sa scriem o intrare in tabel
void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = (uint16_t)(handler & 0xFFFF);           // Luam partea de jos a adresei
    idt[n].sel = KERNEL_CS;                                     // Selectam segmentul de cod kernel
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;                                        // 0x8E = 10001110 (Present, Ring0, Int Gate)
    idt[n].high_offset = (uint16_t)((handler >> 16) & 0xFFFF);  // Luam partea de sus a adresei
}

void set_idt() {
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    // -- Reprogramarea PIC-ului --
    // In mod implicit, IRQ 0-7 sunt mapate pe INT 0-7
    // Dar INT 0-7 sunt deja ocupate de erorile CPU (Divide by Zero, ...)
    // Trebuie sa mutam PIC-ul sa inceapa de la 32

    // Ports:
    //  -> 0x20 Master PIC - Command (Comanda)
    //  -> 0x21 Master PIC - Data (Parametrii)
    //  -> 0xA0 Slave PIC - Command (Comanda)
    //  -> 0xA1 Slave PIC - Data (Parametrii)


    // P1: Initializare
    port_byte_out(0x20, 0x11);  // 0001 0001
    port_byte_out(0xA0, 0x11);  // primul byte semnifica initializarea
                                           // al doilea byte semnifica existenta P4

    // P2: Remapare
    port_byte_out(0x21, 0x20);  // Master Data -> 0x20  (IRQ0 = INT 32; IRQ1 = INT 33; ...)
    port_byte_out(0xA1, 0x28);  // Slave Data -> 0x28   (IRQ8 = INT 40; IRQ9 = INT 41; ...)

    // P3: Legarea
    port_byte_out(0x21, 0x04);  // 0000 0100; Spune ca are Slave la Pinul IRQ 2
    port_byte_out(0xA1, 0x02);  // 0000 0010; Spune ca Identitatea lui este IRQ 2

    // Environment (8086 mode)
    port_byte_out(0x21, 0x01);  // 0x01 semnifica 8086 Mode
    port_byte_out(0xA1, 0x01);  // PIC putea fi folosit si la alte tipuri de procesoare

    // Masks (0 = activ, 1 = dezactivat)
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);


    // Exceptiile CPU (0-31)
    set_idt_gate(0 , (uint32_t)isr0 );
    set_idt_gate(1 , (uint32_t)isr1 );
    set_idt_gate(2 , (uint32_t)isr2 );
    set_idt_gate(3 , (uint32_t)isr3 );
    set_idt_gate(4 , (uint32_t)isr4 );
    set_idt_gate(5 , (uint32_t)isr5 );
    set_idt_gate(6 , (uint32_t)isr6 );
    set_idt_gate(7 , (uint32_t)isr7 );
    set_idt_gate(8 , (uint32_t)isr8 );
    set_idt_gate(9 , (uint32_t)isr9 );
    set_idt_gate(10, (uint32_t)isr10);
    set_idt_gate(11, (uint32_t)isr11);
    set_idt_gate(12, (uint32_t)isr12);
    set_idt_gate(13, (uint32_t)isr13);
    set_idt_gate(14, (uint32_t)isr14);
    set_idt_gate(15, (uint32_t)isr15);
    set_idt_gate(16, (uint32_t)isr16);
    set_idt_gate(17, (uint32_t)isr17);
    set_idt_gate(18, (uint32_t)isr18);
    set_idt_gate(19, (uint32_t)isr19);
    set_idt_gate(20, (uint32_t)isr20);
    set_idt_gate(21, (uint32_t)isr21);
    set_idt_gate(22, (uint32_t)isr22);
    set_idt_gate(23, (uint32_t)isr23);
    set_idt_gate(24, (uint32_t)isr24);
    set_idt_gate(25, (uint32_t)isr25);
    set_idt_gate(26, (uint32_t)isr26);
    set_idt_gate(27, (uint32_t)isr27);
    set_idt_gate(28, (uint32_t)isr28);
    set_idt_gate(29, (uint32_t)isr29);
    set_idt_gate(30, (uint32_t)isr30);
    set_idt_gate(31, (uint32_t)isr31);

     // Mapam IRQ-urile (32+)
    set_idt_gate(32, (uint32_t)irq0);
    set_idt_gate(33, (uint32_t)irq1);

     // Incarcam tabelul in procesor
    __asm__ __volatile__("lidt (%0)" : : "r" (&idt_reg));
}
