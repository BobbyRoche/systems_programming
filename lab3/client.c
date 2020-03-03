
/* some code borrowed from echoclient.c*/
#include "csapp.h"

int main(int argc, char **argv) 
 {
  int clientfd, port; //declare the client file descriptor and variable for the port number
  char *host,*filename, buf[MAXLINE]; //host URL name and the name of the file we want, as well as the buffer
  struct hostent *he; //host entry struct
  struct sockaddr_in addr; //socket address
  rio_t rio; 
  char body_buf[2056];
  int count;
  int t=0;
//if given the incorrect number of arguments, show which arguments we are looking for
  if (argc != 4) 
   {
    fprintf(stderr, "usage: %s <host> <port> <file>\n", argv[0]);
    exit(0);
   }
  host = argv[1];			//first arg is stored as the host name
  port = atoi(argv[2]); //second arg is stored as the port, converted to int
  filename = argv[3];   //third arg is stored as the name of the file
  clientfd=Open_clientfd(host,port);
  //printf("%s, %d, %s\n\n",host,port,filename);	//testing to make sure arguements are read in properly

  if((he = gethostbyname(host))==NULL)	//setup the host entry struct with the proper name
	{											   //if there's an issue with gethostbyname we print an error and exit
		fprintf(stderr,"Error *gethostbyname*\n");
		exit(1);
	}
 
	//setting up sockaddr_in
	addr.sin_family = AF_INET; 
	addr.sin_port = htons(port);
	addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(addr.sin_zero), 8);
	//connect to the socket 
	connect(clientfd,(struct sockaddr *)&addr, sizeof(struct sockaddr));
	//create the header string
	char req[512];
	snprintf(req,256,"GET /%s HTTP/1.1\r\nHost: %s\r\n\r\n",filename,host);
	//send the http request to the server
	send(clientfd,req,strlen(req),0);
	//intialize rio read
	Rio_readinitb(&rio, clientfd);
	//read each line once we get to the end of the header, break
	while (Rio_readlineb(&rio,buf,MAXLINE)>0) 
	{
		if(strstr(buf,"Content-Length:"))
		{
			char *num=strrchr(buf,' ');
			if(num && *(num+1))
			{
				char* n=num+1;
			//	n[strlen(n)-1]='\0';
				count = atoi(n);
				printf("%s",buf);
//				Rio_readlineb(&rio,buf,MAXLINE);
//				printf("%d",count);
			}
//			printf("Found content length %d\n",byte_count);
			break;

		}
		//attempt at breaking at \r\n but it would not work
		if(strstr(buf,"\r\n"))
		{
//			printf("Reached end of header.\n");			
		}
		//print header lines
		printf("%s",buf);


    //Rio_writen(clientfd, buf, strlen(buf));
    //Rio_readlineb(&rio, buf, MAXLINE);
	}
//	after header, read the length of the "Content-Length"
// add one for null terminator
	rio_readnb(&rio,body_buf,(size_t)(count+1));
	printf("%s\n",body_buf);

	Close(clientfd);
	exit(0);
 }
