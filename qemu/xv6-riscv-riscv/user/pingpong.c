#include "kernel/types.h"
#include "user/user.h"

int main()
{
	char buffer = 'c';	 //one byte buffer
	int fd1[2]; //parent to child pipe
	int fd2[2];	//child to parent pipe
	int length = sizeof(buffer);

	pipe(fd1);
	pipe(fd2);
	int pid = fork();
	if (pid > 0)		//parent process
	{
		close(fd1[0]);
		if (write(fd1[1], &buffer, length) != length)
		{
			fprintf(2,"parent write error\n");
			exit(1);
		}
		close(fd1[1]);

		close(fd2[1]);
		close(0);
		dup(fd2[0]);
		close(fd2[0]);
		if (read(0, &buffer, length) != length)
		{
			fprintf(2,"parent read error\n");
			exit(1);
		}
		
		printf("%d: received pong\n",getpid());
		close(0);
		wait(&pid);
		exit(0);
	}
	else	//child process
	{
		close(fd1[1]);
		close(0);
		dup(fd1[0]);
		close(fd1[0]);
		if (read(0, &buffer, length) != length)
		{
			fprintf(2,"child read error\n");
			exit(1);
		}
		printf("%d: received ping\n",getpid());
		close(0);

		close(fd2[0]);
		if (write(fd2[1],&buffer, length) != length)
		{
			fprintf(2,"child write error\n");
			exit(1);
		}
		close(fd2[1]);

		exit(0);

	}
}
