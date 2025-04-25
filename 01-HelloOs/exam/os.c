#include <stdint.h>


#define UART 0x10000000
#define UART_THR (uint8_t *) UART
#define UART_LSR (uint8_t *) (UART_THR + 0x05) //錯
#define UART_LSR_EMPTY_MASK 0x40

// LSR Bit 6: Transmitter empty; both the THR and LSR are empty

int lib_putc(char ch) {
	while((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);//錯
	return *UART_THR = ch;
}
//錯
void lib_puts(char *s) {
	while(*s) lib_putc(*s++);
}

int os_main(void)
{
	lib_puts("Hello OS \n");
	while(1){}
	return 0;
}
