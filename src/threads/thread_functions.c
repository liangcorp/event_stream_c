#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

#define MAX_MESSAGE_SIZE 250

void *hello_fun(void *socket)
{
    char incoming_message[MAX_MESSAGE_SIZE];
    memset(incoming_message, '\0', sizeof(incoming_message));

    /* Receiving a message from the client */
    if (recv(*(int *)socket, incoming_message, MAX_MESSAGE_SIZE, 0) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET recv ERROR <%s:%d>: %s\n", __FILE__, __LINE__,
                strerror(errsv));
        exit(1);
    }

    printf("Incoming message: %s\n", incoming_message);

    char outgoing_message[MAX_MESSAGE_SIZE] = {'\0'};
    snprintf(outgoing_message, MAX_MESSAGE_SIZE, "Hello %d", *(int *)socket);

    /* send some data */
    if (send(*(int *)socket, outgoing_message, MAX_MESSAGE_SIZE, 0) < 0)
    {
        int errsv = errno;
        fprintf(stderr, "SOCKET send ERROR <%s:%d>: %s", __FILE__, __LINE__,
                strerror(errsv));
        exit(1);
    }
    printf("sent hello back\n");

    return 0;
}

/* create a pool of threads with value of 0 */
SocketThreadPool_t socket_thread_pool_create(void)
{
    const unsigned int MAX_THREAD_NUMBER = sysconf(_SC_NPROCESSORS_ONLN) + 1;

    SocketThreadWorker_t st_worker[MAX_MESSAGE_SIZE];

    for (int i = 0; i < MAX_THREAD_NUMBER; i++)
    {
        st_worker[i].thread_value = 0;
    }

    SocketThreadPool_t st_pool;
    st_pool.st_worker = st_worker;
    st_pool.no_of_threads = MAX_THREAD_NUMBER;

    return st_pool;
}

/* return an existing or create and return a new pthread */
Result_t get_worker_thread(SocketThreadPool_t *st_pool, void *socket)
{
    Result_t get_work_thread_result;
    memset(get_work_thread_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    for (int i = 0; i < st_pool->no_of_threads; i++)
    {
        if (st_pool->st_worker[i].thread_value == 0)
        {
            pthread_create(&(st_pool->st_worker[i].thread_value), NULL, hello_fun,
                           socket);
            get_work_thread_result.result_enum = Ok;
            return get_work_thread_result;
        }
    }

    get_work_thread_result.result_enum = Error;
    snprintf(get_work_thread_result.error_message, MAX_ERROR_MESSAGE_SIZE,
             "GET WORKER THREAD ERROR <%s:%d>: %s", __FILE__, __LINE__,
             "thread pool is full");
    return get_work_thread_result;
}
