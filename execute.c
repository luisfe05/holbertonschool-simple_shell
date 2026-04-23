#include "shell.h"

/**
 * child_process - runs the command in the child process
 * @args: array of command and arguments
 * @full_path: the full path to the executable
 * @program_name: name of the shell program for error messages
 * @command_count: number of commands executed so far
 *
 * Description: Tries to run the command with execve.
 * If it fails, prints an error and exits with 127.
 */
void child_process(char **args, char *full_path,
		char *program_name, int command_count)
{
	/* try to run the command */
	if (execve(full_path, args, environ) == -1)
	{
		print_error(program_name, command_count, args[0]);
		free(args);
		free(full_path);
		exit(127);
	}
}

/**
 * fork_and_wait - forks a child and waits for it to finish
 * @args: array of command and arguments
 * @full_path: the full path to the executable
 * @program_name: name of the shell
 * @command_count: number of commands executed so far
 *
 * Description: Creates a child process, runs the command in it,
 * and waits for it to finish. Returns the child's exit status.
 *
 * Return: exit status of the child
 */
int fork_and_wait(char **args, char *full_path,
		char *program_name, int command_count)
{
	pid_t child_pid;
	int status;
	int exit_code = 0;

	child_pid = fork();

	/* fork failed */
	if (child_pid == -1)
	{
		perror(program_name);
		free(args);
		free(full_path);
		return (0);
	}

	/* we are in the child */
	if (child_pid == 0)
		child_process(args, full_path, program_name, command_count);

	/* we are in the parent, wait for child */
	wait(&status);

	/* get the real exit code from status */
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);

	free(args);
	free(full_path);
	return (exit_code);
}

/**
 * execute_command - runs a command using PATH lookup
 * @line: the full command line typed by the user
 * @program_name: name of our shell
 * @command_count: how many commands have run so far
 *
 * Description: Tokenizes the line, checks for builtins,
 * finds the command in PATH, and runs it.
 *
 * Return: exit status of the command, or -1 if exit builtin
 */
int execute_command(char *line, char *program_name, int command_count)
{
	char **args;
	char *full_path;
	int builtin_result;

	/* split the line into words */
	args = tokenize(line);
	if (args == NULL || args[0] == NULL)
	{
		free(args);
		return (0);
	}

	/* check if it's a builtin */
	builtin_result = is_builtin(args, program_name);
	if (builtin_result != 0)
		return (builtin_result);

	/* find the command in PATH */
	full_path = find_in_path(args[0]);
	if (full_path == NULL)
	{
		print_error(program_name, command_count, args[0]);
		free(args);
		return (127);
	}

	/* fork and run the command */
	return (fork_and_wait(args, full_path, program_name, command_count));
}
