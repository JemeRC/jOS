#include "screen.h"
#include "ports.h"
#include "../include/system_data.h"

// Pozitia Cursorului
static int cursor_col = 0;
static int cursor_row = 0;

// Mutarea Cursorului intr-o anumita Locatie
void update_cursor(int row, int col) {

    cursor_row = row;
    cursor_col = col;
    
    //Convertirea Locatiei Date intr-o Adresa de Memorie
    unsigned short position = (row * MAX_COLUMNS) + col;
    
    // Cursorul in Registri Ecranului va fi impartit in doi Bytes

    // --Low Byte--
    // Semnalam registrul Ecranului ca vom modifica Low Byte-ul Cursour-ului
    port_byte_out(REG_SCREEN_CTRL, 0x0F); 

    // Si modificam Low Byte cu Noua Adresa
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(position & 0xFF));
    

    // --High Byte--
    // Semnalam registrul Ecranului ca vom modifica High Byte-ul Cursor-ului
    port_byte_out(REG_SCREEN_CTRL, 0x0E);

    // Si modificam High Byte cu Noua Adresa
    port_byte_out(REG_SCREEN_DATA, (unsigned char)((position >> 8) & 0xFF));
}

// Curatarea Ecranului
void clear_screen() {
    char* video_memory = (char*) VGA_MEMORY_ADDRESS;
    
    // Calcularea Elementului Vectorului unde se afla Monitorul
    int screen_size = MAX_ROWS * MAX_COLUMNS * 2;
    
    // Setam fiecare element al Vectorului cu Spatiu 
    for (int i = 0; i < screen_size; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = COLOR_WHITE;
    }

    // Resetam Cursor-ul la pozitia 0,0
    update_cursor(0, 0);
}

static void handle_scrolling() {
    // Daca cursorul a trecut de ultima linie (24)
    if (cursor_row >= MAX_ROWS) {
        
        char* video_memory = (char*) VGA_MEMORY_ADDRESS;
        
        // P1: Mutam Ecranul cu un rand mai sus
        for (int i = MAX_COLUMNS * 2; i < (MAX_ROWS - 1) * MAX_COLUMNS * 2; i++) {
            video_memory[i] = video_memory[i + (MAX_COLUMNS * 2)];
        }

        // P2: Curatam ultimul rand

        // Calculam pozitia ultimului rand
        int last_row_offset = (MAX_ROWS - 1) * MAX_COLUMNS * 2;
        
        // Incepem sa il acoperim
        for (int i = last_row_offset; i < MAX_ROWS * MAX_COLUMNS * 2; i += 2) {
            video_memory[i] = ' ';       
            video_memory[i+1] = COLOR_WHITE; 
        }

        // P3: Pozitionam cursor-ul pe ultima linie
        cursor_row = MAX_ROWS - 1;
    }
}

void kprint_char(char character){
    char *video_memory = (char*) VGA_MEMORY_ADDRESS;
    if (character == '\n') {
            cursor_col = 0;
            cursor_row++;
    } else if (character == '\b') { 
        if (cursor_col > 5) { // ! HARDCODED !
            cursor_col--;
            int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
            video_memory[offset] = ' '; 
            video_memory[offset + 1] = COLOR_WHITE;
        }
    } else {
        int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
        video_memory[offset] = character;
        video_memory[offset + 1] = COLOR_WHITE;
        cursor_col++;
    }

    if (cursor_col >= MAX_COLUMNS) {
        cursor_col = 0;
        cursor_row++;
    }
    
    if (cursor_row >= MAX_ROWS) handle_scrolling();

    update_cursor(cursor_row, cursor_col);
}

int kprint(char* message) {

    char* video_memory = (char*) VGA_MEMORY_ADDRESS;
    int writtenCharacters = 0;
    int i = 0;
    
    while (message[i] != 0) {

        if (message[i] == '\n') {
            cursor_col = 0;
            cursor_row++;
        } else if (message[i] == '\b') { 
            if (cursor_col > 5) { // ! HARDCODED !
                cursor_col--;
                int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
                video_memory[offset] = ' '; 
                video_memory[offset + 1] = COLOR_WHITE;
                writtenCharacters--;
            }
        } else {
            int offset = (cursor_row * MAX_COLUMNS + cursor_col) * 2;
            video_memory[offset] = message[i];
            video_memory[offset + 1] = COLOR_WHITE;
            cursor_col++;
            writtenCharacters++;
        }

        if (cursor_col >= MAX_COLUMNS) {
            cursor_col = 0;
            cursor_row++;
        }
        
        if (cursor_row >= MAX_ROWS) handle_scrolling();
        i++;
    }

    update_cursor(cursor_row, cursor_col);
    return writtenCharacters;
}

