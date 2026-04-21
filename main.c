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
 * main - entry point of the simple shell
 * @argc: argument count (unused)
 * @argv: argument vector, argv[0] is the program name
 *
 * Description: Main loop of the shell. Reads lines from stdin,
 * removes the trailing newline, and executes each command.
 * Exits on EOF (Ctrl+D). Frees all allocated memory before exit.
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

		/* Replace the trailing '\n' with '\0' to clean the command */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* If the user just pressed Enter, skip and show prompt again */
		if (line[0] == '\0')
			continue;

		/* Count each real execution attempt for error messages */
		command_count++;

		/* Fork a child and execute the command */
		execute_command(line, argv[0], command_count);
	}

	/* Free memory allocated by getline before exiting */
	free(line);
	return (0);
}
