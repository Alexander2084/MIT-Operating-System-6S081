#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
int find(char *fileName, char *path)
{
	struct dirent de;
	int fd;
	struct stat st;
	int flag = 0;
	char buf[strlen(path) + DIRSIZ + 3];
	char *p;

	if ((fd = open(path, 0)) < 0)
	{
		fprintf(2, "cannot open\n");
		return -1;
	}
	

/*	if (fstat(fd, &st) < 0)
	{
		 fprintf(2, " cannot stat %s\n", path);
		 close(fd);
		 return -1;
	 }
*/	
	strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
	while(read(fd, &de, sizeof(de)) == sizeof(de))
	{
		if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
			continue;
		if (strlen(de.name) == 0)
			break;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if (stat(buf, &st) < 0)
		{
			printf("cannot stat %s\n", buf);
			return -1;	
		}
		if (st.type == 1)
		{
			flag = find(fileName, buf);
		}
			
		else if (st.type == 3)
			continue;
		else if (st.type == 2)
		{
			if (strcmp(de.name, fileName) == 0)
			{
				buf[strlen(buf)] = '\n';
				buf[strlen(buf) + 1] = '\0';
				write(1, buf, strlen(buf));
				flag = 1;
			}
		}
	}

	close(fd);
	return flag;
}
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(2,"Usage:find . <fileName>\n");
		exit(1);
	}
	char fileName[strlen(argv[2]) + 1];
	int val;
	char path[2] = ".";

	strcpy(fileName, argv[2]);
	val = find(fileName, path);
	if (val == 0)
	{
		printf("%s not found\n", fileName);
	}
	exit(0);
}


