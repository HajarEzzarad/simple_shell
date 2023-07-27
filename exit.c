#include "shell.h"

/**
 **_strncpy - a function that copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		for (j = i; j < n; j++)
			dest[j] = '\0';
	}
	return (s);
}

/**
 **_strncat - a function that concatenates two strings
 *@dest: the destination string
 *@src: the source string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;

	while (dest[i] != '\0')
		i++;
	for (; src[j] != '\0' && j < n; j++)
	{
		dest[i] = src[j];
		i++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - a function that locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

