#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern char **environ;
char *_getenv(const char *name)
{
	char * env_val;
	char * env_var;
	int cmp;

	env_var = strdup(*environ);
	env_var = strtok(env_var, "=");
	env_val = strtok(NULL, "=");
	cmp = strcmp(name, env_var);
	while (cmp != 0 && environ != NULL)
	{
		environ++;
		if (environ != NULL)
		{
			env_var = strdup(*environ);
			env_var = strdup(*environ);
			env_val = strtok(NULL, "=");
			cmp = strcmp(name, env_var);
		}
	}
	free(env_val);
	if (env_var != NULL)
		return (env_var);
	return (NULL);
}
int main(void)
{
        _getenv("PATH");
}
