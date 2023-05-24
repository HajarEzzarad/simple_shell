#include "shell.h"




/**
 * builtin_env - prints the current environment
 * @data: input struct input
 * Return: void
 */
void builtin_env(input *data)
{
	int i = 0;

	(void)data;
	while (environ[i])
	{
		_printf(environ[i]);
		_printf("\n");
		i++;
	}
}

/**
 * builtin_exit - exits the shell
 * @data: input struct input
 * Return: void
 */
void builtin_exit(input *data)
{
	int status = 0;

	if (data->av[1])
		status = _atoi(data->av[1]);
	free_array(data->av);
	free(data->command);
	free(data);
	exit(status);
}

/**
 * exec_builtin - check if built in and then exec
 * @data: input struct input
 * Return: 1 if built in, 0 if not
 */
int exec_builtin(input *data)
{

	builtin builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{NULL, NULL},
	};
	int i = 0;

	for (i = 0; builtin[i].command; i++)
	{
		if (strcmp(data->av[0], builtin[i].command) == 0)
		{
			builtin[i].f(data);
			return (1);
		}
	}
	return (0);
}




/**
 * get_env - get an environnement 
 * @env_var: variable of env
 * Return: return NULL
 */
char *get_env(char *env_var)
{
	int i = 0;
	char *key;

	while (environ[i])
	{
		key = strtok(environ[i], "=");
		if (_strcmp(env_var, key) == 0)
			return (strtok(NULL, "\n"));
		i++;
	}

	return (NULL);
}
