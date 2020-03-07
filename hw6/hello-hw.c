 #include <pthread.h>
#include "csapp.h"
 #define NUM_THREADS 8
   char *messages[NUM_THREADS];

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//struct used for passing arguements to thread routine
	struct p_args
	{
		int sum;
		int taskid;
		char *msg;
	};
   void *PrintHello(void *threadarg)
    {
		//mutex lock for sunchronized threading
	 // pthread_mutex_lock(&mutex); 
	  //cast arg back to the struct and store it
	  struct p_args *p = (struct p_args *) threadarg;
	 	
     int taskid, sum;
     char *hello_msg;
	  //set the vars to the vars in the struct
     sum = p->sum;
	  hello_msg = p->msg;
	  taskid = p->taskid;
     printf("Thread %d %s Sum=%d\n", taskid, hello_msg, sum);
	  //unlock mutex
	//  pthread_mutex_unlock(&mutex);
     pthread_exit(NULL);
    }
   int main(int argc, char *argv[])
    {
     pthread_t threads[NUM_THREADS];
	  //one struct per thread
	  struct p_args pargs[NUM_THREADS];
	  
     int rc, t, sum;
     sum=0;
     messages[0] = "Hello-0";
     messages[1] = "Hello-1";
     messages[2] = "Hello-2";
     messages[3] = "Hello-3";
     messages[4] = "Hello-4";
     messages[5] = "Hello-5";
     messages[6] = "Hello-6";
     messages[7] = "Hello-7";
     for(t = 0; t < NUM_THREADS; t++)
      { 
       sum = sum + t;
		 //set each var in the struct for each iteration
		 pargs[t].sum = sum;
		 pargs[t].msg = messages[t];
		 pargs[t].taskid = t;
       printf("Creating thread %d\n", t);
		 //create the thread with the args
       pthread_create(&threads[t], NULL, PrintHello, (void *) &pargs[t]);
		 //join so the threads print with their corresponding strings
		 pthread_join(threads[t],NULL);
      }
     pthread_exit(NULL);
    }
