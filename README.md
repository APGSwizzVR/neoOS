# NeoOS 26.4

NeoOS is a standalone x86 operating system.

26 is the OS year family. The decimal value is the release version: 26.3 was the previous foundation build and 26.4 is the first graphical desktop build.

NeoOS 26.4 introduces a native 32-bit framebuffer desktop, mouse input, windows, a dock/taskbar, launcher, live RTC clock, and initial system applications.

The UI uses a custom clean sans-serif bitmap renderer with proportions inspired by modern Apple desktop interfaces. Apple's San Francisco font is proprietary, so this repository does not redistribute it. A licensed font asset can be integrated later.

Build with GCC multilib, NASM, GRUB, xorriso and QEMU:

make
make run

WSL/Windows are development tools only. The resulting ISO is the standalone NeoOS system.
