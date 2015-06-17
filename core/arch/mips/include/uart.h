#ifndef __LING_MIPS_UART_H___
#define __LING_MIPS_UART_H___

typedef unsigned uartport_t;

int uart_init(uartport_t port);
int uart_putc(uartport_t port, int c);
int uart_puts(uartport_t port, const char *buf, size_t len);

#endif //__LING_MIPS_UART_H___
