#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/ctype.h"
#include "include/stdarg.h"
#include "../kernel/drivers/screen.h"
#include "../kernel/drivers/keyboard.h"


int puts(const char *string){
    return kprint((char*) string);
}

int putchar(int iChar){
    char s[2] = { (char)iChar, '\0'};
    kprint(s);
    return iChar;
}    

#define PRINTF_BUFFER_SIZE 1024
int printf(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);

    char buffer[PRINTF_BUFFER_SIZE];
    int buffer_index = 0;
    int total_written = 0;


    #define FLUSH_BUFFER() { \
        buffer[buffer_index] = '\0'; \
        total_written += kprint(buffer); \
        buffer_index = 0; \
    }

    #define PUT_CHAR(c) { \
        buffer[buffer_index++] = (c); \
        if (buffer_index >= PRINTF_BUFFER_SIZE - 1) FLUSH_BUFFER(); \
    }

    while (*format != '\0') {
        if (*format != '%') {
            PUT_CHAR(*format);
            format++;
            continue;
        }

        format++; // Sărim peste '%'

        // Gestionare cazuri
        switch (*format) {
            case 'c': { // Character
                char c = (char) va_arg(parameters, int);
                PUT_CHAR(c);
                break;
            }
            case 's': { // String
                const char *str = va_arg(parameters, const char*);
                while (*str) {
                    PUT_CHAR(*str++);
                }
                break;
            }
            case 'd': { // Integer (Decimal)
                int d = va_arg(parameters, int);
                char temp_buf[32];
                itoa(d, temp_buf, 10);
                char *ptr = temp_buf;
                while (*ptr) {
                    PUT_CHAR(*ptr++);
                }
                break;
            }
            case 'x': { // Integer (heXadecimal)
                int x = va_arg(parameters, int);
                char temp_buf[32];
                PUT_CHAR('0'); 
                PUT_CHAR('x');
                itoa(x, temp_buf, 16);
                char *ptr = temp_buf;
                while (*ptr) {
                    PUT_CHAR(*ptr++);
                }
                break;
            }
            default: {
                PUT_CHAR('%');
                PUT_CHAR(*format);
                break;
            }
        }
        format++;
    }

    if (buffer_index > 0) {
        FLUSH_BUFFER();
    }

    va_end(parameters);
    return total_written;
}
int getchar(void){
    return (int) keyboard_read_char();
}

char* gets(char *buffer){
    int index = 0;
    char c;
    
    while(1){
        c = (char) getchar();

        if(c == 0) continue;
        if(c == '\b') {
            if(index > 0){
                index--;
            }
            continue;
        }

        if(c == '\n') {
            buffer[index] = '\0';
            return buffer;
        }

        if (index < 254) { 
            buffer[index++] = c;
        }
    }
}

int scanf(const char *format, ...){
    va_list args;
    va_start(args, format);

    int items_read = 0;
    char buffer[100];

    while (*format) {
        if (isspace(*format)) {
            format++;
            continue;
        }

        if (*format != '%') {
            format++;
            continue;
        }

        format++; // Sarim peste '%'

        // 1. STRING (%s)
        if (*format == 's') {
            char *destination = va_arg(args, char*);
            char c;
            
            // Sarim peste spatiile initiale
            while (isspace(c = (char)getchar()));
            
            int i = 0;
            do {
                destination[i++] = c;
                kprint_char(c);
                c = (char)getchar();
            } while(!isspace(c));

            destination[i] = '\0';
            items_read++;
        }
        
        // 2. INTEGER (%d)
        else if (*format == 'd') {
            int *destination = va_arg(args, int*);
            char c;
            int i = 0;

            // Sarim peste spatiile initiale
            while (isspace(c = (char)getchar()));

            // Minus
            if (c == '-') {
                buffer[i++] = c;
                kprint_char(c);
                c = (char)getchar();
            }

            // Citim cat timp sunt cifre
            while (c >= '0' && c <= '9') {
                buffer[i++] = c;
                kprint_char(c);
                c = (char)getchar();
            }
            buffer[i] = '\0';
            
            *destination = atoi(buffer);
            items_read++;
        }

        // 3. HEX (%x)
        else if (*format == 'x') {
            int *destination = va_arg(args, int*);
            char c;
            int i = 0;
            
            while (isspace(c = (char)getchar()));

            // Citim cat timp sunt caractere hex (0-9, a-f, A-F)
            while ((c >= '0' && c <= '9') || 
                   (c >= 'a' && c <= 'f') || 
                   (c >= 'A' && c <= 'F')) {
                buffer[i++] = c;
                kprint_char(c);
                c = (char)getchar();
            }
            buffer[i] = '\0';

            *destination = strtol(buffer, 0, 16);

            items_read++;
        }
        
        // 4. CHAR (%c)
        else if (*format == 'c') {
            char *destination = va_arg(args, char*);
            char c = (char)getchar();
            *destination = c;
            kprint_char(c); 
            items_read++;
        }

        format++;
    }

    va_end(args);
    return items_read;
}