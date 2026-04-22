#include "shell.h"

/**
 * is_builtin - checks if a command is a builtin and runs it
 * @args: the array of tokens from the command line
 * @program_name: name of our shell, used in error messages
 *
 * Description: Checks if the command is a known builtin.
 * Right now the only builtin is exit. If it matches, runs it.
 * Returns 1 if a builtin was found and handled, 0 if not.
 *
 * Return: 1 if builtin was handled, 0 if not a builtin
 */
int is_builtin(char **args, char *program_name)
{
	/* suppress unused warning — will be used in task 6 for env */
	(void)program_name;

	/* check if the command is exit */
	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		exit(0);
	}

	/* not a builtin */
	return (0);
}
