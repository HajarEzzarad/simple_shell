#include "shell.h"

/**
 * _getenviron - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **_getenviron(info_t *info)
{
	if (!info->environ || info->envr_chang)
	{
		info->environ = list_to_strings(info->env);
		info->envr_chang = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int _unsetenv(info_t *info, char *v)
{
	list_t *n = info->env;
	size_t i = 0;
	char *p;

	if (!n || !v)
		return (0);

	while (n)
	{
		p = starts_with(n->s, v);
		if (p && *p == '=')
		{
			info->envr_chang = delete_node_at_index(&(info->env), i);
			i = 0;
			n = info->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (info->envr_chang);
}

/**
 * _setenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * @v: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *v, char *val)
{
	char *buffer = NULL;
	list_t *n;
	char *p;

	if (!v || !val)
		return (0);

	buffer = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, v);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	n = info->env;
	while (n)
	{
		p = starts_with(n->s, v);
		if (p && *p == '=')
		{
			free(n->s);
			n->s = buffer;
			info->envr_chang = 1;
			return (0);
		}
		n = n->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->envr_chang = 1;
	return (0);
}

