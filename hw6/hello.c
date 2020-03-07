/*
 * hello.c- Pthreads "hello, world" program
 */
#include "csapp.h"

 void *thread(void *vargp);
 int main(int argc, char **argv)
 {
	int n; //n peers
	if(argc<2) //if arg is not given default to creating one thread
	{
		printf("default value n = 1\n");
		n = 1;
	}
	else //otherwise set n to the arguement
	{
		n = atoi(argv[1]);
	}
	pthread_t tid[n]; //create a list of size n
	int i;
	for(i =0; i<n; i++) //create and join n pthreads
	{
		Pthread_create(&tid[i], NULL, thread, NULL);
		Pthread_join(tid[i], NULL);
	}
	exit(0);
 }

 void *thread(void *vargp)
 {
	printf("Hello, world!\n");
	return NULL;
}
	
