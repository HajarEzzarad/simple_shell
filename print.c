#include "shell.h"

/**
* _putchar - writes the char c tou stdout.
* @c: the char to print
* Return: 1 for succes and -1 for error.
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _printf - Writes string to stdout
 *
 * @s1: string to print
 *
 * Return: On success 1.
*/

void _printf(const char *s1)
{
	int i = 0;

	while (s1[i] != '\0')
	{
		_putchar(s1[i]);
		i++;
	}
}
