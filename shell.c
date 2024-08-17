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
 * main - simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	size_t buffsize = 1024;
	char *argv[1024], *buffer = NULL;
	int status;
	pid_t pid;
	struct stat st;

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
		if (argv[0][0] != '/')
		{
			if (find_path(argv[0]) == -1)
			{
				printf("$ ");
				continue;
			}
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
		}
		else
			continue;
		if (argv[0] != NULL && argv[0][0] != '/')
			free(argv[0]);
		printf("$ ");
	}
	free(buffer);
	return (0);
}
