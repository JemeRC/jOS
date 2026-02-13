; src/libc/arch/i386/setjmp.asm
; Implementare setjmp/longjmp pentru x86 (32-bit)
; Format: ELF

global setjmp
global longjmp

section .text

; -----------------------------------------------------------------------------
; int setjmp(jmp_buf env);
;
; Salveaza contextul curent in buffer-ul 'env'.
; Returneaza 0.
;
; Stack layout la intrare:
; [ESP + 4] -> pointer catre 'env' (jmp_buf)
; [ESP    ] -> adresa de retur (EIP)
; -----------------------------------------------------------------------------
setjmp:
    ; 1. Luam pointerul catre structura jmp_buf din stiva
    mov eax, [esp + 4]      ; eax = env

    ; 2. Salvam registrii "callee-saved" (EBX, ESI, EDI, EBP)
    ; Acesti registrii trebuie pastrati intacti intre apeluri de functii
    mov [eax + 0], ebx      ; env[0] = ebx
    mov [eax + 4], esi      ; env[1] = esi
    mov [eax + 8], edi      ; env[2] = edi
    mov [eax + 12], ebp     ; env[3] = ebp

    ; 3. Salvam Stack Pointer-ul (ESP)
    ; Atentie: Vrem ESP-ul de dinainte de apelul setjmp (adica unde e stiva caller-ului).
    ; Acum ESP pointeaza la adresa de retur. Deci caller-ul avea ESP + 4.
    lea ecx, [esp + 4]
    mov [eax + 16], ecx     ; env[4] = esp (calculat)

    ; 4. Salvam Instruction Pointer-ul (EIP)
    ; EIP-ul (adresa de retur) se afla fix in varful stivei acum [esp].
    mov ecx, [esp]
    mov [eax + 20], ecx     ; env[5] = eip (return address)

    ; 5. Returnam 0
    xor eax, eax            ; eax = 0
    ret

; -----------------------------------------------------------------------------
; void longjmp(jmp_buf env, int val);
;
; Restaureaza contextul salvat si sare inapoi la setjmp.
; setjmp va returna 'val'.
;
; Stack layout:
; [ESP + 8] -> val
; [ESP + 4] -> pointer catre 'env'
; [ESP    ] -> adresa de retur (ignorata, ca nu ne mai intoarcem aici)
; -----------------------------------------------------------------------------
longjmp:
    ; 1. Luam argumentele
    mov edx, [esp + 4]      ; edx = env
    mov eax, [esp + 8]      ; eax = val

    ; 2. Verificam daca 'val' este 0.
    ; Standardul C spune ca longjmp nu poate returna 0.
    ; Daca userul da longjmp(env, 0), setjmp trebuie sa returneze 1.
    test eax, eax
    jnz .val_ok             ; Daca nu e 0, sari peste incrementare
    inc eax                 ; Daca e 0, fa-l 1
.val_ok:

    ; 3. Restauram registrii din buffer
    mov ebx, [edx + 0]      ; ebx = env[0]
    mov esi, [edx + 4]      ; esi = env[1]
    mov edi, [edx + 8]      ; edi = env[2]
    mov ebp, [edx + 12]     ; ebp = env[3]
    
    ; 4. Restauram stiva (CRITIC!)
    mov esp, [edx + 16]     ; esp = env[4]

    ; 5. Sarim la vechea adresa (EIP)
    ; Nu folosim 'ret' pentru ca am schimbat deja stiva.
    ; Pur si simplu sarim la adresa stocata in buffer.
    jmp [edx + 20]          ; sari la env[5]