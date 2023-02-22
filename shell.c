#include <unistd.h>
#include "shell.h"

/**
 * Return: 0
 */
int main(void)
{
	size_t len;
	char *inputcmd = NULL;
	char **tkncommand;

	while (1)
	{
		/* read input command as string */
		printf("($) ");
		getline(&inputcmd, &len, stdin);

		/* tokenize the command string */
		tkncommand = tokenize_string(inputcmd);

		/* execute tokenized command and arguments*/
		execute_cmd(tkncommand);
	}
	free(inputcmd);
	free(tkncommand);
	return (0);
}
