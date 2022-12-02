#ifndef LIBC_H
#define LIBC_H

#include "common.h"

size_t strlen(const char* str);

void *memcpy(void *dest, const void * src, size_t n);

#endif