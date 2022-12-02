#include "common.h"

#include "libc.h"
#include "vga_terminal.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	terminal_setcolor(VGA_COLOR_LIGHT_BLUE);

	/* Newline support is left as an exercise. */
	for (size_t i = 0; i < VGA_HEIGHT / 3; i++) {
		terminal_writestring("Hello, kernel World!\nI'm at new line\nOne extra line\n");
	}
	terminal_writestring("An additional line\nSecond line\n");
	terminal_putentryat('1', VGA_COLOR_RED, 20, VGA_HEIGHT - 1);
	terminal_putentryat('2', VGA_COLOR_LIGHT_RED, 50, VGA_HEIGHT - 1);
	terminal_writestring("\nAnd one more string\n");
	terminal_setcolor(VGA_COLOR_CYAN);
	terminal_writestring("\n\nTwo empty lines in between");
}