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
		return (NULL);
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
	char *argv[1024], absolute_path[1024], *buffer = NULL;
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
			strcpy(absolute_path, find_path(argv[0]));
		else
			strcpy(absolute_path, argv[0]);
		if (stat(absolute_path, &st) != -1)
		{
			argv[0] = absolute_path;
			pid = fork();
			if (pid == 0)
			{
				execv(argv[0], argv);
				perror("execv failed");
				exit(EXIT_FAILURE);
			}
			else
				wait(&status);
		}
		else
			printf("Command not found: %s\n", argv[0]);
		printf("$ ");
	}
	free(buffer);
	return (0);
}
