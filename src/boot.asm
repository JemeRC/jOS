hang:
    jmp hang

times 512-($-$$) db 0
db 0x55
db 0xAA