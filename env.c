#include "main.h"
extern char **environ;
char *_getenv(const char *name)
{
	char *env_val, *env_var, **env, *env_dup;
	
	for (env = environ; env != NULL; env++)
	{
		env_dup = strdup(*env);
		if (env_dup == NULL)
		{
			perror("Memory allocation failed");
    			return NULL;
		}
		env_var = strtok(env_dup, "=");
		env_val = strtok(NULL, "=");
		if (strcmp(name, env_var) == 0)
		{
			env_val = strdup(env_val);
			free(env_dup);
			return (env_val);
		}
		free(env_dup);
	}
	return (NULL);
}
char *find_path(const char *file_name)
{
	char *path, *path_check, *path_dup, *absolute_route;
	struct stat st;

	path = _getenv("PATH");
	if (path == NULL)
	{
		perror("Failed to retrieve PATH");
		return NULL;
	}
	path_dup = strdup(path);
	if (path_dup == NULL)
	{
		perror("memory allocation failed");
		return NULL;
	}
	path_check = strtok(path_dup, ":");
	while (path_check != NULL)
	{
		absolute_route = malloc((strlen(path_check) + strlen(file_name) + 2) * sizeof(char));
		if (absolute_route == NULL)
		{
			perror("Memory allocation failed");
			free(path_dup);
			return NULL;
		}
		strcpy(absolute_route, path_check);
		strcat(absolute_route, "/");
		strcat(absolute_route, file_name);
		if (stat(absolute_route, &st) == 0)
		{
			free(path_dup);
			return (absolute_route);
		}
		free(absolute_route);
		path_check = strtok(NULL, ":");
	}
	perror("Command not found in PATH");
	free(path_dup);
	return (NULL);
}
