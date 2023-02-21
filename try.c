#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 80

int main(void)
{
    char *args[MAX_LINE / 2 + 1];
    char command[MAX_LINE];
    int should_run = 1;

    while (should_run)
    {
        printf(" $(osh)> ");
        fflush(stdout);

        fgets(command, MAX_LINE, stdin);
        command[strlen(command) - 1] = '\0'; // remove trailing newline

        // tokenize the command into arguments
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
        }
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // child process
                if (execvp(args[0], args) == -1)
                {
                    perror("execvp");
                    exit(1);
                }
            }
            else if (pid == -1)
            {
                perror("fork");
            }
            else
            {
                // parent process
                wait(NULL);
            }
        }
    }

    return 0;
}
