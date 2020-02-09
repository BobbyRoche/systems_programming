Robert Roche
Hw3

Simply type 'make' command to make the h3 executable

then type: 

./h3 'find' 'replace' 'prefix'

My program works as expected with the tests I ran. 

code explanation:

The program takes args for 'find' 'replace' and 'prefix'
If we find the 'find' variable, we mark our flag to skip the prefix and we replace accordingly.

If we do not find 'find' we do not mark the flag and move on to check if we have our 'prefix'
If we do we prepend accordingly, if not we skip prepend and leave the file unchanged.