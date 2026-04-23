#include "shell.h"

/**
 * build_full_path - builds a full path by joining directory + command
 * @dir: the directory path
 * @command: the command name
 *
 * Description: Allocates a new string with format "dir/command".
 *
 * Return: pointer to the full path, or NULL on failure
 */
char *build_full_path(char *dir, char *command)
{
	int dir_len = 0;
	int cmd_len = 0;
	int i = 0;
	int j = 0;
	char *full_path;

	/* measure both strings */
	while (dir[dir_len] != '\0')
		dir_len++;
	while (command[cmd_len] != '\0')
		cmd_len++;

	/* +2 for '/' and '\0' */
	full_path = malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (full_path == NULL)
		return (NULL);

	/* copy the directory */
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}

	/* add the slash */
	full_path[i++] = '/';

	/* copy the command */
	while (j < cmd_len)
	{
		full_path[i + j] = command[j];
		j++;
	}

	full_path[i + j] = '\0';
	return (full_path);
}

/**
 * try_paths - tries each directory in PATH to find the command
 * @path_copy: a writable copy of the PATH value
 * @command: the command name
 *
 * Description: Uses strtok to split PATH by ':' and tries each
 * directory with stat to see if the command exists there.
 *
 * Return: full path if found, NULL otherwise
 */
char *try_paths(char *path_copy, char *command)
{
	char *dir;
	char *full_path;
	struct stat st;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_full_path(dir, command);
		if (full_path != NULL && stat(full_path, &st) == 0)
			return (full_path);
		free(full_path);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * find_in_path - searches for a command in the PATH directories
 * @command: the command name to find
 *
 * Description: If command has '/' or '.', treats as full path.
 * Otherwise searches through each directory in PATH.
 *
 * Return: full path if found (must be freed), NULL otherwise
 */
char *find_in_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *result;
	struct stat st;

	/* if command is a path, check it directly */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	/* get the PATH variable */
	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	/* copy it because strtok modifies the string */
	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	/* search each directory */
	result = try_paths(path_copy, command);
	free(path_copy);
	return (result);
}
