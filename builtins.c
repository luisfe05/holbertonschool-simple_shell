#include "shell.h"

/**
 * print_env - prints the current environment to stdout
 *
 * Description: Walks through the global environ array and writes
 * each "name=value" string to stdout followed by a newline.
 * Uses write directly to avoid stdio buffering issues.
 */
void print_env(void)
{
	int i = 0;
	int len;

	/* Walk through every environment variable */
	while (environ[i] != NULL)
	{
		/* Measure the length of this variable string */
		len = 0;
		while (environ[i][len] != '\0')
			len++;

		/* Write the variable and a newline */
		write(STDOUT_FILENO, environ[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * is_builtin - checks if a command is a builtin and runs it
 * @args: the array of tokens from the command line
 * @program_name: name of our shell (unused, for future builtins)
 *
 * Description: Checks if the command is a known builtin.
 * Current builtins: exit and env. Returns -1 for exit (signal
 * to main to stop the loop), 1 if env was handled, 0 if not
 * a builtin. Does NOT call exit() directly — lets main handle
 * cleanup properly.
 *
 * Return: -1 for exit, 1 if env handled, 0 if not a builtin
 */
int is_builtin(char **args, char *program_name)
{
	/* suppress unused warning */
	(void)program_name;

	/* exit builtin — signal main to exit cleanly */
	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		return (-1);
	}

	/* env builtin — prints environment variables */
	if (_strcmp(args[0], "env") == 0)
	{
		print_env();
		free(args);
		return (1);
	}

	/* not a builtin */
	return (0);
}
