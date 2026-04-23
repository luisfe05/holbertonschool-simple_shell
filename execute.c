#include "shell.h"

/**
 * child_process - runs the command in the child process
 * @args: array of command and arguments
 * @full_path: the full path to the executable
 * @program_name: name of the shell program for error messages
 * @command_count: number of commands executed so far
 *
 * Description: Tries to run the command with execve using the
 * full path. If it fails, prints an error and exits with 127.
 */
void child_process(char **args, char *full_path,
		char *program_name, int command_count)
{
	if (execve(full_path, args, environ) == -1)
	{
		print_error(program_name, command_count, args[0]);
		free(args);
		free(full_path);
		exit(127);
	}
}

/**
 * fork_and_run - forks, runs the command, and returns exit status
 * @args: array of command and arguments
 * @full_path: the full path to the executable
 * @program_name: name of the shell program
 * @command_count: number of commands executed so far
 *
 * Description: Creates a child, runs child_process in it, waits
 * for the child to finish, and returns its exit status.
 *
 * Return: exit status of the child process
 */
int fork_and_run(char **args, char *full_path,
		char *program_name, int command_count)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(program_name);
		free(args);
		free(full_path);
		return (0);
	}

	if (child_pid == 0)
		child_process(args, full_path, program_name, command_count);

	wait(&status);
	free(args);
	free(full_path);

	/* Extract real exit code from status (shifted 8 bits in Unix) */
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

/**
 * execute_command - tokenizes, validates, and executes a command
 * @line: the full command line typed by the user
 * @program_name: name of our shell, used in error messages
 * @command_count: how many commands have run so far
 *
 * Description: Tokenizes the line, checks for builtins, finds the
 * command in PATH, and runs it. Returns the command's exit status
 * so main can track it for the exit builtin.
 *
 * Return: exit status of the command, or -1 if exit builtin was used
 */
int execute_command(char *line, char *program_name, int command_count)
{
	char **args;
	char *full_path;
	int builtin_result;

	args = tokenize(line);
	if (args == NULL || args[0] == NULL)
	{
		free(args);
		return (0);
	}

	builtin_result = is_builtin(args, program_name);
	if (builtin_result != 0)
		return (builtin_result);

	full_path = find_in_path(args[0]);
	if (full_path == NULL)
	{
		print_error(program_name, command_count, args[0]);
		free(args);
		return (127);
	}

	return (fork_and_run(args, full_path, program_name, command_count));
}
