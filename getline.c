#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHand);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			rm_comments(*buf);
			build_hist_list(info, *buf, info->histocount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->comd_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		checkchain(info, buf, &j, i, len);
		while (j < len)
		{
			if (ischain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->comd_buffer_type = COMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: the buffer
 * @i: size
 *
 * Return: res
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t res = 0;

	if (*i)
		return (0);
	res = read(info->readfiledesc, buffer, READ_BUFFER_SIZE);
	if (res >= 0)
		*i = res;
	return (res);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t j;
	ssize_t res = 0, s = 0;
	char *p = NULL, *new_ptr = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	res = read_buffer(info, buffer, &len);
	if (res == -1 || (res == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	j = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = _realloc(p, s, s ? s + j : j + 1);
	if (!new_ptr)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_ptr, buffer + i, j - i);
	else
		_strncpy(new_ptr, buffer + i, j - i + 1);

	s += j - i;
	i = j;
	p = new_ptr;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHand - blocks ctrl-C
 * @signum: the signal number
 * Return: void
 */
void sigintHand(__attribute__((unused))int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

