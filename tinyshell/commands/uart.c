/*
 * uart.c
 *
 *  Created on: 26/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

/* UART configuration command: Enables, disables e (re)configures UART's
 *
 * uart enable [uartnum]
 * uart disable [uartnum]
 * uart configure [uartnum] [baud] [parity] [stopbits] */

#include "uart.h"
#include "../../utils/ustdlib.h"
#include "../../driverlib/uart.h"
#include "../ColoredOutput.h"
#include "../../inc/hw_memmap.h"

static unsigned int uartnum, baud, parity, stopbits;
static unsigned int amount;
static unsigned long address;

//static const unsigned long uart_addresses[] = {
//		UART0_BASE,
//		UART1_BASE,
//		UART2_BASE,
//		UART3_BASE,
//		UART4_BASE,
//		UART5_BASE,
//		UART6_BASE,
//		UART7_BASE
//};

int uart (void) {

	unsigned long uart_base, uart_config;

	if (uartnum > 7 || uartnum < 0) {
		t_printf (BOLD_RED("Invalid uart number: %d\n"), uartnum);
		return 1;
	}

	switch (uartnum) {

	}


	return 0;
}

void uart_args (char *command) {
	int i, base;

	base = 0;
	for (i = base; command[i] != '\0' && command[i] != ' '; i++)
		if (command[i] == ' ') { command[i] = '\0'; break; }

	uartnum = ustrtoul (&command[base], 0, 10);

	base = i + 1;
	for (i = base; command[i] != '\0' && command[i] != ' '; i++)
		if (command[i] == ' ') { command[i] = '\0'; break; }

	baud = ustrtoul (&command[base], 0, 10);

	base = i + 1;
	for (i = base; command[i] != '\0' && command[i] != ' '; i++)
		if (command[i] == ' ') { command[i] = '\0'; break; }

	parity = ustrtoul (&command[base], 0, 10);

	base = i + 1;
	for (i = base; command[i] != '\0' && command[i] != ' '; i++)
		if (command[i] == ' ') { command[i] = '\0'; break; }

	stopbits = ustrtoul (&command[base], 0, 10);
}

/* UART print string command: Writes verbatim the string after the command
 *
 * uartprint [uartnum] [value] */
int uartprint (void) {

	return 0;
}

void uartprint_args (char *command) {

}


/* UART read line command: Reads a line (\n terminated) and prints to the console
 * uartreadline [uartnum] */
int uartreadline (void) {

	return 0;
}

void uartreadline_args (char *command) {

}

/* UART read command: Reads [amount] bytes from [uartnum] and stores in [address]
 *
 * uartread [uartnum] [address] [amount] */
int uartread (void) {

	return 0;
}

void uartread_args (char *command) {

}

/* UART write command: Writes [amount] bytes from [address] to [uartnum]
 *
 * uartwrite [uartnum] [address] [amount] */
int uartwrite (void) {

	return 0;
}

void uartwrite_args (char *command) {

}
