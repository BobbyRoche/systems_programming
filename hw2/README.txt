Robert Roche

HW2

Answer for 10.6:
Output:
	fd2 = 4
Unix assigns descriptor 0 to stdin, 1 to stdout, and 2 to stderror. Using the open function will begin setting our descriptors at 3.
So fd1=3 and fd2=4 since fd was closed then reopened as another file it stays at fd4. 

The other files have makefiles specified for them

for 10.8: make -f makefile-fstatcheck

    10.10: make -f makefile-cpfile
    
    tee: make -f makefile-tee

notes on fstatcheck:
The only thing of note is 0 1, and 2 work as expected. If one wanted to check more file descriptors, you must 
creat a file and open it in the program. Based on permissions the program will behave appropriately.

notes on tee: 
tee can be run after using make by entering the command ./tee <option -a> <filename for output>
if not arguements are given this will only write to stdout. if only -a is given it will write to a file called -a since
no file is given to be created or appended to it creates a file called -a.
When entering input you can enter multiple lines of text. To stop entering text enter an EOF character, or ctrl-D,
then press ctrl-D again to write to the file and exit the program. So in total when you are done entering text, press ctrl-D twice.