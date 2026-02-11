[ORG 0x7c00]    ; Pointer DS la 0x7C00

xor ax, ax      ; AX = 0
mov ds, ax      ; DS = 0

cld             ; DF = 0, Direction Flag (directia in care se deplaseaza pointerii)
                        ;  -> 0 = Pointerii Cresc (inc)
                        ;  -> 1 = Pointerii Scad  (dec)

mov si, msg     ; Pointer SI la MSG

call bios_print

hang:
    jmp hang        ; Loop Infinit pentru a bloca Procesorul


bios_print:
    lodsb           ; Al = [SI]
                    ; SI = SI + 1
    or al, al       ; daca AL = 0 atunci ZF = 1 (Zero Flag)
    jz done         ; JZ = Jump daca ZF = 1
    
    mov ah, 0x0E    ;
    mov bh, 0       ; Setup Printare prin BIOS
    int 0x10        ;
    
    jmp bios_print  ; Loop
done:
    ret


msg db 'Hello World', 13, 10, 0     ; Mesaj de Afisare

times 510-($-$$) db 0   ; Esential pentru a putea fi indetificat
db 0x55                 ; de BIOS ca un BootSector
db 0xAA                 ;