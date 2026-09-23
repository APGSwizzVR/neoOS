#include <stdint.h>
#include "rtc.h"
static inline uint8_t inb(uint16_t p){uint8_t v;__asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p));return v;}
static inline void outb(uint16_t p,uint8_t v){__asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p));}
static uint8_t b(uint8_t v){return (uint8_t)((v>>4)*10+(v&15));}
static uint8_t c(uint8_t r){outb(0x70,r);return inb(0x71);}
void rtc_time(char *o){uint8_t h=b(c(4)),m=b(c(2));o[0]='0'+h/10;o[1]='0'+h%10;o[2]=':';o[3]='0'+m/10;o[4]='0'+m%10;o[5]=0;}
