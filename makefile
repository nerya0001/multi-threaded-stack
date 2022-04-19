CC=g++
AR=ar
FLAGS=-Wall -g

all: server client

server: libutil.a server.o 
	$(CC) $(FLAGS) server.o libutil.a -o server -lpthread -ltbb
client: client.o
	$(CC) $(FLAGS) client.o -o client

libutil.a: stack.o queue.o memory.o
	$(AR) -rcs libutil.a stack.o queue.o memory.o

server.o: server.cpp stack.hpp queue.hpp memory.hpp
	$(CC) $(FLAGS) -c server.cpp -o server.o

memory.o: memory.cpp
	$(CC) $(FLAGS) -c memory.cpp

client.o: client.cpp 
	$(CC) $(FLAGS) -c client.cpp

stack.o: stack.cpp stack.hpp
	$(CC) $(FLAGS) -c stack.cpp

queue.o: queue.cpp queue.hpp
	$(CC) $(FLAGS) -c queue.cpp


.PHONY: clean all

clean:
	rm -f *.o *.a server client



