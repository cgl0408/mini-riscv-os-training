#ifndef __LIB_H__
#define __LIB_H__
#include "riscv.h"
#include <stddef.h>
#include <stdarg.h>

extern void lib_delay(volatile int count);
extern void lib_puts(char* s);
extern int lib_putc(char c);

#endif