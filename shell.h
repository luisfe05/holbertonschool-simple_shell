#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* the environment variables */
extern char **environ;

/* main.c */
void prompt(void);
void handle_line(char *line, ssize_t nread, char **argv, int *command_count);

/* execute.c */
void child_process(char **args, char *program_name, int command_count);
void execute_command(char *line, char *program_name, int command_count);

/* tokenize.c */
int count_tokens(char *line, char *delim);
char **tokenize(char *line);

#endif
