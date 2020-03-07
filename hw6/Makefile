CC	= gcc
CFLAGS = -Wall -I .. 
LDLIBS = -lpthread


all: hello hello-hw

hello-hw: hello-hw.c csapp.o
	$(CC) -o hello-hw hello-hw.c csapp.o $(LDFLAGS) $(LDLIBS)

hello: hello.c csapp.o
	$(CC) -o hello hello.c csapp.o $(LDFLAGS) $(LDLIBS)


csapp.o: csapp.c
	$(CC) -O2 -c csapp.c


