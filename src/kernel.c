#define VIDEO_MEMORY 0xB8000
#define MAX_ROWS 25
#define MAX_COLOUMS 80

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_YELLOW = 14,
    VGA_COLOR_WHITE = 15,
};

// Foreground = Culoarea Textului | Background = Culoarea Fundalului
static inline char vga_color_creator(enum vga_color Foreground, enum vga_color Background){
    return Foreground | (Background << 4);
}

void clear_screen(char* video){
    int screen_size = MAX_ROWS * MAX_COLOUMS * 2;

    for(int i = 0; i < screen_size; i += 2){
        video[i] = ' ';
        video[i+1] = 0x00;
    }
}

void kmain(){
    char* video = (char*) 0xB8000;
    char defaultFontColor = vga_color_creator(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    char defaultErrorColor = vga_color_creator(VGA_COLOR_RED, VGA_COLOR_BLACK);

    clear_screen(video);

    video[0] = 'j';
    video[1] = vga_color_creator(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    video[2] = 'O';
    video[3] = defaultFontColor;
    video[4] = 'S';
    video[5] = defaultFontColor;

    while(1);
}