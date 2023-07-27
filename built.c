#include "shell.h"

/**
 * _myexit - a function that exits the shell
 * @info: Structure containing potential arguments.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit;

	if (info->argv[1])
	{
		exit = _erroratoi(inf->argv[1]);
		if (exit == -1)
		{
			info->st = 2;
			print_err(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_n = _erroratoi(info->argv[1]);
		return (-2);
	}
	info->err_n = -1;
	return (-2);
}

/**
 * _mcd - a function that changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _mcd(info_t *info)
{
	char *s, *dir, buf[1024];
	int chdir_rt;

	s = getcwd(buf, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_rt = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_rt = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_rt = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rt = chdir(info->argv[1]);
	if (chdir_rt == -1)
	{
		print_err(info, "can't cd to ");
		_errputs(info->argv[1]), _errputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _mhelp - a function that changes the current direc of the process
 * @info: Structure containing potential arguments.
 *  Return: 0
 */
int _mhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call\n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
