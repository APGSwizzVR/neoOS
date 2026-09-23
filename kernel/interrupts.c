#include <stdint.h>
#include "interrupts.h"
struct idt_entry{uint16_t base_low;uint16_t selector;uint8_t zero;uint8_t flags;uint16_t base_high;}__attribute__((packed));
struct idt_ptr{uint16_t limit;uint32_t base;}__attribute__((packed));
static struct idt_entry idt[256];static struct idt_ptr idtp;extern void keyboard_stub(void);
static void gate(uint8_t n,uint32_t b){idt[n].base_low=b&0xffff;idt[n].selector=0x08;idt[n].zero=0;idt[n].flags=0x8e;idt[n].base_high=(b>>16)&0xffff;}
static void pic(void){__asm__ volatile("movb $0x11,%%al;outb %%al,$0x20;outb %%al,$0xa0;movb $0x20,%%al;outb %%al,$0x21;movb $0x28,%%al;outb %%al,$0xa1;movb $0x04,%%al;outb %%al,$0x21;movb $0x02,%%al;outb %%al,$0xa1;movb $0x01,%%al;outb %%al,$0x21;outb %%al,$0xa1": : :"al");}
void interrupts_init(void){for(int i=0;i<256;i++){idt[i].base_low=0;idt[i].selector=0x08;idt[i].zero=0;idt[i].flags=0;idt[i].base_high=0;}gate(33,(uint32_t)keyboard_stub);pic();idtp.base=(uint32_t)idt;idtp.limit=sizeof(idt)-1;__asm__ volatile("lidt %0": :"m"(idtp));__asm__ volatile("sti");}
