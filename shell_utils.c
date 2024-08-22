#include "main.h"
/**
 * get_flags - tokenises user arguments
 * @buffer: the user input string
 * @arguments: buffer
 * @env: enviroment
 * Return: an array of user arguments
 */
char **get_flags(char *buffer, char *arguments[], char **env)
{
	char *path, *processed_arg;
	int i, args_size = 8;

	arguments = malloc(args_size * sizeof(char *));
	if (arguments == NULL)
		return (NULL);
	path = strtok(buffer, " \n\r\t");
	if (path == NULL)
		return (NULL);
	arguments[0] = path;
	if (strcmp(arguments[0], "exit") == 0)
	{
		free(buffer);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(arguments[0], "env") == 0)
	{
		for (; *env != NULL; env++)
			printf("%s\n", *env);
		return (0);
	}
	processed_arg = path;
	for (i = 1; processed_arg != NULL; i++)
	{
		if (i >= args_size)
		{
			args_size *= 2;
			arguments = realloc(arguments, args_size * sizeof(char *));
			if (arguments == NULL)
				return (NULL);
		}
		processed_arg = strtok(NULL, " \n\r\t");
		arguments[i] = processed_arg;
	}
	arguments[i] = NULL;
	return (arguments);
}
/**
 * handle_arg - analizes the first argument
 * @arguments: Buffer
 * @av: argument vector
 * @env: enviroment
 * @count: number of times argument has been passed
 * Return: argument analized
 */
int handle_arg(char *arguments[], char **av, char **env, size_t count)
{
	char *path = NULL;
	pid_t pid = 0;
	int status = 0;
	struct stat st;

	if (arguments[0][0] != '/')
	{
		path = find_path(arguments[0], av, env, count);
		if (path == NULL)
			return (0);
		arguments[0] = path;
	}
	if (stat(arguments[0], &st) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(arguments[0], arguments, env);
			handle_error(av[0], arguments[0], count);
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
			wait(&status);
		if (arguments[0] == path)
			free(path);
	}
	else
	{
		handle_error(av[0], arguments[0], count);
		return (0);
	}
	return (0);
}
/**
 * handle_error - returns a error message
 * @count: number of commands since start
 * @av: name of the shell
 * @command: the command that gave the error
 */
void handle_error(char *av, char *command, size_t count)
{
	char *error;
	int size = sizeof(av) + sizeof(count) + sizeof(command) + 4;

	error = malloc(size * sizeof(char));
	sprintf(error, "%s: %li: %s", av, count, command);
	perror(error);
	free(error);
}
