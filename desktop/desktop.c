#include <stdint.h>
#include "desktop.h"
#include "../kernel/console.h"
static int mouse_x = 512;
static int mouse_y = 384;
void desktop_init(void) {
    console_write("\nNeoOS 26 Desktop\n");
    console_write("-----------------\n");
    console_write("NeoOS   File   Edit   View                 Wi-Fi  Sound  Battery\n\n");
    console_write("                       Desktop\n\n");
    console_write("      [Terminal] [Explorer] [Settings] [Device Manager]\n\n");
    console_write("                    [  Dock  ]\n");
}
void desktop_render(void) {}
void desktop_mouse_move(int dx, int dy) { mouse_x += dx; mouse_y += dy; if(mouse_x<0)mouse_x=0; if(mouse_y<0)mouse_y=0; if(mouse_x>1023)mouse_x=1023; if(mouse_y>767)mouse_y=767; }
void desktop_mouse_click(uint8_t button) { (void)button; }
