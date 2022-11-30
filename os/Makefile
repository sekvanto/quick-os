BUILD_DIR=../build/os
OS=$(BUILD_DIR)/os

CFLAGS+=-ffreestanding -nostdlib -m32 -gdwarf-4 -ggdb3

OS_SRCS := $(wildcard *.c)
OS_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_SRCS))

all: $(OS)

$(BUILD_DIR)/%.o: %.c
	gcc $(CFLAGS) -m32 -c  $< -o $@

$(OS): $(OS_OBJS)
	ld -m elf_i386 -nmagic --noinhibit-exec -Tos.lds $(OS_OBJS) -o $@

clean:
	rm $(BUILD_DIR)/*
