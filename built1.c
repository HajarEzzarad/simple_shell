#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->histy);
	return (0);
}

/**
 * unset_al - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_al(info_t *info, char *s)
{
	char *p, c;
	int rt;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	rt = delete_node_at_index(&(info->al),
		get_node_index(info->al, node_starts_with(info->al, s, -1)));
	*p = c;
	return (rt);
}

/**
 * set_al - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_al(info_t *info, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_al(info, s));

	unset_al(info, s);
	return (add_node_end(&(info->al), s, 0) == NULL);
}

/**
 * print_al - prints an alias string
 * @n: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_al(list_t *n)
{
	char *p = NULL, *a = NULL;

	if (n)
	{
		p = _strchr(n->s, '=');
		for (a = n->s; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int index = 0;
	char *p = NULL;
	list_t *n = NULL;

	if (info->argc == 1)
	{
		n = info->al;
		while (n)
		{
			print_al(n);
			n = n->next;
		}
		return (0);
	}
	for (index = 1; info->argv[index]; index++)
	{
		p = _strchr(info->argv[index], '=');
		if (p)
			set_al(info, info->argv[index]);
		else
			print_al(node_starts_with(info->al, info->argv[index], '='));
	}

	return (0);
}

