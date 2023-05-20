#include "shell.h"

/**
 * _strlen - a function that returns length of a string
 * @str: string
 * Return: length of the string
 */
int _strlen(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		i++;
		str++;
	}
	return (i);
}

/**
 * _strdup - a function that allcates a space
 * @src: string source
 * Return: a pointer
 */
char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = malloc(len + 1);
	char *ptr;

	if (dest == NULL)
		exit(EXIT_FAILURE);

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}
/**
 * str_concat - concatenates 2 strings
 * @s1: first string
 * @s2: second string
 * Return: a pointer
 */
char *str_concat(char *s1, char *s2)
{
	int len = _strlen(s1) + _strlen(s2);
	char *dest = malloc(len + 1);
	char *ptr = dest;

	if (s1 != NULL)
	{
		while (*s1 != '\0')
		{
			*ptr = *s1;
			ptr++;
			s1++;
		}
	}
	if (s2 != NULL)
	{
		while (*s2 != '\0')
		{
			*ptr = *s2;
			ptr++;
			s2++;
		}
	}
	*ptr = '\0';

	return (dest);
}

/**
 * str_compare -  a function that compares two strings
 * @s1: first string
 * @s2: second string
 * @pref_or_match: if string needs to be matched or just needs
 * a prefix
 *
 * Retrun: the difference between strings
 */
int str_compare(char *s1, char *s2, int pref_or_match)
{
	if (s1 == NULL || s2 == NULL)
		return (FALSE);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);

		s1++;
		s2++;
	}

	if (pref_or_match == PREFIX)
		return (TRUE);

	if (*s1 == *s2)
		return (TRUE);

	return (FALSE);
}
