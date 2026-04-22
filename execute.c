#include "shell.h"

/**
 * child_process - runs the command in the child process
 * @args: array of command and arguments
 * @program_name: name of the shell program for error messages
 * @command_count: number of commands executed so far
 *
 * Description: Tries to run the command with execve.
 * If it fails, prints an error and exits.
 */
void child_process(char **args, char *program_name, int command_count)
{
	/* try to run the command */
	if (execve(args[0], args, environ) == -1)
	{
		/* if execve failed, print the error message */
		fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, command_count, args[0]);
		free(args);
		exit(127);
	}
}

/**
 * execute_command - forks and runs a command
 * @line: the full command line typed by the user
 * @program_name: name of our shell, used in error messages
 * @command_count: how many commands have run so far
 *
 * Description: Splits the line into tokens, forks a child,
 * and runs the command. Parent waits for child to finish.
 */
void execute_command(char *line, char *program_name, int command_count)
{
	pid_t child_pid;
	int status;
	char **args;

	/* split the line into words */
	args = tokenize(line);
	if (args == NULL)
		return;

	/* create a child process */
	child_pid = fork();

	/* fork failed */
	if (child_pid == -1)
	{
		perror(program_name);
		free(args);
		return;
	}

	/* we are in the child process */
	if (child_pid == 0)
		child_process(args, program_name, command_count);
	else
	{
		/* we are in the parent, wait for child to finish */
		wait(&status);
		free(args);
	}
}
