#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
char *buffer = NULL;
void handle_sigint(int signal)
{
	free(buffer);
	exit(0);
}
int main(void)
{
	ssize_t buffsize = 1024;
	char *path, *arguments;
	int status, i;
	char *argv[1024];
	struct stat st;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
		return(-1);
	signal(SIGINT, handle_sigint);

	printf("$ ");
	while (getline(&buffer, &buffsize, stdin) != -1)
	{
		path = strtok(buffer, " \n\r\t");
		if (stat(path, &st) != -1)
		{
			argv[0] = path;
			arguments = path;
			for (i = 1; arguments != NULL; i++)
			{
				arguments = strtok(NULL, " \n\r\t");
				argv[i] = arguments;
			}
			argv[i] = NULL;
			pid_t p = fork();
			if (p == 0)
			{
				execv(argv[0], argv);
			}
			else
			{
				wait(&status);
			}
		}
		printf("$ ");
	}
	free(buffer);
	return (0);
}
