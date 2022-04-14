CC=g++
AR=ar
FLAGS=-Wall -g

all: server client

server: libutil.a server.o 
	$(CC) $(FLAGS) server.o libutil.a -o server -lpthread -ltbb
client: client.o
	$(CC) $(FLAGS) client.o -o client

libutil.a: util.o queue.o
	$(AR) -rcs libutil.a util.o queue.o

server.o: server.cpp util.hpp queue.hpp
	$(CC) $(FLAGS) -c server.cpp -o server.o
client.o: client.cpp 
	$(CC) $(FLAGS) -c client.cpp
util.o: util.cpp util.hpp
	$(CC) $(FLAGS) -c util.cpp
queue.o: queue.cpp queue.hpp
	$(CC) $(FLAGS) -c queue.cpp


.PHONY: clean all

clean:
	rm -f *.o *.a server client



