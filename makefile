CC=g++
AR=ar
FLAGS=-Wall -g

all: main server

main: main.o libutil.a server.o client.o 
	$(CC) $(FLAGS) main.o libutil.a -o main

server: server.o
	$(CC) $(FLAGS) server.o -o server -lpthread

libutil.a: util.o
	$(AR) -rcs libutil.a util.o

server.o: server.cpp util.hpp
	$(CC) $(FLAGS) -c server.cpp -o server.o

client.o: client.cpp util.hpp
	$(CC) $(FLAGS) -c client.cpp

main.o: main.cpp util.hpp
	$(CC) $(FLAGS) -c main.cpp

util.o: util.cpp util.hpp
	$(CC) $(FLAGS) -c util.cpp	



.PHONY: clean all

clean:
	rm -f *.o *.a main server client



