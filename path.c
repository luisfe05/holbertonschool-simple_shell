#include "shell.h"

/**
 * build_full_path - builds a full path by joining directory + command
 * @dir: the directory path
 * @command: the command name
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

	while (dir[dir_len] != '\0')
		dir_len++;
	while (command[cmd_len] != '\0')
		cmd_len++;

	full_path = malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (full_path == NULL)
		return (NULL);

	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}

	full_path[i++] = '/';

	while (j < cmd_len)
	{
		full_path[i + j] = command[j];
		j++;
	}

	full_path[i + j] = '\0';
	return (full_path);
}

/**
 * search_path_dirs - iterates through PATH directories to find command
 * @path_copy: a writable copy of the PATH variable
 * @command: the command name to search for
 *
 * Description: Uses strtok to split PATH by ':' and tries each
 * directory to see if the command exists there.
 *
 * Return: full path if found (must be freed), NULL otherwise
 */
char *search_path_dirs(char *path_copy, char *command)
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
 * Description: If command starts with '/' or '.', treats it as
 * a direct path. Otherwise walks PATH using search_path_dirs.
 *
 * Return: full path if found (must be freed), NULL if not found
 */
char *find_in_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *result;
	struct stat st;

	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	result = search_path_dirs(path_copy, command);
	free(path_copy);
	return (result);
}