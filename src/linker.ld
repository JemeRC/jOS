ENTRY(start)

SECTIONS
{
    . = 0x7C00;

    .text :
    {
        *(.text)
    }

    .data :
    {
        *(.data)
    }
    .rodata :
    {
        *(.rodata)
    }

    .sig : AT(0x7C00 + 510)
    {
        SHORT(0xAA55);
    }
}