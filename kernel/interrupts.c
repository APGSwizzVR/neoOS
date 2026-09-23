#include <stdint.h>
#include "interrupts.h"

struct idt_entry{uint16_t low;uint16_t sel;uint8_t zero;uint8_t flags;uint16_t high;}__attribute__((packed));
struct idt_ptr{uint16_t limit;uint32_t base;}__attribute__((packed));
static struct idt_entry idt[256];static struct idt_ptr idtp;
extern void keyboard_stub(void);extern void mouse_stub(void);
static inline uint8_t inb(uint16_t p){uint8_t v;__asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p));return v;}
static inline void outb(uint16_t p,uint8_t v){__asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p));}
static void gate(uint8_t n,uint32_t b){idt[n].low=b&0xffff;idt[n].sel=8;idt[n].zero=0;idt[n].flags=0x8e;idt[n].high=(b>>16)&0xffff;}
static void pic_remap(void){uint8_t a=inb(0x21),b=inb(0xa1);outb(0x20,0x11);outb(0xa0,0x11);outb(0x21,0x20);outb(0xa1,0x28);outb(0x21,4);outb(0xa1,2);outb(0x21,1);outb(0xa1,1);outb(0x21,a);outb(0xa1,b);}
void interrupts_init(void){for(int i=0;i<256;i++){idt[i].low=0;idt[i].sel=0;idt[i].zero=0;idt[i].flags=0;idt[i].high=0;}gate(33,(uint32_t)keyboard_stub);gate(44,(uint32_t)mouse_stub);pic_remap();outb(0x21,0xf9);outb(0xa1,0xef);idtp.base=(uint32_t)&idt;idtp.limit=sizeof(idt)-1;__asm__ volatile("lidt %0"::"m"(idtp));}
void interrupts_enable(void){__asm__ volatile("sti");}
