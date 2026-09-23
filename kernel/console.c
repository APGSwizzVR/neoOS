#include <stdint.h>
#include "console.h"
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
static volatile uint16_t *const VGA=(uint16_t*)0xB8000;
static uint8_t row=0,column=0;
static uint16_t cell(unsigned char c){return (uint16_t)c|((uint16_t)0x07<<8);}
static void scroll(void){if(row<VGA_HEIGHT)return;for(int y=1;y<VGA_HEIGHT;y++)for(int x=0;x<VGA_WIDTH;x++)VGA[(y-1)*VGA_WIDTH+x]=VGA[y*VGA_WIDTH+x];for(int x=0;x<VGA_WIDTH;x++)VGA[(VGA_HEIGHT-1)*VGA_WIDTH+x]=cell(' ');row=VGA_HEIGHT-1;}
void console_clear(void){for(int y=0;y<VGA_HEIGHT;y++)for(int x=0;x<VGA_WIDTH;x++)VGA[y*VGA_WIDTH+x]=cell(' ');row=0;column=0;}
void console_putc(char c){if(c=='\n'){column=0;row++;scroll();return;}if(c=='\r'){column=0;return;}if(c=='\b'){if(column){column--;VGA[row*VGA_WIDTH+column]=cell(' ');}return;}VGA[row*VGA_WIDTH+column]=cell((unsigned char)c);column++;if(column>=VGA_WIDTH){column=0;row++;scroll();}}
void console_write(const char *s){while(*s)console_putc(*s++);}
