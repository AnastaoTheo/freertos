/*
 * about.c
 *
 *  Created on: 15/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include "about.h"
#include "../ColoredOutput.h"

extern int (* t_printf)(const char *format, ...);
extern void (* t_gets)(char *str, unsigned int size);

int about (void) {

	t_printf ("\n" BOLD_YELLOW("TinyShell") " - A small shell\n"
			"Written in C by " BOLD_GREEN("Cristovao Rufino") " <"
			BOLD_YELLOW("cristovaozr@gmail.com") ">\n\n");

	return 0;
}

