#include "main.h"
/**
 * _getenv - search the value of a variable
 * @name: name of the variable to check
 * Return: the values in the environ
 */
char *_getenv(const char *name, char **av,  char **enviroment)
{
	char *env_val, *env_var, **env, *env_dup;

	for (env = enviroment; *env != NULL; env++)
	{
		env_dup = strdup(*env);
		if (env_dup == NULL)
		{
			perror(av[0]);
			return (NULL);
		}
		env_var = strtok(env_dup, "=");
		env_val = strtok(NULL, "=");
		if (env_var && strcmp(name, env_var) == 0)
		{
			env_val = strdup(env_val);
			free(env_dup);
			return (env_val);
		}
		free(env_dup);
	}
	return (NULL);
}
/**
* find_path - checks if a file exist
* @file_name: name of the file to check
* Return: the route to the file
*/
char *find_path(char *file_name, char **av, char **env)
{
	char *path, *path_check, *path_dup, *absolute_route;
	struct stat st;
	int dup_size;

	path = _getenv("PATH", av, env);
	if (path == NULL)
	{
		perror(av[0]);
		return (NULL);
	}
	path_dup = strdup(path);
	free(path);
	path_check = strtok(path_dup, ":");
	while (path_check != NULL)
	{
		dup_size = (strlen(path_check) + strlen(file_name) + 2);
		absolute_route = malloc(dup_size * sizeof(char));
		if (absolute_route == NULL)
		{
			perror("Memory allocation failed");
			free(path_dup);
			return (NULL);
		}
		sprintf(absolute_route, "%s/%s", path_check, file_name);
		if (stat(absolute_route, &st) == 0)
		{
			free(path_dup);
			return (absolute_route);
		}
		path_check = strtok(NULL, ":");
		free(absolute_route);
	}
	perror(av[0]);
	free(path_dup);
	return (NULL);
}
