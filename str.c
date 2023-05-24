#include "shell.h"

/**
 * _strdup - a function that allocate memory for a new string
 * @s1: string to be duplicated.
 * Return: pointer
 */
char *_strdup(const char *s1)
{
	char *d;
	int i;

	i = 0;
	while (s1[i])
		i++;
	d = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	if (!d)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

/**
 * _strlen - a function that returns the length of a string
 * @str: string
 * Return: the length of a string
 */

int _strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/**
 * _strcmp - a functin that compares 2 strings.
 * @s1: first string
 * @s2: second string
 * Return: pointer
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/**
 * _strcat - a function that appends src to dest
 * @dest: destination string
 * @src: source string
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strcpy - a function that copy string from src to dest
 * @dest: pointer to destination string
 * @src: pointer to source string
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
