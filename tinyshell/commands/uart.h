/*
 * uart.h
 *
 *  Created on: 20/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef UART_H_
#define UART_H_

/* UART configuration command: Enables, disables e (re)configures UART's
 *
 * uart enable [uartnum]
 * uart disable [uartnum]
 * uart configure [uartnum] [baud] [parity] [stopbits] */
int uart (void);
void uart_args (char *command);

/* UART print string command: Writes verbatim the string after the command
 *
 * uartprint [uartnum] [value] */
int uartprint (void);
void uartprint_args (char *command);

/* UART read line command: Reads a line (\n terminated) and prints to the console
 * uartreadline [uartnum] */
int uartreadline (void);
void uartreadline_args (char *command);

/* UART read command: Reads [amount] bytes from [uartnum] and stores in [address]
 *
 * uartread [uartnum] [address] [amount] */
int uartread (void);
void uartread_args (char *command);

/* UART write command: Writes [amount] bytes from [address] to [uartnum]
 *
 * uartwrite [uartnum] [address] [amount] */
int uartwrite (void);
void uartwrite_args (char *command);

extern int (* t_printf)(const char *format, ...);

#endif /* UART_H_ */
