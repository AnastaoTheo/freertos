/*
 * TinyShell.c
 *
 *  Created on: 14/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#include "TinyShell.h"
#include "ColoredOutput.h"

static Command_t *commands;
static unsigned int CommandNumber;
int (* t_printf)(const char *format, ...);
void (* t_gets)(char *str, unsigned int size);

void TinyShellInit (Command_t *command_list, unsigned int command_number, int (*printf_function)(const char *, ...),
    int (* gets_function)(char *, unsigned int)) {

	commands = command_list;
	CommandNumber = command_number;
	t_printf = printf_function;
	t_gets = gets_function;
}

static int my_strcmp (const char *s1, const char *s2) {
	int r = 0, i;

	for (i = 0; s1[i] != 0 || s2[i] != 0; i++) {
		r |= (s1[i] ^ s2[i]);
		r = (r << 1) | ((r & 0x80000000) > 31);
	}

	return r;
}

static int default_help (void) {
	int i;

	t_printf ("\n" BOLD_GREEN("TinyShell available commands:") "\n");
	for (i = 0; i < CommandNumber; i++) {
		t_printf(BOLD_YELLOW("%s") " - " BOLD_CYAN("%s\n"), commands[i].command_name,
                (commands[i].description==0)? "No desc. available" : commands[i].description);
	}
	t_printf ("\r\n");

	return 0;
}

static int parse (char *command) {
	int arg_base, i;

	if (command[0] == '?')
		return default_help();

	if (command[0] == '\0')
		return 0;

	// Gets the command name
	for (i = 0; command[i] != '\0'; i++) {
		if (command[i] == ' ') {

			command[i] = '\0';
			break;
		}
	}
	arg_base = i + 1;

	// Searches in list of commands. If not found returns ERR_COMMAND_NOT_FOUND
	for (i = 0 ;i < CommandNumber; i++) {

		if (my_strcmp(commands[i].command_name, command) == 0)
			break;

	}

	if (i == CommandNumber)
		return ERR_COMMAND_NOT_FOUND;

	// Build args, if any
	if (commands[i].build_args) commands[i].build_args(&command[arg_base]);

	// Runs command at last
	return commands[i].execute();
}

void TinyShellRun (void) {

	char cmd[COMMAND_MAX_LENGTH];
	int i, ret;

	while (1) {
		t_printf (BOLD_GREEN("TinyShell") "> ");
		t_gets (cmd, COMMAND_MAX_LENGTH);
		for (i = 0; cmd[i] != 0 && i < COMMAND_MAX_LENGTH; i++)
			if (cmd[i] == '\n' || cmd[i] == '\r') { cmd[i] = '\0'; break; }

		ret = parse (cmd);
		if (ret < 0)
			t_printf (BOLD_YELLOW("Command not found: %s\n"), cmd);
		else if (ret > 0)
			t_printf (BOLD_RED("Error executing command: %s\n"), cmd);

	}
}

