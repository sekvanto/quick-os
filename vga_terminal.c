#include "vga_terminal.h"
#include "libc.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

/* Terminal scrolling */
void scroll()
{
	for (size_t i = 0; i < VGA_HEIGHT - 1; i++) {
		const size_t src_index = (i + 1) * VGA_WIDTH;
		const size_t dest_index = i * VGA_WIDTH;
		// memcpy(&terminal_buffer[dest_index], &terminal_buffer[src_index], VGA_WIDTH);
		for (size_t i = 0; i < VGA_WIDTH; i++) {
			terminal_buffer[dest_index + i] = terminal_buffer[src_index + i];
		}
	}

	terminal_column = 0;
	terminal_row = VGA_HEIGHT - 1;
	uint8_t previous_color = terminal_color;
	terminal_setcolor(VGA_COLOR_BLACK);

	for (size_t i = 0; i < VGA_WIDTH; i++) {
		terminal_putentryat(' ', terminal_color, terminal_column++, terminal_row);
	}

	terminal_column = 0;
	terminal_row = VGA_HEIGHT - 1;
	terminal_setcolor(previous_color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			scroll();
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++) {
		/* newline support */
		if (data[i] == '\n') {
			if (++terminal_row == VGA_HEIGHT)
				scroll();
			terminal_column = 0;
		/* other characters */
		} else {
			terminal_putchar(data[i]);
		}
	}
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}