#include "shell.h"

/**
 * gethistoryfile - a function that gets the history file
 * @info: parameter struct
 * Return: allocated string containg history file
 */

char *gethistoryfile(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * write_hist - a func that creates a file
 * or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = gethistoryfile(info);
	list_t *n = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (n = info->histy; n; n = n->next)
	{
		_putsfiledesc(n->s, fd);
		_putfiledesc('\n', fd);
	}
	_putfiledesc(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - a function that reads history from file
 * @info: the parameter struct
 * Return: histocount on success, 0 otherwise
 */
int read_hist(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gethistoryfile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_hist_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(info, buf + last, linecount++);
	free(buf);
	info->histocount = linecount;
	while (info->histocount-- >= HISTORY_MAX)
		delete_node_at_index(&(info->histy), 0);
	renumber_hist(info);
	return (info->histocount);
}

/**
 * build_hist_list - a function that adds entry
 * to a history linked list
 * @info: Structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: 0 (succes)
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *n = NULL;

	if (info->histy)
		n = info->histy;
	add_node_end(&n, buf, linecount);
	if (!info->histy)
		info->histy = n;
	return (0);
}

/**
 * renumber_hist - a func that renumbers the history
 * linked list after changes
 * @info: Structure
 * Return: the new histocount
 */
int renumber_hist(info_t *info)
{
	list_t *n = info->histy;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (info->histocount = i);
}

