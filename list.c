#include "shell.h"

/**
 * add_node - a function that adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: string field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - a function that adds a node to the end of the list
 * @head: address of pointer to head node
 * @s: string field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *s, int num)
{
	list_t *new_node, *n;

	if (!head)
		return (NULL);

	n = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (s)
	{
		new_node->s = _strdup(s);
		if (!new_node->s)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}

/**
 * delete_node_at_index - a function that deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *n, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		n = *head;
		*head = (*head)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *head;
	while (n)
	{
		if (i == index)
		{
			prev_n->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		prev_node = n;
		n = n->next;
	}
	return (0);
}

/**
 * free_list - a function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *n, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	n = head;
	while (n)
	{
		next_node = n->next;
		free(n->str);
		free(n);
		n = next_node;
	}
	*head_ptr = NULL;
}

