CC	= gcc
CFLAGS = -Wall -I .. 
LDLIBS = -lpthread

all: client server

client: client.c csapp.o
	$(CC) -o client client.c csapp.o $(LDFLAGS) $(LDLIBS)

server: server.c csapp.o 
	$(CC) -o server server.c  csapp.o $(LDFLAGS) $(LDLIBS)
