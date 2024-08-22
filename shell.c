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
	size_t buffsize = 0, count = 0;
	char **arguments = NULL, *buffer = NULL;
	(void)ac;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	while (getline(&buffer, &buffsize, stdin) != -1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		count++;
		arguments = NULL;
		arguments = get_flags(buffer, arguments, env);
		if (arguments == NULL)
			continue;
		if (invalid_path(arguments[0]) == 1)
		{
			handle_error(av[0], arguments[0], count);
			free(arguments);
			continue;
		}
		handle_arg(arguments, av, env, count);
		free(arguments);
	}
	free(buffer);
	printf("\n");
	return (0);
}
