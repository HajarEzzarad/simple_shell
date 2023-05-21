#include "shell.h"

int status;

char *shell_name;

/**
 * command_manager - manages the process a command goes through to get executed
 * @args: command and arguments
 *
 * Return: TRUE if success, FALSE if failure
 */
int command_manager(char **args)
{
	char **argsPTR = args;
	int prevEVAL = NEITHER;
	int noERR = TRUE;
	char prevOP = 'c';
	char nextOP = 'c';
	int whatDO;

	while (*args != NULL && prevEVAL != EXIT_SHELL)
	{
		while (*argsPTR != NULL && **argsPTR != '&'
		       && **argsPTR != '|')
			argsPTR++;

		if (str_compare(*argsPTR, "||", MATCH) == TRUE)
		{
			*argsPTR = NULL;
			argsPTR++;
			nextOP = '|';
		}
		if (str_compare(*argsPTR, "&&", MATCH) == TRUE)
		{
			*argsPTR = NULL;
			argsPTR++;
			nextOP = '&';
		}
		if (nextOP == 'c')
			break;

		prevEVAL = and_or(args, prevOP, prevEVAL);
		if (prevEVAL == FALSE)
			noERR = FALSE;
		prevOP = nextOP;
		args = argsPTR;
	}

	if (nextOP == 'c')
	{
		whatDO = execute_command(args);

		if (whatDO == EXIT_SHELL)
			return (EXIT_SHELL);
	}

	if (noERR == FALSE || whatDO == FALSE)
		return (FALSE);

	return (TRUE);
}

/**
 * built_ins - checks if a command is a built in
 * @args: command and arguments
 *
 * Return: SKIP_FORK if built in, DO_EXECVE if not a built in, EXIT_SHELL if
 * exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int built_ins(char **args)
{
	char **argsPTR = args;
	int i;

	while (*argsPTR != NULL)
	{
		if (**argsPTR == '#')
		{
			*argsPTR = NULL;
			break;
		}
		*argsPTR = check_for_vars(*argsPTR);

		argsPTR++;
	}
	if (*args == NULL)
		return (SKIP_FORK);

	i = alias_func(args, FALSE);
	if (i == DO_EXECVE || i == SKIP_FORK)
		return (i);

	if (str_compare("exit", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = _atoi(args[1]);
		if (status < 0)
		{
			status = 2;
			err_message(args[0], args[1]);
			return (SKIP_FORK);
		}
	}
	if (str_compare("exit", *args, MATCH) == TRUE)
		return (EXIT_SHELL);
	else if (str_compare("setenv", *args, MATCH) == TRUE && args[1] != NULL)
		return (_setenv(args[1], args[2]));
	else if (str_compare("unsetenv", *args, MATCH) == TRUE
		 && args[1] != NULL)
		return (_unsetenv(args[1]));
	else if (str_compare("cd", *args, MATCH) == TRUE)
		return (change_dir(args[1]));
	else if (str_compare("env", *args, MATCH) == TRUE)
		return (print_env());

	return (DO_EXECVE);
}

/**
 * and_or - deals with command line logical operators
 * @args: command and arguments
 * @operator: first char of logical operator
 * @last_compare: if last command in logic evaluated to true or false
 *
 * Return: if this command evaluates to true or false
 */
int and_or(char **args, char operator, int last_compare)
{
	int i;

	if (last_compare == NEITHER)
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}
	if (last_compare == TRUE && operator == '&')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == FALSE && operator == '|')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == TRUE && operator == '|')
		return (TRUE);

	return (FALSE);
}

/**
 * check_command - checks if a non-built-in exists
 * @args: argument and commands
 *
 * Return: TRUE if valid command, FALSE if not
 */
char *check_command(char **args)
{
	char *commandBuf;
	char *fullBUF;
	char *pathSTR = NULL;
	char *pathPTR;
	char *pathTMP;
	char **pathVAR;
	char **path_var_ptr;

	if (access(*args, X_OK) == 0)
		return (_strdup(*args));

	if (get_array_element(environ, "PATH") != NULL)
		pathSTR = _strdup(get_array_element(environ, "PATH") + 5);

	pathPTR = pathSTR;

	if (pathSTR != NULL)
	{
		if (*pathSTR == ':')
		{
			commandBuf = str_concat("./", *args);
			if (access(commandBuf, X_OK) == 0)
			{
				free(pathSTR);
				return (commandBuf);
			}
			else
			{
				free(commandBuf);
				pathPTR = _strdup(pathSTR + 1);
				free(pathSTR);
				pathSTR = pathPTR;
			}
		}
		while (*pathPTR != '\0')
		{
			if (*pathPTR == ':' && *(pathPTR + 1) == ':')
			{
				*(pathPTR + 1) = '\0';
				pathTMP = (str_concat(pathSTR, ".:"));
				pathPTR = str_concat(pathTMP, pathPTR + 2);
				free(pathSTR);
				free(pathTMP);
				pathSTR = pathPTR;
			}
			pathPTR++;
		}
	}

	pathVAR = make_array(pathSTR, ':', NULL);
	path_var_ptr = pathVAR;

	commandBuf = str_concat("/", *args);

	fullBUF = _strdup(commandBuf);

	while (*path_var_ptr != NULL && access(fullBUF, X_OK) != 0)
	{
		free(fullBUF);
		fullBUF = str_concat(*path_var_ptr, commandBuf);
		path_var_ptr++;
	}

	free(commandBuf);
	free(pathSTR);
	free(pathVAR);

	if (access(fullBUF, X_OK) != 0)
	{
		err_message(args[0], NULL);
		free(fullBUF);
		return (NULL);
	}

	return (fullBUF);
}

/**
 * execute_command - executes a command
 * @args: command and arguments
 *
 * Return: TRUE or EXIT_SHELL
 */
int execute_command(char **args)
{
	char *bufPTR = *args;
	char *command_name;
	pid_t pid;
	int what_do = built_ins(args);

	if (what_do == DO_EXECVE)
	{
		command_name = check_command(args);
		if (command_name == NULL)
			return (FALSE);

		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(command_name, args, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(command_name);
		fflush(stdin);
	}

	if (str_compare("false", *args, MATCH) == TRUE)
		status = 1;

	if (*args != bufPTR)
		free(*args);
	args++;

	while (*args != NULL)
	{
		while (*bufPTR != '\0')
		{
			bufPTR++;
		}
		bufPTR++;

		if (*args != bufPTR)
			free(*args);

		args++;
	}

	if (what_do == EXIT_SHELL)
		return (EXIT_SHELL);

	if (status != 0)
		return (FALSE);

	return (TRUE);
}
