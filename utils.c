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

	/* guard against NULL input */
	if (str == NULL)
		return (NULL);

	/* count the length of the string */
	while (str[len] != '\0')
		len++;

	/* allocate memory for the copy, +1 for null terminator */
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);

	/* copy each character including the null terminator */
	while (i <= len)
	{
		dup[i] = str[i];
		i++;
	}

	return (dup);
}

/**
 * _strcmp - compares two strings character by character
 * @s1: first string
 * @s2: second string
 *
 * Description: Walks both strings at the same time comparing
 * each character. Stops when characters differ or end is reached.
 *
 * Return: 0 if equal, positive if s1 > s2, negative if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	/* walk both strings until they differ or both end */
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;

	/* return difference of the first differing characters */
	return (s1[i] - s2[i]);
}
