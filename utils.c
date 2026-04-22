#include "shell.h"

/**
 * _strdup - duplicates a string by allocating new memory
 * @str: the source string to duplicate
 *
 * Description: Allocates memory with malloc and copies the contents
 * of str into the new buffer. The caller is responsible for freeing
 * the returned pointer.
 *
 * Return: pointer to the new string, or NULL on failure
 */
char *_strdup(char *str)
{
	int i = 0;
	int len = 0;
	char *dup;

	/* Guard against NULL input */
	if (str == NULL)
		return (NULL);

	/* Count the length of the string (excluding null terminator) */
	while (str[len] != '\0')
		len++;

	/* Allocate memory for the copy, +1 for null terminator */
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	/* Copy each character including the null terminator */
	while (i <= len)
	{
		dup[i] = str[i];
		i++;
	}

	return (dup);
}
