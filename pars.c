#include "shell.h"

/**
 * iscmd - determines if a file is an executable command
 * @info: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int iscmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupl_chars - duplicates characters
 * @pathstr: the PATH string
 * @sta: starting index
 * @stp: stopping index
 * Return: pointer to new buffer
 */
char *dupl_chars(char *pathstr, int sta, int stp)
{
	static char buf[1024];
	int i = 0, j = 0;

	for (j = 0, i = sta; i < stp; i++)
		if (pathstr[i] != ':')
			buf[j++] = pathstr[i];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path - a function that finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @comd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *comd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(comd) > 2) && starts_with(comd, "./"))
	{
		if (iscmd(info, comd))
			return (comd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dupl_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, comd);
			else
			{
				_strcat(path, "/");
				_strcat(path, comd);
			}
			if (iscmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
