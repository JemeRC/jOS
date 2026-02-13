#include "include/stdio.h"
#include "include/stdlib.h"
#include "../kernel/drivers/screen.h"
#include "../kernel/drivers/keyboard.h"


int putchar(int iChar){
    kprint_char( (char) iChar);
    return iChar;
}

int puts(const char *string){
    kprint( (char*) string);
    kprint_char('\n');
    return 1;
}


int printf(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            putchar(*format);
            written++;
            format++;
            continue;
        }

        format++; // Sarim peste '%'
        
        switch (*format) {
            case 'c': {
                char c = (char) va_arg(parameters, int);
                putchar(c);
                written++;
                break;
            }
            case 's': {
                const char *str = va_arg(parameters, const char*);

                kprint((char*) str);
                
                break;
            }
            case 'd': {
                int d = va_arg(parameters, int);

                char buffer[32];
                itoa(d, buffer, 10);
                char *ptr = buffer;
                
                written += kprint(buffer);
                break;
            }
            case 'x': {
                int x = va_arg(parameters, int);
                char buffer[34];
                buffer[0] = '0';
                buffer[1] = 'x';
                char *ptr = buffer;
                itoa(x, ptr + 2, 16);
                
                written += kprint(buffer);
                break;
            }
            default: {
                putchar('%');
                written++;
                break;
            }
        }
        format++;
    }

    va_end(parameters);
    return written;
}


int getchar(void){
    char c = get_input_char();
    return (int) c;
}

char* gets(char *buffer){
    int index = 0;
    char c;
    
    while(1){
        c = (char) getchar();

        if(c == '\b') {
            if(index > 0){
                index--;
                kprint("\b \b");
            }
            continue;
        }

        if(c == '\n') {
            buffer[index] = '\0';
            kprint_char('\n');
            return buffer;
        }

        buffer[index++] = c;
        kprint_char(c);
    }
}

_Bool isspace(char caracter){
    return (caracter == ' ' ? 1 : 0);
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