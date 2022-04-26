# Multi-Threaded Stack  
> Made by [Nerya Bigon](https://github.com/nerya0001) and [Ori Howard](https://github.com/OriHoward)

The goal in this assignment is to understand how the OS implements malloc and free on multi-threaded system, and how to implement mutexes.  

## Tests  
In order to test our system we've used [doctest](https://github.com/doctest/doctest), which allows us to easily test each component.  
we've also used threads to make sure the mutex works as expected.

### How To Run  
1. Download this repository
2. Open a terminal window in the main folder and run the following comand:

```
make all
```
3. Then run the server using the following command:

```
./server
```

4. And then run clients by opennig a separate terminals and runnig the following command:

```
./client host
```
* For example:  
```
./client 127.0.0.1
```    

This server is also compatible with telnet - the command is:  

```
telnet remotehostname 3490
```  

5. To run the test, run in a separate terminal the following command:  
```
./test
```  
### Bonus
In the bonus we were asked to implement the double ended queue.
The queue will support the following commands:
`ENQUEUE <text>` - insert to the tail (same as PUSH).  
`DEQUEUE <text>` - remove the tail (same as POP).  
we have also added a new command:  
`TOPQ` - Same as peek

#### Probable assumptions:
We assumed the queue is a separate object from the stack.  
All the client have access to the stack and to the queue.  
The stack and the queue are safe threaded (Mutex).





