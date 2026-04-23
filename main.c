#include "shell.h"

/**
 * prompt - displays the prompt if in interactive mode
 *
 * Description: Uses isatty to check if stdin is a terminal.
 * If it is, prints "$ " to stdout. Skips the prompt in
 * non-interactive mode (pipes or redirected input).
 */
void prompt(void)
{
	/* Only show the prompt if stdin is a terminal */
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}

/**
 * handle_line - cleans the line and executes the command
 * @line: the input line from getline
 * @nread: number of bytes read by getline
 * @argv: argument vector, argv[0] is the program name
 * @command_count: pointer to the command counter in main
 *
 * Description: Strips the trailing newline, skips empty lines,
 * increments the counter and calls execute_command.
 *
 * Return: -1 if the shell should exit, 0 otherwise
 */
int handle_line(char *line, ssize_t nread, char **argv, int *command_count)
{
	/* Replace the trailing '\n' with '\0' to clean the command */
	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	/* If the user just pressed Enter, skip and show prompt again */
	if (line[0] == '\0')
		return (0);

	/* Count each real execution attempt for error messages */
	(*command_count)++;

	/* Execute the command and return whether we should exit */
	return (execute_command(line, argv[0], *command_count));
}

/**
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the program name
 *
 * Description: Main loop of the shell. Reads lines from stdin
 * and passes them to handle_line for cleaning and execution.
 * Exits on EOF (Ctrl+D) or when the exit builtin is used.
 * Frees all allocated memory before exit.
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int command_count = 0;

	(void)argc;

	while (1)
	{
		prompt();

		/* Read a line from stdin; getline allocates memory for us */
		nread = getline(&line, &len, stdin);

		/* Check for EOF — getline returns -1 */
		if (nread == -1)
		{
			/* Print newline so the user's terminal prompt looks clean */
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* If handle_line returns -1, the exit builtin was used */
		if (handle_line(line, nread, argv, &command_count) == -1)
			break;
	}

	/* Free memory allocated by getline before exiting */
	free(line);
	return (0);
}
