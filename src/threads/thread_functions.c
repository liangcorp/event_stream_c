#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "result_data_type.h"
#include "socket_functions.h"
#include "thread_functions.h"

#define MAX_MESSAGE_SIZE 250

void *hello_fun(void *thread_worker_var)
{
    ThreadWorkerVariable_t thread_variable = *(ThreadWorkerVariable_t *)thread_worker_var;

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
    snprintf(outgoing_message, MAX_MESSAGE_SIZE, "Hello %d", thread_variable.socket);

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
    close(thread_variable.socket);

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
Result_t get_worker_thread(SocketThreadWorker_t *st_worker, void *socket)
{
    ThreadWorkerVariable_t thread_worker_var;

    thread_worker_var.socket = *(int *)socket;

    Result_t get_work_thread_result;
    memset(get_work_thread_result.error_message, '\0', MAX_ERROR_MESSAGE_SIZE);

    pthread_create(&(st_worker->thread_value), NULL, hello_fun, &thread_worker_var);
    get_work_thread_result.result_enum = Ok;
    return get_work_thread_result;

    get_work_thread_result.result_enum = Error;
    snprintf(get_work_thread_result.error_message, MAX_ERROR_MESSAGE_SIZE,
             "GET WORKER THREAD ERROR <%s:%d>: %s", __FILE__, __LINE__,
             "thread pool is full");
    return get_work_thread_result;
}
