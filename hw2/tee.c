#include "csapp.h"
#include <getopt.h>
static int append_mode =0;

int main(int argc, char *argv[])
{
	char buf[128]; //set char buffer to 128 bytes
	size_t s; 
	char *file_mode; //used to track if we're appending or overrideing
	int i=1; //defaults to read the first commandarg
	FILE *file; 
	char c;
	while((c = getopt(argc, argv, "a"))!=-1) //checks if we are given the -a option
	{
		if(c == 'a')
		{
			append_mode=1; //if so we change the append mode to 1 signaling we are appending
			i=2; //changing i to 2 since argv[1] is -a the file will be the second arg
		}
		break;
	}
	
		
	if(argc>1)
	{
		FILE *pFile = fopen(argv[i], append_mode ? "a":"w");	//opens the file given with either the a or w depending on the option
		file = pFile; 
	}
		

while ((s = fread(&buf[0], 1, sizeof(buf), stdin)) > 0) //reads from stdin
{
	fwrite(&buf[0], 1, s, stdout); //prints to stdout and to the specified file
	if(argc>1)
		fwrite(&buf[0], 1, s, file);	
}
if(argc>1)
	fclose(file);
	

return 0;
}
