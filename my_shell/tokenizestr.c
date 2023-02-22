#include "shell.h"

/**
 * tokenize_string: breaks down a string into tokens
 * Description - takes a string separates into tokens
 * determined by @TOKEN_DELIM
 * @str: string
 * Return - an array of string tokens
 */
char **tokenize_string(char *str)
{
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens)
    {
        fprintf(stderr, "hsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(str, TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                free(tokens_backup);
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
