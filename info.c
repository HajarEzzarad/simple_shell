#include "shell.h"

/**
 * clearinfo - initializes info_t struct
 * @info: struct address
 */
void clearinfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->p = NULL;
	info->argc = 0;
}

/**
 * setinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setinfo(info_t *info, char **av)
{
	int index = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (index = 0; info->argv && info->argv[index]; index++)
			;
		info->argc = index;

		replace_al(info);
		replace_v(info);
	}
}

/**
 * freeinfo - frees info_t struct fields
 * @info: struct address
 * @a: true if freeing all fields
 */
void freeinfo(info_t *info, int a)
{
	ffree(info->argv);
	info->argv = NULL;
	info->p = NULL;
	if (a)
	{
		if (!info->comd_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->histy)
			free_list(&(info->histy));
		if (info->al)
			free_list(&(info->al));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->comd_buffer);
		if (info->readfiledesc > 2)
			close(info->readfiledesc);
		_putchar(BUFFER_FLUSH);
	}
}

