#include "shell.h"
#include <sys/wait.h>

#define CHILDPROCESS 0

int execute_cmd(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == CHILDPROCESS)
    {
        // Child process
        if (execvp(args[0], args) == -1)
        {
            perror("command error: "); // COULDN'T EXECUTE ARGUMENT
        }
        printf("Are we still in the child process?\n");
        exit(EXIT_FAILURE);
    }
    else if (pid == -1)
    {
        // Error forking
        perror("fork error: ");
    }
    else
    {
        // Parent process
        wait(&status);
    }

    return 1;
}
