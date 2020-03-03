#include "csapp.h"
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc<3)
	{
		printf("Improper number of arguments, please provide the paths of 2 directories\n");
		exit(1);
	}
	//declaration and initialization of necessary dat
	struct dirent *dp1, *dp2;
	struct stat st1, st2;
	bool current_file_found = false;
	DIR *dd1, *dd2;
	FILE *fp1, *fp2;
	FILE *fptr, *fptr2;
	char *src, *dst;
	char c,cc,cc2;
	time_t a_modt, b_modt;
	src = (argv[1]);
	dst = (argv[2]);
	dd1 = opendir(src);
	dd2 = opendir(dst);
	char *aname, *bname;
	//while loop for problem 1 and 3
	//copy files in dir a to dir b if file a not in dir b
	while((dp1=readdir(dd1)) != NULL)  //readdir
	{
		aname = dp1->d_name;
		//iterates over the files in dir b to see if it contains the file from dir a
		while ((dp2=readdir(dd2)) != NULL) //read dir
		{
			bname = dp2->d_name;
			//if file name a = file name b
			if(strcmp(aname,bname)==0) 
			{
				//set flag to true
				current_file_found = true;

			}
			else
			{
				current_file_found = false;
			}
		//printf("%s\n", dp2->d_name);
		
		//if the file match was found check last time stamp whichever was most recent is copied to the other
			if((current_file_found) && (strcmp(aname,".")!=0) && (strcmp(aname,"..")!=0) && (strcmp(bname,".")!=0) &&(strcmp(bname,"..")!=0))
			{
				char apath[256];
				apath[0]='\0';
				strcat(apath,src);
				strcat(apath,"/");
				strcat(apath,aname); //construct a string with the path of the new file being written to
				char bpath[256]; //construct the path of the file being read from.
				bpath[0]='\0';
				strcat(bpath,dst);
				strcat(bpath,"/");
				strcat(bpath,bname);

				//setup stat struct with each directory
				stat(apath,&st1);
				stat(bpath,&st2);
				//get the last modified time
				a_modt = st1.st_mtime;
				b_modt = st2.st_mtime;

				//if b is newer than a (in terms of mod) write b to a
				if(difftime(a_modt, b_modt) < 0)
				{
					printf("Second dir version of %s has been modified more recently.Copying contents to first dir.\n",bname);
				//	if(access(bpath, R_OK)!=0)
				//	{
				//		printf("%s permissions will not allow read!\n",bpath);
				//		continue;
				//	}
				//	else if(access(apath, W_OK)!=0)
				//	{
				//		printf("%s permissions will not allow write!\n",apath);
				//		continue;
				//	}
					
					fptr = fopen(bpath,"r");
					fptr2 = fopen(apath, "w");
					cc = fgetc(fptr);
					while(cc!=EOF)
					{
						fputc(cc, fptr2);
						cc=fgetc(fptr);
					}
					
				}
				//if a is newer than b write a to b
				else if(difftime(a_modt, b_modt)>0)
				{
					printf("First dir version of %s has been modified more recently. Copying contents to second dir.\n",aname);
				//	if(access(apath, R_OK)!=0)
				//	{
				//		printf("%s permissions will not allow read!\n",apath);
				//		break;
				//	}
				//	else if(access(bpath, W_OK)!=0)
				//	{
				//		printf("%s permissions will not allow write!\n",bpath);
				//		break;
				//	}
					fptr = fopen(apath,"r");
					fptr2 = fopen(bpath, "w");
					cc2 = fgetc(fptr);
					while(cc2!=EOF)
					{
						fputc(cc2, fptr2);
						cc2=fgetc(fptr);
					}
	
				}
				fclose(fptr);
				fclose(fptr2);
			}
		}
		//if no match was found add file from dir a to b
			//if the file match was found check last time stamp whichever was most recent is copied to the other
		if((!(current_file_found)) && (strcmp(aname,".")!=0) && (strcmp(aname,"..")!=0) && (strcmp(bname,".")!=0) &&(strcmp(bname,"..")!=0))
		{
			char wname[256];
			wname[0]='\0';
			strcat(wname,dst);
			strcat(wname,"/");
			strcat(wname,aname); //construct a string with the path of the new file being written to
			char rname[256]; //construct the path of the file being read from.
			rname[0]='\0';
			strcat(rname,src);
			strcat(rname,"/");
			strcat(rname,aname);
			//open the files
			fp1 = fopen(rname,"r");
			fp2 = fopen(wname,"w");
			//copy fp1 to fp2
			c = fgetc(fp1);
			while(c!=EOF)
			{
				fputc(c, fp2);
				c=fgetc(fp1);
			}
			printf("Copied file from %s to %s\n",rname,wname);
			fclose(fp1);
			fclose(fp2);
			
		}
		else
		{
			current_file_found = false;
		}

		//reset pointer in dir b
		rewinddir(dd2);
	}
	rewinddir(dd1);
	rewinddir(dd2);
	current_file_found = false;
	//while loop for problem 2
	while((dp2=readdir(dd2)) != NULL)  //readdir
	{
		bname = dp2->d_name;
		//iterates over the files in dir a to see if it contains the file from dir b
		while ((dp1=readdir(dd1)) != NULL) //read dir
		{
			aname = dp1->d_name;
			//if file name a = file name b
		//	printf("Comp %s to %s",bname,aname);
			if(strcmp(aname,bname)==0)
			{
				//set flag to true
				current_file_found = true;
			}
		//printf("%s\n", dp2->d_name);
		}
		//if the file was not found, create and copy the file to dir b
		if(!(current_file_found))
		{	
			char remove_f[256];
			remove_f[0]='\0';
			strcat(remove_f,dst);
			strcat(remove_f,"/");
			strcat(remove_f,bname);
			if(remove(remove_f)==0)
			{
				printf("Removed file at %s\n",remove_f);
			}
		}
		else
		{
			current_file_found = false;
		}
		rewinddir(dd1);
	}
	
	return 0;
}
