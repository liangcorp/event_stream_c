#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>

#include "http_messages.h"
#include "thread_functions.h"

#define MAX_MESSAGE_SIZE 500
#define MAX_THREAD_NUMBER 1

void *hello_fun(void *thread_worker_void_ptr)
{
    ThreadWorkerVariable_t thread_variable = *(ThreadWorkerVariable_t *)thread_worker_void_ptr;

    printf("DEBUG %d\n", thread_variable.socket);
    int thread_pool_index = thread_variable.thread_pool_index;

    char incoming_message[MAX_MESSAGE_SIZE];
    memset(incoming_message, '\0', sizeof(incoming_message));

    /* Receiving a message from the client */
    if (recv(thread_variable.socket, incoming_message, MAX_MESSAGE_SIZE, 0) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET recv ERROR <%s:%d>: %s\n", __FILE__, __LINE__,
                strerror(errsv));
        exit(1);
    }

    printf("Incoming message: %s\n", incoming_message);

    char outgoing_message[MAX_MESSAGE_SIZE] = {'\0'};
    snprintf(outgoing_message, MAX_MESSAGE_SIZE, return_http_200_default);

    /* send some data */
    if (send(thread_variable.socket, outgoing_message, MAX_MESSAGE_SIZE, 0) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET send ERROR <%s:%d>: %s", __FILE__, __LINE__,
                strerror(errsv));
        exit(1);
    }
    printf("sent hello back\n");

    printf("free up thread %d\n", thread_pool_index);
    thread_variable.socket_thread_worker_ptr->thread_value = 0;
    close(thread_variable.socket);

    return 0;
}

/* create a pool of threads with value of 0 */
ThreadPool_t thread_pool_create(void)
{
    // const unsigned int MAX_THREAD_NUMBER = sysconf(_SC_NPROCESSORS_ONLN) + 1;

    static ThreadWorker_t socket_thread_worker[MAX_THREAD_NUMBER];

    for (int i = 0; i < MAX_THREAD_NUMBER; i++)
    {
        socket_thread_worker[i].thread_value = 0;
    }

    ThreadPool_t st_pool;
    st_pool.socket_thread_worker_ptr = socket_thread_worker;
    st_pool.no_of_threads = MAX_THREAD_NUMBER;

    return st_pool;
}
