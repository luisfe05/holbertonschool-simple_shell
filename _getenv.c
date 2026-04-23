#include "shell.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of the variable to look up (e.g. "PATH")
 *
 * Description: Walks through the global environ array looking
 * for a string that starts with "name=". When found, returns
 * a pointer to the value (the part after the '='). Does not
 * allocate memory — returns a pointer into environ directly.
 *
 * Return: pointer to the value, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i = 0;
	int j;

	/* Guard against NULL input or empty environ */
	if (name == NULL || environ == NULL)
		return (NULL);

	/* Walk through each environment string */
	while (environ[i] != NULL)
	{
		j = 0;

		/* Compare character by character with name */
		while (name[j] != '\0' && environ[i][j] == name[j])
			j++;

		/* Full match + '=' means we found the variable */
		if (name[j] == '\0' && environ[i][j] == '=')
			return (&environ[i][j + 1]);

		i++;
	}

	/* Variable not found */
	return (NULL);
}
