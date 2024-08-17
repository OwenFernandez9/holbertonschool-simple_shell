#include "main.h"
/**
 * get_flags - tokenises user arguments
 * @buffer: the user input string
 * @argv: the array to fill
 * Return: an array of user arguments
 */
char **get_flags(char *buffer, char *argv[])
{
	char *path, *arguments;
	int i;

	path = strtok(buffer, " \n\r\t");
	if (path == NULL)
	{
		perror("./shell");
		return (NULL);
	}
	argv[0] = path;
	arguments = path;
	for (i = 1; arguments != NULL; i++)
	{
		arguments = strtok(NULL, " \n\r\t");
		argv[i] = arguments;
	}
	argv[i] = NULL;
	return (argv);
}
/**
 * handle_arg - analizes the first argument
 * @argv: the first argument inputed
 * Return: argument analized
 */
int handle_arg(char *argv[1024])
{
	char *path = NULL;
	pid_t pid = 0;
	int status = 0;
	struct stat st;

	if (argv[0][0] != '/')
	{
		path = find_path(argv[0]);
		if (path == NULL)
		{
			printf("$ ");
			return(0);
		}
		argv[0] = path;
	}
	if (stat(argv[0], &st) != -1)
	{
		pid = fork();
		if (pid == 0)
		{
			execv(argv[0], argv);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);
		if (argv[0] == path)
			free(path);
	}
	else
	{
		perror("./shell");
		return(0);
	}
	return (0);
}
/**
 * main - simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	size_t buffsize = 1024;
	char *argv[1024], *buffer = NULL;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
		return (-1);
	printf("$ ");
	while (getline(&buffer, &buffsize, stdin) != -1)
	{
		if (get_flags(buffer, argv) == NULL)
		{
			printf("$ ");
			continue;
		}
		handle_arg(argv);
		printf("$ ");
	}
	free(buffer);
	return (0);
}
