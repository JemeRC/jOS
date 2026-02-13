#include "screen.h"
#include "ports.h"
#include "../include/system_data.h"

// Pozitia Cursor-ului
static int cursor_col = 0;
static int cursor_row = 0;

void update_cursor(int row, int col) {
    cursor_row = row;
    cursor_col = col;
    unsigned short position = (row * MAX_COLUMNS) + col;

    port_byte_out(REG_SCREEN_CTRL, 0x0F);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(position & 0xFF));
    port_byte_out(REG_SCREEN_CTRL, 0x0E);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)((position >> 8) & 0xFF));
}

void clear_screen() {
    char* video_memory = (char*) VGA_MEMORY_ADDRESS;
    int screen_size = MAX_ROWS * MAX_COLUMNS * 2;
    
    for (int i = 0; i < screen_size; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = COLOR_WHITE;
    }
    update_cursor(0, 0);
}

static void handle_scrolling() {
    if (cursor_row < MAX_ROWS) return;

    char* video_memory = (char*) VGA_MEMORY_ADDRESS;
    
    for (int i = 0; i < (MAX_ROWS - 1) * MAX_COLUMNS * 2; i++) {
        video_memory[i] = video_memory[i + (MAX_COLUMNS * 2)];
    }

    int last_row_offset = (MAX_ROWS - 1) * MAX_COLUMNS * 2;
    for (int i = last_row_offset; i < MAX_ROWS * MAX_COLUMNS * 2; i += 2) {
        video_memory[i] = ' ';       
        video_memory[i+1] = COLOR_WHITE; 
    }

    cursor_row = MAX_ROWS - 1;
}

void kprint_char(char character) {
    char *video_memory = (char*) VGA_MEMORY_ADDRESS;

    if (character == '\n') {
        cursor_col = 0;
        cursor_row++;
    } 
    else if (character == '\b') {

        if (cursor_col > 0) {
            cursor_col--;

            int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
            video_memory[offset] = ' ';
            video_memory[offset + 1] = COLOR_WHITE;
        }
    } 
    else {
        int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
        video_memory[offset] = character;
        video_memory[offset + 1] = COLOR_WHITE;
        cursor_col++;
    }

    if (cursor_col >= MAX_COLUMNS) {
        cursor_col = 0;
        cursor_row++;
    }

    // Scroll
    handle_scrolling();

    update_cursor(cursor_row, cursor_col);
}

int kprint(char* message) {
    int i = 0;
    while (message[i] != 0) {
        kprint_char(message[i++]);
    }
    return i;
}