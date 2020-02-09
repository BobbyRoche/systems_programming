#include <stdio.h> 
#include <stdlib.h> 
//the problem here was an int bit overflow. num was set at the minimum for int due to 1<<31 shift
int main () 
 {
  char * buf;
  int num;
  num = 1 << 31-1;
  buf = malloc(num) ;
  fgets (buf, 1024, stdin) ;
  printf ("%s\n", buf) ;
  return(1);
 }
