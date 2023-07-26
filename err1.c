#include "shell.h"

/**
 * _erroratoi - a function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erroratoi(char *str)
{
	int index = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	while (str[index] != '\0')
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			res *= 10;
			res += (str[index] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		index++;
	}
	return (res);
}

/**
 * print_err - prints an error message
 * @info: the parameter & return info struct
 * @errstr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_err(info_t *info, char *errstr)
{
	_errputs(info->fname);
	_errputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(errstr);
}

/**
 * print_dec - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs, cur;

	if (fd == STDERR_FILENO)
		__putchar = _errputchar;
	if (input < 0)
	{
		abs = -input;
		__putchar('-');
		count++;
	}
	else
		abs = input;
	cur = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		cur %= i;
	}
	__putchar('0' + cur);
	count++;

	return (count);
}

/**
 * conv_number - a function that converter function, a clone of itoa
 * @num: number
 * @b: base
 * @fl: argument flags
 *
 * Return: string
 */
char *conv_number(long int num, int b, int fl)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *p;
	unsigned long n = num;

	if (!(fl & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = fl & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';

	do {
		*--p = arr[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * rm_comments - a function that replaces
 * first instance of '#' with '\0'
 * @buffer: address of the string to modify
 * Return: Always 0;
 */
void rm_comments(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
}
