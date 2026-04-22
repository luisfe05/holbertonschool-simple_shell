#include "shell.h"

/**
 * build_full_path - builds a full path by joining directory + command
 * @dir: the directory path (e.g. "/usr/bin")
 * @command: the command name (e.g. "ls")
 *
 * Description: Allocates a new string with the format "dir/command".
 * The caller is responsible for freeing the returned pointer.
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

	/* Measure both strings */
	while (dir[dir_len] != '\0')
		dir_len++;
	while (command[cmd_len] != '\0')
		cmd_len++;

	/* +2: one for the '/', one for the null terminator */
	full_path = malloc(sizeof(char) * (dir_len + cmd_len + 2));
	if (full_path == NULL)
		return (NULL);

	/* Copy directory part */
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}

	/* Add the '/' separator */
	full_path[i++] = '/';

	/* Copy command part */
	while (j < cmd_len)
	{
		full_path[i + j] = command[j];
		j++;
	}

	/* Null-terminate the string */
	full_path[i + j] = '\0';

	return (full_path);
}

/**
 * find_in_path - searches for a command in the PATH directories
 * @command: the command name to find (e.g. "ls")
 *
 * Description: If the command contains a '/', it's treated as a
 * full path and returned as a duplicated string if it exists.
 * Otherwise, walks through each directory in PATH and checks if
 * the command exists there using stat.
 *
 * Return: pointer to the full path if found (must be freed),
 * or NULL if the command wasn't found
 */
char *find_in_path(char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char *full_path;
	struct stat st;

	/* If command already has a '/', treat as absolute/relative path */
	if (command[0] == '/' || command[0] == '.')
	{
		if (stat(command, &st) == 0)
			return (_strdup(command));
		return (NULL);
	}

	/* Get PATH from environment */
	path_env = _getenv("PATH");
	if (path_env == NULL)
		return (NULL);

	/* Copy PATH because strtok modifies the string */
	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	/* Try each directory in PATH one by one */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = build_full_path(dir, command);
		if (full_path != NULL && stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}

	/* Not found in any PATH directory */
	free(path_copy);
	return (NULL);
}
