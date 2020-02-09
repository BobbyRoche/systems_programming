#include "csapp.h"

int main(int argc, char **argv)
{
	struct stat stat;
	char *type, *readok;
	int fd; //add file descriptor
	//int fd1;
	//fd1 = Open("check.txt",O_RDONLY,0); //tester seeing if file descriptor 3 opens when you open a new file (it does)

	fd = atoi(argv[1]); //takes file descriptor number as cmdln arg and translates it to an int

	Fstat(fd, &stat); //use Fstat function as we used stat function but this time with file descriptor 
	if(S_ISREG(stat.st_mode))
		type = "regular";
	else if(S_ISDIR(stat.st_mode))
		type = "directory";
	else
		type = "other";
	if((stat.st_mode & S_IRUSR))
		readok = "yes";
	else
		readok = "no";
	printf("type: %s, read: %s\n",type, readok);
	exit(0);
	return 0;
}
