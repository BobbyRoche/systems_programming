/*Figure 18*/
#include "csapp.h"

#define N 2

//signal handler
void handler(int sig)
{
	//prints the current process and the signal, and handles the signal
	printf("Process %d recieved signal %d, and was caught by the handler.\n",getpid(),sig);
	exit(0);

}

int main()
{
	int status, i;
	char *test = "abc";
//convert the pids to an array of 2 pids
	pid_t pid[N],pid2;

	/*Parent creates N children */
	for (i=0; i<N; i++)
		if((pid[i] = Fork()) == 0) //child
		{
			//install a seg fault handler in ONLY the first child
			if(i==0)
			{
				signal(SIGSEGV, handler);
			}
			//cause a segfault by writing to read only
			strcpy(test,"xyz"); 
			exit(100+i);
		}

			/*Parent reaps N children in no particular order */
			i=0;
			while ((pid2 = waitpid(pid[i++], &status, 0)) >0)
			{
				if (WIFEXITED(status))
					printf("child %d terminated normally with exit status=%d\n",pid2,WEXITSTATUS(status));
				//in the event of signal, we print the pid and the signal number
				else if(WIFSIGNALED(status))
				{
					char s[256];
					snprintf(s,256, "child %d terminated by signal %d",pid2, SIGSEGV); 
					psignal(WTERMSIG(status),s);
				}
				else
					printf("child %d terminated abnormally\n", pid2);
				}

	/* The normal termination is if there are no more children */
	if(errno != ECHILD)
		unix_error("waitpid error");
	
	exit(0);
}

