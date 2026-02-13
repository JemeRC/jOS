[org 0x7c00]
BITS 16

KERNEL_OFFSET equ 0x1000    ; Adresa Kernelului

start:
    mov [BOOT_DRIVE], dl    ; BIOS salveaza ID-ul unitatii de boot in DL

    cli                     ; Fara Intreruperi
    xor ax, ax              ; AX = 0
    mov ds, ax              ; DS = 0
    mov es, ax              ; ES = 0
    mov ss, ax              ; SS = 0
    mov sp, 0x7C00          ; SP = 0x7C00 (Seteaza Stiva sub Bootloader)

    call load_kernel        ; Incarcam Kernelul pe Disk

    lgdt [gdt_descriptor]   ; Incarcarea GDT (Global Descriptor Table)

    mov eax, cr0            ;
    or eax, 1               ; Activeaza Protected Mode
    mov cr0, eax            ; 

    jmp CODE_SEG:init_pm

;------------------------------------------------------------------------------
; Incarcare Kernel
;------------------------------------------------------------------------------
load_kernel:
    mov bx, KERNEL_OFFSET   ; ES:BX = 0x0000:0x1000
    mov dh, 20              
    mov dl, [BOOT_DRIVE]    
    call disk_load
    ret

;------------------------------------------------------------------------------
; Disk Load
;------------------------------------------------------------------------------
disk_load:
    push dx                 ; Salvăm DH (numărul de sectoare cerute)
    mov ah, 0x02            ; BIOS read sector function
    mov al, dh              ; Numar de sectoare de citit
    mov ch, 0x00            ; Cilindrul 0
    mov dh, 0x00            ; Capul 0
    mov cl, 0x02            ; Sector 2
    
    int 0x13                ; Apel BIOS
    
    jc disk_error           ; Salt dacă Carry Flag e setat (eroare hardware)

    pop dx                  ; Recuperăm DX original (DH = sectoare cerute)
    cmp dh, al              ; COMPARĂM: sectoare cerute (DH) vs sectoare citite (AL)
    jne disk_error          ; Dacă nu sunt egale, eroare de citire
    ret

disk_error:
    mov ah, 0x0e
    mov al, 'D'             ; Afisam 'D' pentru Disk Error
    int 0x10
    jmp $

;------------------------------------------------------------------------------
; GDT - Global Descriptor Table
;------------------------------------------------------------------------------
gdt_start:
    dq 0x0000000000000000   ; Null Descriptor

gdt_code:
    dq 0x00CF9A000000FFFF   ; Code Segment

gdt_data:
    dq 0x00CF92000000FFFF   ; Data Segment

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

;------------------------------------------------------------------------------
; 32-bit Protected Mode
;------------------------------------------------------------------------------
BITS 32

init_pm:
    mov ax, DATA_SEG        ; Actualizam registrele de segment
    mov ds, ax              
    mov ss, ax              
    mov es, ax              
    mov fs, ax              
    mov gs, ax              

    mov esp, 0x90000        ; Setam noua stiva in modul protejat

    call KERNEL_OFFSET      ; Pornim Kernelul

    jmp $                   ; Blocaj in caz de return din kernel

BOOT_DRIVE db 0             

times 510-($-$$) db 0       
dw 0xaa55