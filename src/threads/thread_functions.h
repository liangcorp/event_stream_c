#pragma once

#include <pthread.h>

typedef struct ThreadWorker
{
    pthread_t thread_value;
} ThreadWorker_t;

typedef struct ThreadWorkerVariable
{
    int socket;
    int thread_pool_index;
    ThreadWorker_t *socket_thread_worker_ptr;
} ThreadWorkerVariable_t;

typedef struct ThreadPool
{
    ThreadWorker_t *socket_thread_worker_ptr;
    unsigned int no_of_threads;
} ThreadPool_t;

void *hello_fun(void *thread_worker_var);
ThreadPool_t thread_pool_create(void);
