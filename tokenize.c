#include "shell.h"

/**
 * count_tokens - counts the number of tokens in a string
 * @line: the input string to count tokens in
 * @delim: the delimiter to split by
 *
 * Description: Makes a copy of the line and uses strtok to count
 * how many tokens exist. Uses a copy because strtok modifies
 * the original string by replacing delimiters with null bytes.
 *
 * Return: number of tokens found, 0 on failure
 */
int count_tokens(char *line, char *delim)
{
	int count = 0;
	char *token;
	char *copy;

	/* Make a copy so strtok doesn't destroy the original line */
	copy = strdup(line);
	if (copy == NULL)
		return (0);

	/* Count each token strtok finds */
	token = strtok(copy, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}

	/* Free the copy — we only needed it for counting */
	free(copy);
	return (count);
}

/**
 * tokenize - splits a line into an array of tokens
 * @line: the input string to split
 *
 * Description: Counts the tokens first, allocates an array big
 * enough to hold them all plus a NULL terminator, then fills the
 * array using strtok. The caller is responsible for freeing the
 * returned array.
 *
 * Return: pointer to array of strings, or NULL on failure
 */
char **tokenize(char *line)
{
	int count = 0;
	int i = 0;
	char **args;
	char *token;

	/* Count tokens so we know how much memory to allocate */
	count = count_tokens(line, " ");

	/* Allocate array: one slot per token plus one for NULL terminator */
	args = malloc(sizeof(char *) * (count + 1));
	if (args == NULL)
		return (NULL);

	/* Split the line and fill the array */
	token = strtok(line, " ");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " ");
	}

	/* Last slot must be NULL — execve requires this */
	args[i] = NULL;

	return (args);
}
