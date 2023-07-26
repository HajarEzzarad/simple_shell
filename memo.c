#include "shell.h"

/**
 * bfree - a function that frees a pointer and NULLs the address
 * @p: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

