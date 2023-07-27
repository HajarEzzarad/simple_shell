#include "shell.h"

/**
 *_errputs - a function that prints an input string
 * @s: the string to be printed
 * Return:
 */
void _errputs(char *s)
{
	int index;

	if (!s)
		return;
	for (index = 0; s[index] != '\0'; index++)
		_errputchar(s[index]);
}

/**
 * _errputchar - a function that writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _errputchar(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 * _putfiledesc - a function that writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfiledesc(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, index);
		index = 0;
	}
	if (c != BUFFER_FLUSH)
		buffer[index++] = c;
	return (1);
}

/**
 *_putsfiledesc - a function that prints an input string
 * @s: the string
 * @fd: the filedescriptor to write to
 * Return: the number of chars
 */
int _putsfiledesc(char *s, int fd)
{
	int index = 0;

	if (!s)
		return (0);
	while (*s)
	{
		index = index + _putfiledesc(*s++, fd);
	}
	return (index);
}
