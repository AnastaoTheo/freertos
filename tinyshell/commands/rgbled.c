#include "rgbled.h"
#include "../../stellaris_drivers/rgb.h"
#include "../../utils/uartstdio.h"
#include "../../utils/ustdlib.h"
#include "../ColoredOutput.h"

static unsigned long color[3];
static int sub_command;
static int state;

int rgbled (void) {

	switch (sub_command) {

	case TURN_ON:
		RGBInit (1);
		state = 1;
		break;

	case TURN_OFF:
		RGBDisable();
		state = 0;
		break;

	case SET_COLOR:
		if (!state) {
			UARTprintf (BOLD_RED("You must run ") BOLD_CYAN("rgbled on") BOLD_RED(" before setting color\r\n"));
			return 1;
		}
		RGBColorSet (color);
		break;

	default:
		sub_command = 0;
		return 1;

	}

	sub_command = 0;
	return 0;
}

void rgbled_args (char *command) {
	int i, base;

	for (i = 0; command[i] != 0; i++) {
		if (command[i] == ' ') {
			command[i] = '\0';
			break;
		}
	}

	if (ustrcmp (command, "on") == 0) sub_command = TURN_ON;
	else if (ustrcmp(command, "off") == 0) sub_command = TURN_OFF;
	else if (ustrcmp(command, "set") == 0) sub_command = SET_COLOR;
	else sub_command = 0;

	base = i + 1;
	if (sub_command == SET_COLOR) {

		for (i = 0; command[base + i] != ' '; i++);
		command[base + i] = '\0';
		color[0] = ustrtoul (&command[base], 0, 16);

		base += i + 1;
		for (i = 0; command[base + i] != ' '; i++);
		command[base + i] = '\0';
		color[1] = ustrtoul (&command[base], 0, 16);

		base += i + 1;
		color[2] = ustrtoul (&command[base], 0, 16);
	}
}

