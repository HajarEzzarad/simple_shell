#include "shell.h"

/**
 * hshell - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hshell(info_t *info, char **av)
{
	ssize_t r = 0;
	int built_ret = 0;

	while (r != -1 && built_ret != -2)
	{
		clearinfo(info);
		if (interactive(info))
			_puts("$ ");
		_errputchar(BUFFER_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			setinfo(info, av);
			built_ret = find_built(info);
			if (built_ret == -1)
				find_comd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		freeinfo(info, 0);
	}
	write_hist(info);
	freeinfo(info, 1);
	if (!interactive(info) && info->st)
		exit(info->st);
	if (built_ret == -2)
	{
		if (info->err_n == -1)
			exit(info->st);
		exit(info->err_n);
	}
	return (built_ret);
}

/**
 * find_built - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_built(info_t *info)
{
	int i, built_ret = -1;
	built_t builttbl[] = {
		{"exit", _myexit},
		{"env", _envm},
		{"help", _help},
		{"history", _history},
		{"setenv", _setenvm},
		{"unsetenv", _unsetenvm},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builttbl[i].type; i++)
		if (_strcmp(info->argv[0], builttbl[i].type) == 0)
		{
			info->line_count++;
			built_ret = builttbl[i].f(info);
			break;
		}
	return (built_ret);
}

/**
 * find_comd - a functtion that finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void find_comd(info_t *info)
{
	char *p = NULL;
	int i, j;

	info->p = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	p = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->p = p;
		f_comd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && iscmd(info, info->argv[0]))
			f_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->st = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * f_comd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void f_comd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->p, info->argv, _getenviron(info)) == -1)
		{
			freeinfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->st));
		if (WIFEXITED(info->st))
		{
			info->st = WEXITSTATUS(info->st);
			if (info->st == 126)
				print_err(info, "Permission denied\n");
		}
	}
}

