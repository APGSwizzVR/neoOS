#ifndef NEOOS_DESKTOP_H
#define NEOOS_DESKTOP_H
#include <stdint.h>
void desktop_set_framebuffer(uint32_t,uint32_t,uint32_t,uint32_t,uint8_t,uint8_t);
int desktop_is_ready(void);
void desktop_init(void);
void desktop_render(void);
void desktop_mouse_event(int,int,int);
#endif
