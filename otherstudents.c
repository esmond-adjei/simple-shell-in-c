#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *command = NULL;
    size_t len;
    char *stkn;

    while (1)
    {
        printf("($) ");
        getline(&command, &len, stdin);

        stkn = strtok(command, "\n");
        char *arr[] = {stkn, NULL};
        execve(arr[0], arr, NULL);
    }
    free(command);
    return (0);
}