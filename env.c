#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char **environ;
char *_getenv(const char *name)
{
	char *env_val, *env_var, **env, *env_check;
	
	for (env = environ; env != NULL; env++)
	{
		env_check = *env;
		env_var = strtok(env_check, "=");
		env_val = strtok(NULL, "=");
		if (strcmp(name, env_var) == 0)
			return (env_val);
	}
	return (NULL);
}
char *find_path(const char *file_name)
{
	char *path, *path_check, *absolute_route;

	path = _getenv("PATH");
	path_check = strtok(path, ":");
	strcat(path_check, "/");
	strcat(path_check, file_name);
	#ifdef DEBUG
        printf("%s\n", path_check);
        #endif
}
int main(void)
{
     	find_path("ls");
}
