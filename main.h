#ifndef SH_H
#define SH_H
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
char *find_path(char *file_name, char **av, char **env, size_t count);
char *_getenv(const char *name, char **env);
int handle_arg(char *arguments[], char **av, char **env, size_t count);
char **get_flags(char *buffer, char *arguments[], char **env, int status);
int invalid_path(const char *str);
char *get_cwd(char *file_name, char *path, char **env);
void handle_error(char *av, char *command, size_t count);
int handle_builtin(char *in, char **env, int st, char *arg[], char *buff);
#endif
