#include <stdint.h>
#include "mouse.h"
extern void desktop_mouse_event(int dx,int dy,int buttons);
static uint8_t packet[3];static uint8_t cycle;
static inline uint8_t inb(uint16_t p){uint8_t v;__asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p));return v;}
static inline void outb(uint16_t p,uint8_t v){__asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p));}
static void waitw(void){for(uint32_t i=0;i<100000;i++)if(!(inb(0x64)&2))return;}
static void waitr(void){for(uint32_t i=0;i<100000;i++)if(inb(0x64)&1)return;}
static void mw(uint8_t v){waitw();outb(0x64,0xd4);waitw();outb(0x60,v);}
static uint8_t mr(void){waitr();return inb(0x60);}
void mouse_init(void){waitw();outb(0x64,0xa8);waitw();outb(0x64,0x20);uint8_t s=mr();s|=2;s&=(uint8_t)~0x20;waitw();outb(0x64,0x60);waitw();outb(0x60,s);mw(0xf6);(void)mr();mw(0xf4);(void)mr();cycle=0;}
void mouse_handler(void){uint8_t s=inb(0x64);if(!(s&1)||!(s&0x20))return;uint8_t d=inb(0x60);if(cycle==0&&!(d&8))return;packet[cycle++]=d;if(cycle==3){cycle=0;desktop_mouse_event((int8_t)packet[1],(int8_t)packet[2],packet[0]&7);}outb(0x20,0x20);outb(0xa0,0x20);}
