#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
void forkoff(char *command, char *arguments[])
{
	int pid = fork();
	
	if (pid < 0)
	{
		fprintf(2, "Cannot fork off new process\n");
		exit(1);
	}
	else if (pid == 0)
	{
		exec(command, arguments);
	}
	wait(&pid);
	exit(0);
}
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(2, "Too few arguments\n");
		exit(1);
	}
	char stdInput[MAXARG];
	read(0, stdInput, MAXARG);	

	int i = 0;
	int j = 0;
	char *p = stdInput;
	stdInput[strlen(stdInput)] = '\0';
	char *start = p;
	char *newArgs[MAXARG];
	for (i = 2; i < argc; i++)
	{
		newArgs[j++] =  argv[i];
	}
	while (*p != '\0')
	{
		if (*p == ' ' || *p == '\n')
		{
			newArgs[j] = (char *)malloc(p - start + 1);
			*p = '\0';
			memmove(newArgs[j], start, p - start + 1);
			j++;
			start = p + 1;

			if (*p == '\n')
			{
				forkoff(argv[1], newArgs);
				for (int k = argc - 2;k < j; k++)
				{
					free(newArgs[k]);
				}
				j = argc - 2;
			}

			p++;
		}
	
	}


	exit(0);
}
