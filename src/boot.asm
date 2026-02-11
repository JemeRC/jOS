global start
extern kmain

BITS 16


start:
    cli                     ; Opreste Intreruperile 
    xor ax, ax              ; AX = 0
    mov ds, ax              ; DS = 0
    mov ss, ax              ; SS = 0
    mov sp, 0x7C00          ; SP = 0x7C00 (Seteaza Stiva sub Bootloader)

    lgdt [gdt_descriptor]   ; Incarcarea GDT (Global Descriptor Table)

    mov eax, cr0            ;
    or eax, 1               ; Activeaza Protected Mode
    mov cr0, eax            ; 

    jmp CODE_SEG:init_pm

;=========
;   GDT
;=========

gdt_start:
    dq 0x0000000000000000       ; Null Descriptor

gdt_code:
    dq 0x00CF9A000000FFFF       ; Code Segment

gdt_data:
    dq 0x00CF92000000FFFF       ; Data Segment

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

;=================
;   32-bit Code
;=================

BITS 32

init_pm:
    mov ax, DATA_SEG        ;
    mov ds, ax              ;
    mov ss, ax              ; Actualizarea registrelor de segment
    mov es, ax              ; pentru modul protejat
    mov fs, ax              ;   
    mov gs, ax              ;   

    mov esp, 0x90000        ; Mutarea Pointerului Stivei intr-un loc mai indepartat pentru siguranta

    call kmain              ; Apelarea Kernelului

    jmp $                   ; Bucla Infinita
