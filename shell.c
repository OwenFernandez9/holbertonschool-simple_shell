#include "main.h"
/**
 * get_flags - tokenises user arguments
 * @buffer: the user input string
 * @arguments: buffer
 * @av: argument vector
 * @env: enviroment
 * Return: an array of user arguments
 */
char **get_flags(char *buffer, char *arguments[], char **av, char **env)
{
	char *path, *processed_arg;
	int i;

	path = strtok(buffer, " \n\r\t");
	if (path == NULL)
	{
		perror(av[0]);
		return (NULL);
	}
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
 * Return: argument analized
 */
int handle_arg(char *arguments[1024], char **av, char **env)
{
	char *path = NULL;
	pid_t pid = 0;
	int status = 0;
	struct stat st;

	if (arguments[0][0] != '/')
	{
		path = find_path(arguments[0], av, env);
		if (path == NULL)
			return (0);
		arguments[0] = path;
	}
	if (stat(arguments[0], &st) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(arguments[0], arguments, env);
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);
		if (arguments[0] == path)
			free(path);
	}
	else
	{
		perror(av[0]);
		return (0);
	}
	return (0);
}
/**
 * main - simple shell
 *
 * @ac: argument count
 * @av: argument vector
 * @env: enviroment
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	size_t buffsize = 1024;
	char *arguments[1024], *buffer = NULL;
	(void)ac;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
		return (-1);
	if (isatty(STDIN_FILENO))
		printf("$ ");
	while (getline(&buffer, &buffsize, stdin) != -1)
	{
		if (get_flags(buffer, arguments, av, env) == NULL)
		{
			printf("$ ");
			continue;
		}
		handle_arg(arguments, av, env);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(buffer);
	return (0);
}
