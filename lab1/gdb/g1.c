#include <ctype.h> 
#include <stdio.h> 
//the first problem was no curley braces around the while loop was only causing the if statement to exectue infinitely
//in addition, '\n' in the print statement was causing one character to print per line
//fixes were to add braces and to add an if to only go to a newline if there was a newline char

int main () 
 {
  char c;
  c = fgetc (stdin);
  while (c != EOF) 
{
  if(c == '\n')
	printf("\n");

  if (isalnum (c) ) 
   printf ("%c", c);
 	c = fgetc (stdin);
}
  return(1);
 }
