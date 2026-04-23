#include "shell.h"

/**
 * print_error - prints a "command not found" error message
 * @program_name: name of the shell (argv[0])
 * @command_count: number of commands executed so far
 * @command: the command that failed
 *
 * Description: Prints the error to stderr in the exact same
 * format as /bin/sh, for example:
 *     ./hsh: 1: qwerty: not found
 */
void print_error(char *program_name, int command_count, char *command)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
		program_name, command_count, command);
}
