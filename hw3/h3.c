#include "csapp.h"
#include <dirent.h>



int main(int argc, char *argv[])
{
	int MAXSIZE = 128;
	size_t s;
	struct dirent *dp;
	char *find, *replace, *prefix; //arguement strings
	char *tempstr; //temo string used later
	FILE *old, *tempf,*pref; //old or original file, temp file is used as a temp file for replacing, pref is used for prepending
	DIR *dd; //directory descriptor
	char *dir; //directory name
	char line[MAXSIZE]; //string used to get lines in file
	int is_found = 0; //flag to show if find is found
	int pre_found = 0; //flag to show if prefix is found
	dd = opendir("."); //setting directory pointer to current directory
	dir = "."; //set directory name to current dir
	find = argv[1]; //sets find to arg1
	replace = argv[2]; //sets replace to arg2
	prefix = argv[3]; //sets prefix to arg3
	tempstr = "!!!+++!!++";


	char *file_name;
	while((dp = readdir(dd)) != NULL) //while there's still files in the current dir
	{
		int count =0; //reset count to 0 every time we look at a new file
		is_found = 0; //reset flags to 0
		pre_found =0;
		file_name = dp->d_name; //set the file name to the name of the current file
		int length = strlen(file_name); //set length to the length of the current file
		if (strncmp(dp->d_name + length - 4, ".txt", 4) == 0) //check the last 4 to see if it is a .txt file
		{
			old = fopen(file_name, "r+"); //if it is open the original file as a read
			tempf = fopen("h3tempfile","w+"); //open temp file
			while(fgets(line, MAXSIZE, old)!=NULL) //while there are lines left
			{
				char *position;
				char temp[MAXSIZE]; //set temp line and position
				int index = 0; //current index
				int len; //length of old word

				len = strlen(find);

				while((position = strstr(line, find))!=NULL)//while there's still occurences of the word
				{
					is_found = 1; //word was found
					count+=1; 
					strcpy(temp, line); //copy the found word into temp
					index = position - line; //get the index of the current word
					line[index] = '\0'; //add null char to the string
					strcat(line, replace); //cat the string with the replace
					strcat(line, temp + index + len); //cat the rest
				}
				if(is_found==1) //if we did find 
				{
					fputs(line,tempf); //add the line to the tempfile
				}	
			}
			if(is_found ==1 )
			{
				printf("%s was replaced %d times by %s in %s\n",find,count,replace,file_name); //print info on this operations
			}
			if(is_found==0) //if we did not find find
			{
				fseek(old,0,SEEK_SET); //reset pointers
				fseek(tempf,0,SEEK_SET);
				while(fgets(line, MAXSIZE, old)!=NULL) //same as before but this time we're searching for the prefix
				{
					char *position;
					char temp[MAXSIZE];
					int index = 0;
					int len;
					len = strlen(prefix);
					while((position = strstr(line, prefix))!=NULL) //if we find the prefix we replace it with our nonsense string so there is no mixups
					{
						pre_found = 1;
						strcpy(temp, line);
						index = position - line;
						line[index] = '\0';
						strcat(line, tempstr);
						strcat(line, temp + index + len);
					}
					fputs(line,tempf);
				
				}
				if(pre_found==1) //if we find our prefix, we do the find and replace, but this time with the string specified in the assignment. Otherwise this code is the same as previous loop
				{ 
					pref = fopen("h3prefile","w+");
					char *new_str = malloc(strlen(find)+strlen(prefix)+1);
					strcat(new_str,find);
					strcat(new_str,prefix);
					fseek(tempf,0,SEEK_SET);
					while(fgets(line, MAXSIZE,tempf)!=NULL)
						{
							char *position;
							char temp[MAXSIZE];
							int index = 0;
							int len;

							len = strlen(tempstr);

							while((position = strstr(line, tempstr))!=NULL)
							{
								count+=1;
								strcpy(temp, line);
								index = position - line;
								line[index] = '\0';
								strcat(line, new_str);
								strcat(line, temp + index + len);
							}
							fputs(line,pref);
				
						}
						if(pre_found == 1)
						{
							printf("%s was appended to %s %d times in %s\n",find,prefix,count,file_name); //print statistics 
						}
				}
			
				}
				if((is_found == 1) || (pre_found == 1)) //if we are using a tempfile
				{
					remove(file_name); //get rid of old file
					
					if(is_found==1) //if we did a find and replace we rename temp file to the original file
					{
						rename("h3tempfile",file_name);
					}
					else if(pre_found ==1) //if we did a prefix we prefix temp file to original
					{
						rename("h3prefile",file_name);
						remove("h3tempfile");
					}
				}
				else
					remove("h3tempfile");//cleanup
		

			fclose(old);//close og file and other files when necessary
			fclose(tempf);
			if(pre_found==1)
			{
				fclose(pref);
			}
			
			}
		}
	
			return 0;

		}
		

