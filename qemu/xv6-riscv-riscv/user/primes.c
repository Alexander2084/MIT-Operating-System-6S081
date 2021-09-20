#include "user/user.h"
#include "kernel/types.h"
#define RD 0
#define WT 1
void new_process()
{	
	int leftNum = 0;
	if (read(RD, &leftNum, sizeof(int)))
	{
		printf("prime %d\n", leftNum);
	}
	int nextNum = 0;
			
	if (read(RD , &nextNum, sizeof(int)) != 0)
	{
		int child_p[2];
		pipe(child_p);
		int pid = fork();
		if (pid > 0)
		{
			close(child_p[RD]);
			close(WT);
			dup(child_p[WT]);
			close(child_p[WT]);
			do
			{
				if (nextNum % leftNum)
				{
					write(WT, &nextNum, sizeof(int));
				}
			}while(read(RD, &nextNum, sizeof(int)));
			close(WT);
			wait(&pid);
		}
		else
		{
			close(child_p[WT]);
			close(RD);
			dup(child_p[RD]);
			close(child_p[RD]);
			new_process();
		}
	
	}
	exit(0);
}

int main(int argc, char *argv[])
{
	
	int i = 2;
	int parent_p[2];
	pipe(parent_p);
	int pid = fork();

	if (pid == 0)
	{
		close(parent_p[WT]);
		close(RD);
		dup(parent_p[RD]);
		close(parent_p[RD]);
		new_process();
	}
	else
	{
		close(parent_p[RD]);
		close(WT);
		dup(parent_p[WT]);
		close(parent_p[WT]);
		for (i = 2;i <= 35;i++)
		{
			write(WT,  &i, sizeof(int));
		}
		close(WT);
		wait(&pid);

	}
		
	
	exit(0);
}
