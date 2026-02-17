[bits 32]
[extern kmain]      ; Definim ca exista o functie externa in C numita kmain

global _start       ; Punctul de intrare (pentru linker, optional dar util)

_start:
    call kmain      ; Chemam functia principala din kernel.c
    jmp $           ; Daca kmain se termina (return), blocam procesorul aici