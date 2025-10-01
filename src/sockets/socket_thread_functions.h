#pragma once

#include <pthread.h>

typedef struct SocketThreadWorker
{
    pthread_t thread_value;
} SocketThreadWorkerType;

typedef struct SocketThreadWorkerVariable
{
    int socket;
    int thread_pool_index;
    SocketThreadWorkerType *socket_thread_worker_ptr;
} SocketThreadWorkerVariable_t;

typedef struct SocketThreadPool
{
    SocketThreadWorkerType *socket_thread_worker_ptr;
    unsigned int no_of_threads;
} SocketThreadPoolType;

void *hello_fun(void *thread_worker_var);

SocketThreadPoolType thread_pool_create(void);
