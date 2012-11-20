#include "regrw.h"
#include "../../utils/ustdlib.h"
#include "../ColoredOutput.h"
#include "../../utils/uartstdio.h"

static volatile unsigned long *address;
static volatile unsigned long value;

int regread (void) {

	UARTprintf ("Value of register 0x%X: %X\r\n", address, *address);

	return 0;
}

void regread_args(char *command) {

	address = ustrtoul (command, 0, 16);
}

int regwrite (void) {
	if (address == 0xFFFFFFFF)	return 1;
 
	UARTprintf ("Writing 0x%X in register 0x%X\r\n", address, value);
	*address = value;
}

void regwrite_args(char *command) {
	int i;

	for (i = 0; command[i] != ' ' || command[i] != '\0'; i++);
	if (command[i] == '\0') {
		address = 0xFFFFFFFF;
		return ;
	}

	command[i] = '\0';
	address = ustrtoul (command, 0, 16);
	value = ustrtoul (&command[i+1], 0, 16);
}

