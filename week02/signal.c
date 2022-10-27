#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_THREADS   8

void *thread_f(void *);

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;
int g_threads_done = 0;

int main(int argc, char *argv[])
{
    int rc = 0;

    pthread_t thread[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        rc = pthread_create(&thread[i], NULL, thread_f, NULL);

    pthread_mutex_lock(&g_mutex);
    while (g_threads_done < NUM_THREADS)
        rc = pthread_cond_wait(&g_cond, &g_mutex);
    pthread_mutex_unlock(&g_mutex);

    rc = pthread_mutex_destroy(&g_mutex);
    rc = pthread_cond_destroy(&g_cond);

    pthread_exit(NULL);
    return 0;
}

void *thread_f(void *unused)
{   
    sleep(1);

    pthread_mutex_lock(&g_mutex);
        g_threads_done++;
    pthread_cond_signal(&g_cond);
    pthread_mutex_unlock(&g_mutex);

    pthread_exit(NULL);
    return NULL;
}
