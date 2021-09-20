#include "user/user.h"
#include "kernel/types.h"

int main( int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(2, "Usage: sleep integer...\n");
    	exit(1);
	}
	int time;
	time = atoi(argv[1]);
	printf("nothing happens for a little while\n");
	sleep(time);
	exit(0);
}
