/*
 * tinyshell_task.c
 *
 *  Created on: 15/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "TinyShell.h"

#include "utils/uartstdio.h"

#include "commands/about.h"
#include "commands/rgbled.h"
#include "commands/regrw.h"
#include "commands/memop.h"

static Command_t commands[] = {
	{"about", about, 0, "About this shell"},
	{"rgbled", rgbled, rgbled_args, "Controls RGB Led: on, off, set RRRR GGGG BBBB 0-FFFF"},
	{"regread", regread, regread_args, "Reads register value: regread AAAAAAAA"},
	{"regwrite", regwrite, regwrite_args, "Writes register value: regwrite AAAAAAAA XXXXXXXX"},
	{"memcmp", memcmp_2, memcmp_2_args, "Compares two range of address: memcmp AAAAAAAA AAAAAAAA 9999"},
	{"memdump", memdump, memdump_args, "Prints hexadecimal dump of address: memdump AAAAAAAA 9999"},
	{"memset", memset_2, memset_2_args, "Sets a range of addresses to specified value: memset AAAAAAAA 9999 FF"},
	NULL_TERMINATOR
};

void tinyshell_init (void) {

	TinyShellInit (commands, UARTprintf, UARTgets);

	xTaskCreate (TinyShellRun, "TinyShell", configMINIMAL_STACK_SIZE, 0, 1, 0);
}

