#include <stdlib.h>

//the problem in this file was that x[10] was being initialized when only memory was allocated up to x[9]
//the memory leak occured because x was never freed

void f ()
 {
  int *x;
  x = (int *)malloc(10*sizeof(int));
  x[9] = 0;
  free(x);
 }

int main ()
 {
  f();
  return 0;
 }
