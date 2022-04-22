# Multi-Threaded Stack  
> Made by [Nerya Bigon](https://github.com/nerya0001) and [Ori Howard](https://github.com/OriHoward)

The goal in this assignment is to understand how the OS implements malloc and free on multi-threaded system and how we implement mutexes.  

## Tests  
In order to test our system we've used [doctest](https://github.com/doctest/doctest), which allows us to easily test each component.  
we've also used threads to make sure the mutex works as expected.

### How To Run  
click [here]() to run the tests.  

1. download this repository
2. open a terminal window in the main folder and run the following comand:

```
make all
```
3. then run the server using the following command:

```
./server
```

4. and then run clients by opennig a separate terminal and runnig the following command:

```
./client host
```
* for example:  
```
./client 127.0.0.1
```    

this server is also compatible with telnet - the command is:  

```
telnet remotehostname 3490
```  

5. to run the test run in a separate terminal the following command:  
```
./test
```  



