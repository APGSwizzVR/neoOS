#include <stdint.h>
#include "keyboard.h"
#include "console.h"
static const char map[128]={0,27,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x','c','v','b','n','m',',','.','/',0,'*',0,' '};
static unsigned char inb(uint16_t p){unsigned char v;__asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p));return v;}
static void outb(uint16_t p,unsigned char v){__asm__ volatile("outb %0,%1": :"a"(v),"Nd"(p));}
void keyboard_init(void){(void)inb(0x64);outb(0x21,0xfd);}
void keyboard_handler(void){unsigned char s=inb(0x60);if(!(s&0x80)&&s<128&&map[s])console_putc(map[s]);outb(0x20,0x20);}
