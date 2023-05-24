#include "shell.h"
/**
 * _strncmp - a function that compares the first n caracteres
 * of 2 strings
 * @s1: first pointer to string
 * @s2: second pointer to string
 * @n: number of caracteres
 * Return: int
 */
int _strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int index = 0;

	while ((s1[i] != '\0' || s2[i] != '\0') && index < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/**
 * _atoi - a function that converts string to integer
 * @str: pointer to string
 * Return: the convert value
 */

int _atoi(char *str)
{
	int i;
	int con, p;

	con = 0;
	p = -1;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '-')
			p *= -1;

		if (str[i] > 47 && str[i] < 58)
		{
			if (con < 0)
				con = (con * 10) - (str[i] - '0');
			else
				con = (str[i] - '0') * -1;

			if (str[i + 1] < 48 || str[i + 1] > 57)
				break;
		}
	}
	if (p < 0)
		con *= -1;

	return (con);
}
