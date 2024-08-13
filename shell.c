#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(void)
{
	ssize_t buffsize = 1024;
	char *buffer = NULL, *path, *arguments;
	int status, i;
	char *argv[1024];
	struct stat st;

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
				execv(path, argv);
			else
				wait(&status);
		}
		printf("$ ");
	}
	free(buffer);
	return (0);
}
