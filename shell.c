#include "main.h"
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
	size_t buffsize = 1024, count = 0;
	char *arguments[1024], *buffer = NULL;
	(void)ac;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
		return (-1);
	if (isatty(STDIN_FILENO))
		printf("$ ");
	while (getline(&buffer, &buffsize, stdin) != -1)
	{
		count++;
		if (get_flags(buffer, arguments, env) == NULL)
		{
			printf("$ ");
			continue;
		}
		if (invalid_path(arguments[0]) == 1)
		{
			handle_error(av[0], arguments[0], count);
			printf("$ ");
			continue;
		}
		handle_arg(arguments, av, env, count);
		if (isatty(STDIN_FILENO))
			printf("$ ");
	}
	free(buffer);
	return (0);
}
