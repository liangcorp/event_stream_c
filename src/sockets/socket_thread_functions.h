#pragma once

#include <pthread.h>

typedef struct SocketThreadWorker
{
    pthread_t thread_value;
} SocketThreadWorker_t;

typedef struct SocketThreadWorkerVariable
{
    int socket;
    int thread_pool_index;
    SocketThreadWorker_t *socket_thread_worker_ptr;
} SocketThreadWorkerVariable_t;

typedef struct SocketThreadPool
{
    SocketThreadWorker_t *socket_thread_worker_ptr;
    unsigned int no_of_threads;
} SocketThreadPool_t;

void *hello_fun(void *thread_worker_var);
SocketThreadPool_t thread_pool_create(void);
