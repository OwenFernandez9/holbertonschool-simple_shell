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
char *find_path(char *file_name, char **av, char **env);
char *_getenv(const char *name, char **av, char **env);
#endif
