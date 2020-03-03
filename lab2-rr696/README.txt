Robert Roche
Lab2

The program functionality is mostly explained in comments

The program first compairs files in dir a to files in dir b, if it finds a matching file it overrites the older one with the more recently
modified file. If it does not find a match for a give file from a, it copies file a to dir b. After this completes, it checks to see
if any files in dir b exist in a and if they do not they are deleted.

To compile type the make command. To run type ./lab2 <dir a> <dir b>

Sources I used to learn some syntax:
Deleting a file: https://www.geeksforgeeks.org/c-program-delete-file/
stat: https://linux.die.net/man/2/stat

