#ifndef LIBC_H
#define LIBC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);

void *memcpy(void *dest, const void * src, size_t n);

#endif