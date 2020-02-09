Robert Roche

CS283 Lab1

Make (notes other than comments in the files):
	-CLFAGS in makefile5 is commented out, not sure if this would cause problems (I assume it would)
	-running one runs each program built in makefile1 starting from main going 1-3 and outputs from each file, they seem to work properly
	-makefile2 does the same but uses variables rather than individually doing each file
	-One percieved mistake is makefiles 3 and 4 do not remove the executable only the object files
	-ext.h defines the functions
	-do not see mistakes in the source files
	-

GDB: 
The email from the TA's said recapping our gdb interactions was okay. I did a lot of fiddling to learn gdb so my output was a mess,
however I did save it if it is wanted please let me know.
	etox
	-I started by compiling my program using the -g command to allow for debugging.
	-I then set breakpoints starting at each function (b command)
	-I then ran the program, when it hit a break point I used s to step into the functions
	-I then used n to move on to the next line each and used f to check where I was in the program
	-I consistently used print or p to check various variable values during and at the end of each function
	-as I went through I noticed main and getvalue seemed fine
	-at the end of factorial I realized the return value was 0, which was not the value of k!.
	-after looking at the code I found that fact was set to 0 when it needed to be 1. (0*anything=0)
	-after the fix the code functioned as expected

	g1
	-I started by compiling to be debugged
	-After my initial run I realized the issue was happening in the loop so I set a breakpoint there
	-I typed 'hello' as my input
	-after stepping into the loop I used 'n' to go line by line printing 'c' at each step
	-I noticed upon loop iterations the character was not changing. 
	-Upon taking a look at the code I realized there were no curly braces, so only the if statement was being executed
	and the print statement. The pointer was never being moved to the next character.
	-To fix this I put curly braces around the necessary code, but then I noticed the file would print each letter on a new line
	-To fix this I took new-line out of the print statement and put an if statement at the beginning of the while loop to print 
	a new-line only if that was the character. It was not completely clear if the function should terminate after one line
	of text was entered so I left it as is from there. The user can keep entering text to be echoed until they hit ctrl-D 
	signaling the end of the file. If it were desired to only take one line, you would simply replace the while loop statement to 
	terminate the loop if the character were '\n'.

	g2
	-I began by compiling the program for debugging
	-I set a break at line 8 as I knew that is where things besides defining variables began
	-I hit n after num was initialized and after checking the value I saw it was -2147483648
	-I knew this meant this line of code was most likely the issue
	-After doing some research I found 1<<32 causes an overflow
	-To fix this I simply added 1<<32-1
	-The program now works as expected

valgrind:
I have the Valgrind output as well but its very messy, I desribe below what I recieved from using valgrind but can send the raw output if
necessary
	v00
	-error message states 'Invalid write of size 4' and provides line numbers
	-Also 'Address 0x522d068 is 0 bytes after a block of size 40 alloc'd'
	-We also have a memory leak.
	-To fix the error we simply must change the array assignment a[10] to a[9]. We only allocated memory for 10 places in the array
	and a[10] would be the 11th element.
	-To fix the memory leak I simply freed x at the end of the function

	v05
	-error given by valgrind states 'Conditional jump depends on uninitialized value(s)' at line 6
	-x is not initialized in the program, and is used in an if statement.
	-the fix is to simply initialize x which I did in this isntance to 0

	v06
	-same error as v05, but this time the line number is 6 in a function called at line 15
	-upon tracing the error I found y was uninitialized and used as a function arguement which x was set to
	-to fix this I simply intialized y.


	 