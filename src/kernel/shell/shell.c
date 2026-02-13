#include "shell.h"
#include "../../libc/include/string.h"
#include "../../libc/include/stdlib.h"
#include "../drivers/screen.h"
#include "../drivers/power.h"
#include "../include/system_data.h"


// Functie afisare status pentru systeminfo
void print_component_status(char* name, int status) {
    kprint("  [");
    if (status == 1) {
        kprint(" OK ");
    } else if (status == 0) {
        kprint("FAIL");
    } else {
        kprint(" -- ");
    }
    kprint("] ");
    kprint(name);
    kprint("\n");
}

void execute_command(char *input) {

    // --- Comanda HELP ---
    if (strcmp(input, "help") == 0) {
        kprint("Comenzi disponibile:\n");
        kprint("  info       - Informatii sistem si status hardware\n");
        kprint("  clear      - Curata ecranul\n");
        kprint("  hex <num>  - Converteste decimal in hex\n");
        kprint("  rev <txt>  - Inverseaza un text\n");
        kprint("  reboot     - Restarteaza calculatorul\n");
        kprint("  shutdown   - Inchide calculatorul\n");
        kprint("  boom       - BOMBA\n");
        return;
    } 

    // --- Comanda CLEAR ---
    if (strcmp(input, "clear") == 0) {
        clear_screen();
        return;
    }

    // --- Comanda INFO ---
    if (strcmp(input, "info") == 0) {
        kprint("\n================ SYSTEM REPORT ================\n");
        
        kprint("OS Name:    "); kprint(OS_NAME); kprint("\n");
        kprint("Version:    "); kprint(KERNEL_VERSION); kprint("\n");
        kprint("Arch:       "); kprint(ARCHITECTURE); kprint("\n");
        
        kprint("\n------------------ HARDWARE -------------------\n");
        
        // TODO: Sa o faci serioasa
        
        // Tastatura (Stim ca merge, ca tocmai am scris comanda)
        print_component_status("PS/2 Keyboard Driver", 1);
        
        // Ecran (Stim ca merge, ca vedem scrisul)
        print_component_status("VGA Text Mode (80x25)", 1);
        
        // Ceas (Stim ca nu merge, nu masuram nimic)
        print_component_status("CMOS Real Time Clock", -1); 

        kprint("===============================================\n\n");
        return;
    }

    // --- Comanda HEX ---
    if (strncmp(input, "hex", 3) == 0) {
        char *num_str = input + 3;
        if(*num_str == 0) { kprint("Eroare: Lipseste numarul.\n"); return; }
        if(*num_str != ' ') { kprint("Comanda necunoscuta.\n"); return; }
        num_str++;

        int val = atoi(num_str);
        char hex_buffer[32];
        itoa(val, hex_buffer, 16);
        
        kprint("Decimal: "); kprint(num_str);
        kprint(" -> Hex: 0x"); kprint(hex_buffer);
        kprint("\n");
        return;
    }

    // --- Comanda REV ---
    if (strncmp(input, "rev", 3) == 0) {
        char *text = input + 3;
        if(*text == 0 || *text != ' ') { kprint("Eroare.\n"); return; }
        text++;
        
        strrev(text);
        kprint("Invers: "); kprint(text); kprint("\n");
        return;
    }

    if (strcmp(input, "reboot") == 0) {
        reboot();
        return;
    }

    if(strcmp(input,"boom") == 0){
        shutdown();
        return;
    }

    if (strcmp(input, "shutdown") == 0) {
        shutdown();
        return;
    }

    // Comanda Necunoscuta
    kprint("Comanda necunoscuta: '"); 
    kprint(input); 
    kprint("'\nScrie 'help' pentru lista de comenzi.\n");
}