#pragma once

#include <pthread.h>

typedef struct ThreadWorkerVariable
{
    int socket;
    int thread_pool_index;
} ThreadWorkerVariable_t;

typedef struct SocketThreadWorker
{
    pthread_t thread_value;
} SocketThreadWorker_t;

typedef struct SocketThreadPool
{
    SocketThreadWorker_t *st_worker;
    unsigned int no_of_threads;
} SocketThreadPool_t;

void *hello_fun(void *thread_worker_var);
SocketThreadPool_t socket_thread_pool_create(void);
Result_t get_worker_thread(SocketThreadPool_t *st_pool, void *socket);
