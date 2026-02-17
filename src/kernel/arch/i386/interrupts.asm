[bits 32]

; Functii din C
[extern isr_handler]    ; Interrupt Service Routine Handler
[extern irq_handler]    ; Interrupt Request         Handler

; ===============================================
; ISR = Interrupt Service Routine
; ===============================================

; --- DEFINIREA INTRETUPERILOR [ISR] ---

; ISR_NOERRCODE = Intrerupere simpla (fara cod de eroare de la CPU)

; Unele intreruperi (ex: Division by Zero) NU pun automat un cod de eroare pe stiva.
; Asa ca il punem manual (0) ca stiva sa arate la fel mereu.
%macro ISR_NOERRCODE 1
    global isr%1
    isr%1:
        cli             ; Oprim intreruperile
        push byte 0     ; Dummy error code
        push byte %1    ; Numarul intreruperii (ex: 0)
        jmp isr_common_stub
%endmacro

; ISR_ERRCODE = Intrerupere unde CPU-ul pune singur un cod de eroare pe stiva

; Alte intreruperi (ex: Page Fault) pun ele singure un cod de eroare.
; Nu mai avem nevoie de dummy error code (0).
%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0  ; Divide by Zero
ISR_NOERRCODE 1  ; Debug
ISR_NOERRCODE 2  ; NMI
ISR_NOERRCODE 3  ; Breakpoint
ISR_NOERRCODE 4  ; Overflow
ISR_NOERRCODE 5  ; Bounds
ISR_NOERRCODE 6  ; Invalid Opcode
ISR_NOERRCODE 7  ; Device Not Available
ISR_ERRCODE   8  ; Double Fault (Are error code!)
ISR_NOERRCODE 9  ; Coprocessor Segment Overrun
ISR_ERRCODE   10 ; Invalid TSS
ISR_ERRCODE   11 ; Segment Not Present
ISR_ERRCODE   12 ; Stack-Segment Fault
ISR_ERRCODE   13 ; General Protection Fault (GPF) -> Celebra eroare
ISR_ERRCODE   14 ; Page Fault
ISR_NOERRCODE 15 ; Reserved
ISR_NOERRCODE 16 ; x87 FPU Error
ISR_ERRCODE   17 ; Alignment Check
ISR_NOERRCODE 18 ; Machine Check
ISR_NOERRCODE 19 ; SIMD Floating-Point Exception
ISR_NOERRCODE 20 ; Virtualization Exception
ISR_NOERRCODE 21 ; Reserved
ISR_NOERRCODE 22 ; Reserved
ISR_NOERRCODE 23 ; Reserved
ISR_NOERRCODE 24 ; Reserved
ISR_NOERRCODE 25 ; Reserved
ISR_NOERRCODE 26 ; Reserved
ISR_NOERRCODE 27 ; Reserved
ISR_NOERRCODE 28 ; Reserved
ISR_NOERRCODE 29 ; Reserved
ISR_ERRCODE   30 ; Security Exception
ISR_NOERRCODE 31 ; Reserved

; ----------------------------------------

isr_common_stub:
    pusha           ; Salveaza EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI (Toata starea CPU)

    mov ax, ds      ; Salveaza segmentul de date
    push eax

    mov ax, 0x10    ; Incarca segmentul de date Kernel (0x10)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler ; Apel la functia din C 

    pop eax         ; Restaureaza segmentul vechi
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa            ; Restaureaza regiștrii generali (EAX, etc.)
    add esp, 8      ; Curata stiva (scoate error code si ISR number)
    sti             ; Porneste intreruperile la loc
    iret            ; Return special din intrerupere

; ----------------------------------------


; ===============================================
; IRQ = Interrupt Request (Intreruperi Hardware)
; ===============================================

; --- DEFINIREA INTRETUPERILOR [IRQ] ---

; IRQ = Cereri Hardware (Timer, Tastatura)

%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push byte 0
        push byte %2
        jmp irq_common_stub
%endmacro

IRQ 0,  32
IRQ 1,  33


; ----------------------------------------

irq_common_stub:
    pusha           ; Salveaza EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI (Toata starea CPU)

    mov ax, ds      ; Salveaza segmentul de date
    push eax

    mov ax, 0x10    ; Incarca segmentul de date Kernel (0x10)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call irq_handler ; <--- Apel la functia din C (Hardware)
    
    pop eax         ; Restaureaza segmentul vechi
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa            ; Restaureaza regiștrii generali (EAX, etc.)
    add esp, 8      ; Curata stiva (scoate error code si IRQ number)
    sti             ; Porneste intreruperile la loc
    iret            ; Return special din intrerupere

; ----------------------------------------


