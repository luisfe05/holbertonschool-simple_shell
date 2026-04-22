#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/*
 * environ is a global variable defined in libc.
 * It holds all environment variables (PATH, HOME, etc.)
 * We use 'extern' to tell the compiler it exists elsewhere.
 */
extern char **environ;

/* main.c */
void prompt(void);
void handle_line(char *line, ssize_t nread, char **argv, int *command_count);

/* execute.c */
void child_process(char **args, char *full_path,
		char *program_name, int command_count);
void execute_command(char *line, char *program_name, int command_count);

/* tokenize.c */
int count_tokens(char *line, char *delim);
char **tokenize(char *line);

/* path.c */
char *build_full_path(char *dir, char *command);
char *find_in_path(char *command);

/* _getenv.c */
char *_getenv(const char *name);

/* utils.c */
char *_strdup(char *str);

#endif
