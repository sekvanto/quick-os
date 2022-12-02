#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/ascii_logo.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, kernel World!\n\n");
	render_logo();
}
