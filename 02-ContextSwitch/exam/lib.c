#include "lib.h"

void lib_delay(volatile int count){
}

int lib_putc(char ch) {
	while((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
	return *UART_THR = ch;
}

void lib_puts(char *s) {
	while(*s) lib_putc(*s++);
}
