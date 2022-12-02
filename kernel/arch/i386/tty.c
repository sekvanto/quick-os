#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll_once(size_t line) {
	size_t *loop;
	char c;

	for(loop = (size_t*)(line * (VGA_WIDTH * 2) + 0xB8000); loop < (size_t*) (0xB8000 + VGA_WIDTH * 2); loop++) {
		c = *loop;
		*(loop - (VGA_WIDTH * 2)) = c;
	}
}

void terminal_delete_last_line() {
	size_t x, *ptr;

	for(x = 0; x < VGA_WIDTH * 2; x++) {
		ptr = (size_t*) (0xB8000 + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x);
		*ptr = 0;
	}
}

void terminal_scroll() {
	size_t line;
	for(line = 1; line <= VGA_HEIGHT - 1; line++)
	{
		terminal_scroll_once(line);
	}
	terminal_delete_last_line();
	terminal_row = VGA_HEIGHT - 1;
}

void terminal_putchar(char c) {
	unsigned char uc = c;

	/* newline support */
	if (c == '\n') {
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_scroll();
		}
		terminal_column = 0;
		return;
	}

	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_scroll();
		}
	}
}

void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
