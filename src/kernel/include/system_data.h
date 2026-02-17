#ifndef SYSTEM_DATA_H
#define SYSTEM_DATA_H

// === OS INFO ===
#define OS_NAME "jOS"
#define KERNEL_VERSION "0.3"
#define ARCHITECTURE "x86 (32-bit Protected Mode)"

// === Memorie Video ===
#define VGA_MEMORY_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80

// === Porturi Ecran (Cursor) ===
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// === Porturi Tastatură ===
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

// === Culori VGA ===
enum vga_color {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_YELLOW = 14,
    COLOR_WHITE = 15,
};

#endif