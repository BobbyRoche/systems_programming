Robert Roche
HW5

The answer to question to 23 is in the q23 document. The answer to 24 is in q24.c and q24b.c and can be compiled with the make command 
creating the q24 and q24b exe. q24 answers the first question, and q24b answers the second. I answered both questions in one program and 
then split them apart. q24 creates two children, terminates them abnormally by causing a segfault from writing to read-only, then it
contains an extra conditional checking if a signal was sent. If it was we print the pid of the child and the signal that was sent using
psignal. For q24 b I added a conditional that checks if it is the first created child, if it is we add a signal handler. This child
will then handle the segfault signal and the other will not. 

The rest of the code was given from the textbook. 

I did both questions in one file, but a TA reccommended I split them into 2 files just in case.

References:

Showed you can violate read only with str copy. Found this looking for affectvie ways to violate read-only since many of my methods were
not causing seg-faults: 
https://stackoverflow.com/questions/1274626/access-violation-when-using-strcpy/27191999