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
int handle_arg(char *arguments[1024], char **av, char **env, size_t count);
char **get_flags(char *buffer, char *arguments[], char **env);
int invalid_path(const char *str);
void handle_error(char *av, char *command, size_t count);
#endif
