#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* extern variable that holds the environment variables */
extern char **environ;

/* main.c */
void prompt(void);

/* execute.c */
void execute_command(char *line, char *program_name, int command_count);

#endif
