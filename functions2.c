#include "shell.h"

/**
 * _white_spaces - a function that checkes white spaces
 * @s: string
 */
void _white_spaces(char *s)
{
	int i = 0, j = 0;
	int l = _strlen(s);

	while (i < l && (s[i] == ' ' || s[i] == '\t'))
		i++;

	while (i < l)
	{
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = '\0';

	i = _strlen(s) - 1;
	while (i > 0 && (s[i] == ' ' || s[i] == '\t'))
	{
		s[i] = '\0';
		i--;
	}
}
