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
}
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(2, "Too few arguments\n");
		exit(1);
	}
	int m = 0;
	int i = 0;
	int j = 0;

	char stdInput[MAXARG][100];
	char *newArgs[MAXARG];
	for (i = 1; i < argc; i++)
	{
		newArgs[j++] =  argv[i];
	}
	while(read(0, stdInput[m], MAXARG))
	{
	//	printf("%s,size:%d, m:%d\n", stdInput[m],strlen(stdInput[m]), m);
	//	m++;
		char *p = stdInput[m];
		char *start = p;
		m++;
		while (*p != '\0')
		{
		if (*p == ' ' || *p == '\n')
		{
			newArgs[j] = (char *)malloc(p - start + 1);
			memmove(newArgs[j], start, p - start + 1);
			newArgs[j][strlen(newArgs[j]) - 1] = '\0';
			j++;
			start = p + 1;

			if (*p == '\n')
			{
				/*for (int k = 0; k < j;k++)
				{
					printf("%s ", newArgs[k]);
				}
				printf("\n");*/
				forkoff(argv[1], newArgs);
				for (int k = argc - 1;k < j; k++)
				{
					free(newArgs[k]);
				}
				j = argc - 1;
			}

		}
		p++;
	
		}

	}

	exit(0);
}
