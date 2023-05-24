#include "shell.h"

/**
 * free_array - free an array of pointers
 * @array: array of pointers
 * @Return: no return
 */

void free_array(char **array)
{
	int i;
	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * _realloc - allocate memory
 * @ptr: a pointer
 * @size: size of pointer
 * Return: 
 */

char **_realloc(char **ptr, size_t size)
{
	int length;
	char **s;
	

	length = 0;
	if (ptr == NULL)
	{
		s = malloc(sizeof(char *) * 2);
		s[0] = NULL;
		s[1] = NULL;
		return (s);
	}

	s = malloc(size);
	while (ptr[length])
	{
		s[length] = _strdup(ptr[length]);
		free(ptr[length]);
		length++;
	}
	free(ptr);
	s[length++] = NULL;
	s[length] = NULL;
	return (s);
}
