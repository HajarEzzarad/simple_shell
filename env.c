#include "shell.h"

/**
 * _envm - a function that prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _envm(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - a function that gets the value of an environ variable
 * @info: Structure arguments.
 * @name: environ variable name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *n = info->env;
	char *p;

	while (n)
	{
		p = starts_with(n->s, name);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * _setenvm - a function that initialize a new environment
 * variable, or modify an existing one
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _setenvm(info_t *info)
{
	if (info->argc != 3)
	{
		_errputs("\t\tincorrect number \n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenvm - a function that remove an environment variable
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _unsetenvm(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_errputs("\t\t too few arguements\n");
		return (1);
	}

	index = 1;
	while (index <= info->argc)
	{
		_unsetenv(info, info->argv[index]);
		index++;
	}
	return (0);
}

/**
 * pop_env_list - a function that populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * Return: Always 0
 */
int pop_env_list(info_t *info)
{
	list_t *n = NULL;
	size_t index;

	index = 0;
	while (environ[index])
	{
		add_node_end(&n, environ[index], 0);
		index++;
	}
	info->env = n;
	return (0);
}

