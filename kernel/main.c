#include <stdint.h>
#include "console.h"
#include "keyboard.h"
#include "interrupts.h"
#include "../desktop/desktop.h"
#include "../apps/terminal/terminal.h"
#include "../apps/settings/settings.h"
#include "../apps/explorer/explorer.h"
#include "../apps/device_manager/device_manager.h"
static void halt(void){for(;;)__asm__ volatile("cli;hlt");}
void kmain(uint32_t magic,uint32_t info){(void)info;console_clear();console_write("========================================\n              NeoOS 26\n                v0.3\n========================================\n\n");if(magic!=0x2BADB002){console_write("BOOT ERROR: invalid Multiboot magic.\n");halt();}console_write("Kernel:             ONLINE\nArchitecture:       x86-64 target\nInterrupts:         INITIALIZING...\n");interrupts_init();console_write("Interrupts:         ONLINE\n");keyboard_init();console_write("Keyboard:           ONLINE\nDesktop:            INITIALIZING...\n");desktop_init();console_write("Desktop:            ONLINE\n");terminal_app_open();settings_app_open();explorer_app_open();device_manager_open();console_write("\nNeoOS 26 v0.3 is running.\nneoos> ");halt();}
