#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Description: a simple c shell program with builtin operations
 */
int main(int argc, char **argv)
{
	int shell_status = 1;
	char *buffer = NULL;
	char *args[] = {};
	size_t len = 0;
	ssize_t nread;

	while (shell_status)
	{
		/* READ INPUT
			-x get a stream of strings
			-x print it back
		*/
		printf("($) ");
		nread = getline(&buffer, &len, stdin);
		buffer[strlen(buffer) - 1] = '\0'; // remove trailing newline

		if (nread == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		printf("You entered: %s\n", buffer);

		/* PARSE INPUT with tokenization */
		char *token = strtok(buffer, " ");
		int i = 0;
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		int length = sizeof(args) / sizeof(args[0]);
		i = 0;
		for (i; i < length; i++)
		{
			printf(">>>> %s\n", args[i]);
		}
		printf("%d", length);

		if (strcmp(args[0], "exit") == 0)
		{
			shell_status = 0;
		}

		/*
			EXECUTE COMMAND
			- fork()
			- execve()
		*/
		pid_t pid = fork();
		if (pid == 0)
		{
			// execute within child process
			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
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

	free(buffer);
	return (0);
}
