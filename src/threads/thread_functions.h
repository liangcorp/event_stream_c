#pragma once

#include <pthread.h>


typedef struct SocketThreadWorker
{
    pthread_t thread_value;
} SocketThreadWorker_t;

typedef struct ThreadWorkerVariable
{
    int socket;
    int thread_pool_index;
    SocketThreadWorker_t *socket_thread_worker_ptr;
} ThreadWorkerVariable_t;

typedef struct SocketThreadPool
{
    SocketThreadWorker_t *socket_thread_worker;
    unsigned int no_of_threads;
} SocketThreadPool_t;

void *hello_fun(void *thread_worker_var);
SocketThreadPool_t socket_thread_pool_create(void);
