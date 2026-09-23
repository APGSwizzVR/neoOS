TARGET := neoos-26-v0.3
BUILD := build
CC := gcc
LD := ld
AS := nasm
CFLAGS := -m32 -ffreestanding -fno-pie -fno-stack-protector -nostdlib -nostartfiles -nodefaultlibs -Wall -Wextra -O2
LDFLAGS := -m elf_i386 -T linker.ld
C_SOURCES := kernel/main.c kernel/console.c kernel/keyboard.c kernel/interrupts.c desktop/desktop.c apps/terminal/terminal.c apps/settings/settings.c apps/explorer/explorer.c apps/device_manager/device_manager.c
C_OBJECTS := $(patsubst %.c,$(BUILD)/%.o,$(C_SOURCES))
ASM_SOURCES := boot/boot.asm kernel/interrupt_stubs.asm
ASM_OBJECTS := $(patsubst %.asm,$(BUILD)/%.o,$(ASM_SOURCES))
KERNEL := $(BUILD)/kernel.bin
ISO := $(BUILD)/$(TARGET).iso
.PHONY: all clean iso run
all: iso
$(BUILD):
	mkdir -p $(BUILD)/boot $(BUILD)/kernel $(BUILD)/desktop $(BUILD)/apps/terminal $(BUILD)/apps/settings $(BUILD)/apps/explorer $(BUILD)/apps/device_manager $(BUILD)/iso/boot/grub
$(BUILD)/%.o: %.c | $(BUILD)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD)/%.o: %.asm | $(BUILD)
	mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@
$(KERNEL): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^
$(ISO): $(KERNEL) grub.cfg
	mkdir -p $(BUILD)/iso/boot/grub
	cp $(KERNEL) $(BUILD)/iso/boot/kernel.bin
	cp grub.cfg $(BUILD)/iso/boot/grub/grub.cfg
	grub-mkrescue -o $@ $(BUILD)/iso
iso: $(ISO)
run: $(ISO)
	qemu-system-x86_64 -cdrom $(ISO) -m 256M
clean:
	rm -rf $(BUILD)
