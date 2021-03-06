/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include "stack.hpp"
#include "queue.hpp"

#define PORT "3490" // the port users will be connecting to

#define BACKLOG 10 // how many pending connections queue will hold

stack *head = NULL;
pqueue qHead = NULL;


// printPrompt();

void sigchld_handler(int s) {
    // (void)s; // quiet unused variable warning

    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while (waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

void *myThread(void *new_fd) {
    char clientMsg[1024] = {0};
    int numbytes;
    int clientSock = *(int *) new_fd;

    while (1) {
        // while (strcmp(clientMsg, "EXIT")) {
        char str[1024];
        char output[1024] = "OUTPUT: ";
        char babi[1024] = "";
        bzero(str, 1024);

        if (!strcmp("EXIT", clientMsg)) {
            printf("client disconnected\n");
            close(clientSock);
            break;
        }
        if (strncmp(clientMsg, "PUSH", 4) == 0) {
            uint j = 0;
            for (uint i = 5; i < strlen(clientMsg); i++, j++) {
                str[j] = clientMsg[i];
            }
            str[j] = '\0';
            push(str, &head);
            send(clientSock, "Pushed to stack successfully!", 29, 0);
            fflush(stdout);
            // printPrompt();
        } else if (!strcmp("POP", clientMsg)) {
            pop(&head);
            send(clientSock, "Popped from stack successfully!", 31, 0);
            fflush(stdout);
            // printPrompt();
        } else if (!strcmp("TOP", clientMsg)) {
            strcat(output, peek(&head));
            send(clientSock, output, strlen(output), 0);
            memset(output, '0', sizeof(output));
            strcpy(output, "OUTPUT: ");
            fflush(stdout);
            // printPrompt();
        } else if (strncmp(clientMsg, "PRINT", 5) == 0) {
            displayStack(&head);
            send(clientSock, "", 1, 0);
            fflush(stdout);
            // printPrompt();
        } else if (strncmp(clientMsg, "ENQUEUE", 7) == 0) {
            uint j = 0;
            for (uint i = 8; i < strlen(clientMsg); i++, j++) {
                babi[j] = clientMsg[i];
            }
            babi[j] = '\0';
            enqueue(qHead, babi);
            send(clientSock, "Enqueued to queue successfully!", 31, 0);
            fflush(stdout);
        } else if (strncmp(clientMsg, "DEQUEUE", 7) == 0) {
            dequeue(qHead);
            send(clientSock, "Dequeued from queue successfully!", 33, 0);
            fflush(stdout);
        } else if (strncmp(clientMsg, "TOPQ", 4) == 0) {
            strcat(output, topRear(qHead));
            send(clientSock, output, strlen(output), 0);
            memset(output, '0', sizeof(output));
            strcpy(output, "OUTPUT: ");
            fflush(stdout);
        }
        bzero(clientMsg, 1024);
        if ((numbytes = recv(clientSock, clientMsg, BUF_SIZE - 1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if (!numbytes) {
            printf("client disconnected\n");
            close(clientSock);
            return NULL;
        }

        clientMsg[numbytes] = '\0';
        printf("server received: %s\n", clientMsg);

    }

    return NULL;
}

int main(void) {
    int sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    initQ(&qHead);
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    // pthread_t tid;
    pthread_t tid[3];

    int i = 0;
    while (1) { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr((struct sockaddr *) &their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        // if (pthread_create(&tid, NULL, &myThread, &new_fd) != 0)
        if (pthread_create(&tid[i++], NULL, &myThread, &new_fd) != 0) {
            printf("Failed to create thread\n");
        }
    }

    return 0;
}
