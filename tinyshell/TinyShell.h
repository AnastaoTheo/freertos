/*
 * TinyShell.h
 *
 *  Created on: 14/11/2012
 *      Author: Cristóvão Zuppardo Rufino <cristovaozr@gmail.com>
 */

#ifndef TINYSHELL_H_
#define TINYSHELL_H_

/**
 * Command_t - TinyShell structure of commands. A command is comprised of the following items:
 *  command_name (mandatory):
 *      The command as written in the shell. e.g.:
 *      TinyShell > help
 *
 *  execute (mandatory):
 *      Pointer to the function that executes the command. This function must return zero (0)
 *      as success or a positive integer as an error
 *
 *  build_args (optional):
 *      Pointer to the function that parses the remaining of the string containing the arguments.
 *      Each function must be capable of parsing the string and obtaining all the data passed as
 *      arguments. If the function doesn't use any argument this can be set as NULL/(0)
 *
 *  description (optional):
 *      A string containing a quick description of the command. Can be left blank or NULL/(0)
 */
typedef struct {
	const char *command_name;
	int (*execute)(void);
	void (*build_args)(char *command);
	const char *description;
} Command_t;

/**
 * Starts TinyShell passing the command list, a printf-like function and a gets-like function.
 * The command list is an array of Command_t
 */
void TinyShellInit (Command_t *command_list, unsigned int command_number, int (*printf_function)(const char *, ...),
    int (* gets_function)(char *, unsigned int));

/**
 * Starts the shell; enters an infinite loop that parses and executes each command
 */
void TinyShellRun (void);

#define ERR_COMMAND_NOT_FOUND -1
#define COMMAND_MAX_LENGTH 100

#endif /* TINYSHELL_H_ */

