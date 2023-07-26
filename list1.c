#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *n = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		str = malloc(_strlen(n->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, n->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @n: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *n, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(n->s, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @n: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t i;

	for (i = 0; h; i++)
	{
		if (h == n)
			return (i);
		h = h->next;
	}
	return (-1);
}

