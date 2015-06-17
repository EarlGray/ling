#include <stdlib.h>
#include <assert.h>

#define SYS_FREQ 200000000

#define B115200 115200

//#include "ling_common.h"
#include "uart.h"

#define N_UARTS         2
/*
 * Compute the 16-bit baud rate divisor, given
 * the bus frequency and baud rate.
 * Round to the nearest integer.
 */
#define PIC32_BRG_BAUD(fr,bd)   ((((fr)/8 + (bd)) / (bd) / 2) - 1)

#define PIC32_SFR(a)            *(volatile unsigned*)(0xBF800000 + (a))

#define U1MODE          PIC32_SFR (0x22000) /* Mode */
#define U2MODE          PIC32_SFR (0x22200) /* Mode */

/*
 * UART Mode register.
 */
#define PIC32_UMODE_PDSEL_8NPAR 0x0000  /* 8-bit data, no parity */
#define PIC32_UMODE_ON          0x8000  /* UART Enable */

/*
 * UART Control and status register.
 */
#define PIC32_USTA_TRMT         0x00000100 /* Transmit shift register is empty (read-only) */
#define PIC32_USTA_UTXEN        0x00000400 /* Transmit Enable */
#define PIC32_USTA_UTXBRK       0x00000800 /* Transmit Break */
#define PIC32_USTA_URXEN        0x00001000 /* Receiver Enable */
#define PIC32_USTA_UTXINV       0x00002000 /* Transmit Polarity Inversion */
#define PIC32_USTA_UTXISEL      0x0000C000 /* Bitmask: TX interrupt is generated when... */
#define PIC32_USTA_UTXISEL_1    0x00000000 /* ...the transmit buffer contains at least one empty space */
#define PIC32_USTA_UTXISEL_ALL  0x00004000 /* ...all characters have been transmitted */
#define PIC32_USTA_UTXISEL_EMP  0x00008000 /* ...the transmit buffer becomes empty */

#define IFSCLR(n)       PIC32_SFR (0x10044+((n)<<4))
#define IFSSET(n)       PIC32_SFR (0x10048+((n)<<4))
#define IFSINV(n)       PIC32_SFR (0x1004C+((n)<<4))

#define IECCLR(n)       PIC32_SFR (0x100c4+((n)<<4))
#define IECSET(n)       PIC32_SFR (0x100c8+((n)<<4))
#define IECINV(n)       PIC32_SFR (0x100cC+((n)<<4))

#define UART_IRQ_INIT(name) { \
        name##E,  \
        name##RX, \
        name##TX, \
        1 << (name##E  & 31), \
        1 << (name##RX & 31), \
        1 << (name##TX & 31), \
        &IECSET(name##RX >> 5), \
        &IECSET(name##TX >> 5), \
        &IECCLR(name##TX >> 5), \
        &IFSCLR(name##E  >> 5), \
        &IFSCLR(name##RX >> 5), \
        &IFSCLR(name##TX >> 5), \
    }

/*
 * PIC32 UART registers.
 */
typedef struct {
    volatile unsigned mode;		/* Mode */
    volatile unsigned modeclr;
    volatile unsigned modeset;
    volatile unsigned modeinv;
    volatile unsigned sta;		/* Status and control */
    volatile unsigned staclr;
    volatile unsigned staset;
    volatile unsigned stainv;
    volatile unsigned txreg;            /* Transmit */
    volatile unsigned unused1;
    volatile unsigned unused2;
    volatile unsigned unused3;
    volatile unsigned rxreg;            /* Receive */
    volatile unsigned unused4;
    volatile unsigned unused5;
    volatile unsigned unused6;
    volatile unsigned brg;		/* Baud rate */
    volatile unsigned brgclr;
    volatile unsigned brgset;
    volatile unsigned brginv;
} uart_regmap_t;

typedef struct uart_irq {
    int er;                             /* Receive error interrupt number */
    int rx;                             /* Receive interrupt number */
    int tx;                             /* Transmit interrupt number */
    unsigned er_mask;                   /* Receive error irq bitmask */
    unsigned rx_mask;                   /* Receive irq bitmask */
    unsigned tx_mask;                   /* Transmit irq bitmask */
    volatile unsigned *enable_rx_intr;  /* IECSET pointer for receive */
    volatile unsigned *enable_tx_intr;  /* IECSET pointer for transmit */
    volatile unsigned *disable_tx_intr; /* IECCLR pointer for transmit */
    volatile unsigned *clear_er_intr;   /* IFSCLR pointer for receive error */
    volatile unsigned *clear_rx_intr;   /* IFSCLR pointer for receive */
    volatile unsigned *clear_tx_intr;   /* IFSCLR pointer for transmit */
} uart_irq_t;


#define PIC32_IRQ_U1E       112 /* UART1 Fault */
#define PIC32_IRQ_U1RX      113 /* UART1 Receive Done */
#define PIC32_IRQ_U1TX      114 /* UART1 Transfer Done */

#define PIC32_IRQ_U2E       145 /* UART2 Fault */
#define PIC32_IRQ_U2RX      146 /* UART2 Receive Done */
#define PIC32_IRQ_U2TX      147 /* UART2 Transfer Done */

static volatile uart_regmap_t *uartregmap[N_UARTS] = { 0 };

static uart_irq_t uartirqmap[N_UARTS] = {
    UART_IRQ_INIT(PIC32_IRQ_U1),
    UART_IRQ_INIT(PIC32_IRQ_U2),
};

/*
 *  Initialize the UART port
 */
int uart_init(uartport_t port)
{
    volatile uart_regmap_t *reg;

    if (port >= N_UARTS)
        return -1;

    switch (port) {
        case 0: reg = (volatile uart_regmap_t *)&U1MODE; break;
        case 1: reg = (volatile uart_regmap_t *)&U2MODE; break;
        default: return -2;
    }
    uartregmap[port] = reg;

    reg->sta = PIC32_USTA_UTXEN | PIC32_USTA_URXEN;
    reg->brg = PIC32_BRG_BAUD(SYS_FREQ, B115200);
    reg->mode = PIC32_UMODE_PDSEL_8NPAR | PIC32_UMODE_ON;
    return 0;
}

/*
 * Send a char on a port, via a busy wait loop.
 */
int uart_putc(uartport_t port, int c)
{
    assert(port < N_UARTS);
    int timo, s;

    volatile uart_regmap_t *reg = uartregmap[port];
    uart_irq_t *irq = &uartirqmap[port];

    /*
     * Wait for transmitter to be not busy.
     * Give up after a reasonable time.
     */
    timo = 30000;
    while (! (reg->sta & PIC32_USTA_TRMT))
        if (--timo == 0)
            break;//return -1;
    reg->txreg = (unsigned char) c;

    /* Clear TX interrupt. */
    *irq->clear_tx_intr = irq->tx_mask;

    timo = 30000;
    while (! (reg->sta & PIC32_USTA_TRMT))
        if (--timo == 0)
            break;//return -2;
    return 0;
}

int uart_puts(uartport_t port, const char *buf, size_t len)
{
    int i;
    for (i = 0; i < len; ++i) {
        int ret = uart_putc(port, buf[i]);
        /*
        if (ret < 0)
            return ret;
            */
    }
    return i;
}

