#include "shell.h"

/**
 * execute_command - forks a child process and executes a command
 * @line: the command to execute (must be a full path in Task 2)
 * @program_name: name of the shell program (argv[0]) for error messages
 * @command_count: number of commands executed so far, used in error messages
 *
 * Description: Creates a child process with fork. The child replaces
 * itself with the command using execve. The parent waits for the child
 * to finish before returning. If execve fails, the child prints an
 * error in the exact format required and exits with code 127
 * (standard "command not found" code).
 */
void execute_command(char *line, char *program_name, int command_count)
{
	pid_t child_pid;
	int status;
	char *argv[2];

	/* Build the argv array that execve needs — must end in NULL */
	argv[0] = line;
	argv[1] = NULL;

	/* Create a child process — duplicates the current process */
	child_pid = fork();

	/* fork returns -1 on failure (e.g., system ran out of processes) */
	if (child_pid == -1)
	{
		perror(program_name);
		return;
	}

	/* In the child process, fork returns 0 */
	if (child_pid == 0)
	{
		/*
		 * execve replaces the child's program with the requested one.
		 * We pass environ so the new program inherits PATH, HOME, etc.
		 * If execve returns, it means it failed.
		 */
		if (execve(line, argv, environ) == -1)
		{
			/* Print exact error format: program: count: command: not found */
			fprintf(stderr, "%s: %d: %s: not found\n",
				program_name, command_count, line);
			/* Exit with 127 = standard Unix code for "command not found" */
			exit(127);
		}
	}
	else
	{
		/* In the parent process — wait for the child to finish */
		wait(&status);
	}
}
