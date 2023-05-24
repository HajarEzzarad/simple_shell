#include "shell.h"

/**
 * _path - locate the executable file associated with a given command.
 * @data: string input
 * Return: void
 */

int _path(input *data)
{
	char *source, *path;
	char *ps = malloc(_strlen(_getenv("PATH") ? _getenv("PATH") : "") + 1);
	size_t source_len;
	int i = -1;

	if (!_getenv("PATH"))
		goto free;
	_strcpy(ps, _getenv("PATH"));
	if (ps == NULL)
		goto free;

	source = strtok(ps, ":");
	while (source)
	{
		source_len = _strlen(source) + _strlen(data->av[0]) + 2;
		path = malloc(source_len);
		if (path == NULL)
			return (-1);
		_strcpy(path, source);
		_strcat(path, "/");
		_strcat(path, data->av[0]);
		if (access(path, F_OK) == 0)
		{
			free(data->av[0]);
			data->av[0] = _strup(path);
			free(path);
			i = 0;
			break;
		}
		free(path);
		source = strtok(NULL, ":");
	}
free:
	free(ps);
	return (i);
}
/**
 * _getenv - retrieves the value of an environment variable.
 * @name: string input
 * Return: value of an environment variable
 */

char *_getenv(char *name)
{
	int i = -1;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	name_len = _strlen(name);

	while (environ[++i])
	{
		if (!_strncmp(environ[i], name, name_len) && environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}
	return (NULL);
}
