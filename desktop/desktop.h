#ifndef NEOOS_DESKTOP_H
#define NEOOS_DESKTOP_H
#include <stdint.h>
void desktop_init(void);
void desktop_render(void);
void desktop_mouse_move(int dx,int dy);
void desktop_mouse_click(uint8_t button);
#endif
