#include "shell.h"

/**
 * prompt - displays the prompt if in interactive mode
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * handle_line - cleans the line and executes the command
 * @line: the input line from getline
 * @nread: number of bytes read by getline
 * @argv: argument vector, argv[0] is the program name
 * @command_count: pointer to the command counter in main
 * @exit_status: pointer to the last exit status
 *
 * Description: Strips the trailing newline, skips empty lines,
 * increments the counter and calls execute_command. Updates
 * exit_status with the result.
 *
 * Return: -1 if the shell should exit, 0 otherwise
 */
int handle_line(char *line, ssize_t nread, char **argv,
		int *command_count, int *exit_status)
{
	int result;

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	if (line[0] == '\0')
		return (0);

	(*command_count)++;
	result = execute_command(line, argv[0], *command_count);

	if (result == -1)
		return (-1);

	*exit_status = result;
	return (0);
}

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the program name
 *
 * Return: exit status of the last command
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
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (handle_line(line, nread, argv,
				&command_count, &exit_status) == -1)
			break;
	}

	free(line);
	return (exit_status);
}