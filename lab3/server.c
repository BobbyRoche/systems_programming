/* 
*some code borrowed from echoserveri.c - An iterative echo server 
*/ 
#include "csapp.h"

int main(int argc, char **argv) 
 {

	int listenfd, connfd, port, clientlen,s;
	size_t n;
	struct sockaddr_in clientaddr;
	struct hostent *hp;
	char *haddrp;
	char client_msg[1028],path[1028];
	char buf[512],*GET;
	char *fname;
	char *root;
	char *http;
	rio_t rio;
	if (argc != 2) 
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
   }
	port = atoi(argv[1]);

	listenfd = Open_listenfd(port);
	//setup path from root dir
	root = getenv("PWD");
	//while partially borrowed from ICE/csapp
	while (1) 
   {
		clientlen = sizeof(clientaddr);
    	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
	 	hp = Gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
	 	sizeof(clientaddr.sin_addr.s_addr),AF_INET);
	 	haddrp = inet_ntoa(clientaddr.sin_addr);
	 	printf("Server connected to %s (%s) \n", hp->h_name, haddrp);
	//	memset((void*)client_msg, (int)'\0', 99999);
		//recieve the message from the client
		s = recv(connfd, client_msg, 99999, 0);
		printf("Request made: %s",client_msg);
		GET = strtok(client_msg, " \t\n");
		//if it is a GET request construct the proper path
		if(strncmp(GET, "GET\0",4)==0)
		{
			//get the given file name
			fname = strtok(NULL," \t");
			//check to make sure HTTP 1.0/1.1 is included
			http = strtok(NULL, " \t\n");
			if(strncmp(http, "HTTP/1.0",8)!=0 && strncmp(http,"HTTP/1.1",8)!=0)
			{
				Rio_writen(connfd, "No http included. Bad Request", 30);
			}
			//copy the root to the path
			strcpy(path,root);
			//add the desired file to the path
			strcat(path, fname);

			//open the file at the given root.
	 		int fd;
			if((fd=open(path,O_RDONLY))<0)
			{
				Rio_writen(connfd, "404 Error\nFile Not Found",26);
			}
			printf("Server sending data back to client...\n");
  			Rio_readinitb(&rio, fd);
  			while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0) 
  			{
   				Rio_writen(connfd, buf, n);
			}
			printf("Transfer complete, closing socket...\n");
 			
		}
		}
		shutdown(connfd, SHUT_RDWR);
    	Close(connfd);
   
  exit(0);
 }
