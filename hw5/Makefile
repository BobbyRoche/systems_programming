all: q24 q24b
q24: q24.c csapp.o
				gcc -O2 -pthread -g -o q24 q24.c csapp.o
q24b: q24b.c csapp.o
				gcc -O2 -pthread -g -o q24b q24b.c csapp.o
csapp.o: csapp.c
				gcc -O2 -c csapp.c
