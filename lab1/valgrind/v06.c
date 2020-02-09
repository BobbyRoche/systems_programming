#include <stdio.h>
//the problem in this program was y was never being initialized and thus x was uninitialized and being used in an if

int foo (x)
int x;
 {
  if(x < 10)
   {
    printf("x is less than 10\n");
   }
 }

int main()
 {
  int y;
  y=2;
  foo(y);
 }
