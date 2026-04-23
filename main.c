#include "shell.h"

/**
 * prompt - displays the prompt if in interactive mode
 *
 * Description: Uses isatty to check if stdin is a terminal.
 * If it is, prints "$ " to stdout.
 */
void prompt(void)
{
	/* only show prompt if stdin is a terminal */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * handle_line - cleans the line and executes the command
 * @line: the input line from getline
 * @nread: number of bytes read
 * @argv: argument vector
 * @command_count: pointer to command counter
 * @exit_status: pointer to last exit status
 *
 * Description: Strips newline, skips empty lines, increments
 * the counter, runs the command, and saves the exit status.
 *
 * Return: -1 if exit was used, 0 otherwise
 */
int handle_line(char *line, ssize_t nread, char **argv,
		int *command_count, int *exit_status)
{
	int result;

	/* remove the trailing newline */
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	/* skip empty lines */
	if (line[0] == '\0')
		return (0);

	/* count this command */
	(*command_count)++;

	/* run it */
	result = execute_command(line, argv[0], *command_count);

	/* -1 means exit builtin was called */
	if (result == -1)
		return (-1);

	/* save the exit status */
	*exit_status = result;
	return (0);
}

/**
 * main - entry point of the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Description: Main loop of the shell. Reads and executes
 * commands until EOF or exit.
 *
 * Return: last command's exit status
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int command_count = 0;
	int exit_status = 0;

	(void)argc;

	while (1)
	{
		prompt();

		/* read a line */
		nread = getline(&line, &len, stdin);

		/* check for EOF (Ctrl+D) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* handle the line; -1 means exit */
		if (handle_line(line, nread, argv,
				&command_count, &exit_status) == -1)
			break;
	}

	free(line);
	return (exit_status);
}
