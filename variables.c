#include "shell.h"

/**
 * ischain - a function that test if current char
 * in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int ischain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->comd_buffer_type = COMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->comd_buffer_type = COMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->comd_buffer_type = COMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void checkchain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->comd_buffer_type == COMD_AND)
	{
		if (info->st)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->comd_buffer_type == COMD_OR)
	{
		if (!info->st)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_al - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_al(info_t *info)
{
	int i;
	list_t *n;
	char *p;

	for (i = 0; i < 10; i++)
	{
		n = node_starts_with(info->al, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(n->s, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_v - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_v(info_t *info)
{
	int i = 0;
	list_t *n;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(conv_number(info->st, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_str(&(info->argv[i]),
				_strdup(conv_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(info->env, &info->argv[i][1], '=');
		if (n)
		{
			replace_str(&(info->argv[i]),
				_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_str(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_str - a function that replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

