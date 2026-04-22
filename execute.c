#include "shell.h"

/**
 * child_process - runs the command in the child process
 * @args: array of command and arguments
 * @full_path: the full path to the executable
 * @program_name: name of the shell program for error messages
 * @command_count: number of commands executed so far
 *
 * Description: Tries to run the command with execve.
 * If it fails, prints an error and exits.
 */
void child_process(char **args, char *full_path,
		char *program_name, int command_count)
{
	/* Try to run the command with the full path we found */
	if (execve(full_path, args, environ) == -1)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, command_count, args[0]);
		free(args);
		free(full_path);
		exit(127);
	}
}

/**
 * execute_command - forks and runs a command using PATH lookup
 * @line: the full command line typed by the user
 * @program_name: name of our shell, used in error messages
 * @command_count: how many commands have run so far
 *
 * Description: Tokenizes the line, looks up the full path of the
 * command, and if found forks a child to run it. If the command
 * doesn't exist, prints an error WITHOUT forking (Task 4 rule).
 */
void execute_command(char *line, char *program_name, int command_count)
{
	pid_t child_pid;
	int status;
	char **args;
	char *full_path;

	/* Split the line into tokens */
	args = tokenize(line);
	if (args == NULL || args[0] == NULL)
	{
		free(args);
		return;
	}

	/* Find the full path of the command BEFORE forking */
	full_path = find_in_path(args[0]);
	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			program_name, command_count, args[0]);
		free(args);
		return;
	}

	/* Create a child process to run the command */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror(program_name);
		free(args);
		free(full_path);
		return;
	}

	if (child_pid == 0)
		child_process(args, full_path, program_name, command_count);
	else
	{
		wait(&status);
		free(args);
		free(full_path);
	}
}
