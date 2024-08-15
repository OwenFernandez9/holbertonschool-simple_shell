#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char **environ;
char *_getenv(const char *name)
{
	char * env_val, * env_var, ** env, * env_check;
	
	for (env = environ; env != NULL; env++)
	{
		env_check = *env;
		env_var = strtok(env_check, "=");
		env_val = strtok(NULL, "=");
		if (strcmp(name, env_var) == 0)
		{
			printf("%s\n", env_val);
			return (env_val);
		}
	}
	return (NULL);
}
int main(void)
{
        _getenv("PATH");
}
