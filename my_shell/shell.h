#ifndef SHELL_H
#define SHELL_H

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **tokenize_string(char *line);
int execute_cmd(char **args);

#endif
