#include <stdint.h>
#include "interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "../desktop/desktop.h"
#define MULTIBOOT_MAGIC 0x2BADB002u
typedef struct{uint32_t flags,mem_lower,mem_upper,boot_device,cmdline,mods_count,mods_addr,syms[4],mmap_length,mmap_addr,drives_length,drives_addr,config_table,boot_loader_name,apm_table,vbe_control_info,vbe_mode_info;uint16_t vbe_mode,vbe_interface_seg;uint16_t vbe_interface_off,vbe_interface_len;uint64_t framebuffer_addr;uint32_t framebuffer_pitch,framebuffer_width,framebuffer_height;uint8_t framebuffer_bpp,framebuffer_type;}__attribute__((packed)) multiboot_info_t;
void kmain(uint32_t magic,uint32_t info_addr){if(magic!=MULTIBOOT_MAGIC)for(;;)__asm__ volatile("cli;hlt");multiboot_info_t*mb=(multiboot_info_t*)(uintptr_t)info_addr;if(!(mb->flags&(1u<<12)))for(;;)__asm__ volatile("cli;hlt");desktop_set_framebuffer((uint32_t)mb->framebuffer_addr,mb->framebuffer_pitch,mb->framebuffer_width,mb->framebuffer_height,mb->framebuffer_bpp,mb->framebuffer_type);if(!desktop_is_ready())for(;;)__asm__ volatile("cli;hlt");interrupts_init();keyboard_init();mouse_init();desktop_init();interrupts_enable();for(;;){desktop_render();__asm__ volatile("hlt");}}
