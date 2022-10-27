#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS   8

void *thread_f(void *);

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
int g_sum = 0;

int main(int argc, char *argv[])
{
    int rc = 0;
    
    // Mutex variable must be initialised before use.
    rc = pthread_mutex_init(&g_mutex, NULL);

    pthread_t thread[NUM_THREADS];
    int thread_num[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_num[i] = i;
        rc = pthread_create(&thread[i], NULL, thread_f, &thread_num[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        rc = pthread_join(thread[i], NULL);
    rc = pthread_mutex_destroy(&g_mutex);

    printf("Global sum: %d.\n", g_sum);

    pthread_exit(NULL);
    return 0;
}

void *thread_f(void *arg)
{
    int thread_num = *(int *) arg;

    // Critical region.
    // Lock the shared resource to eliminate risk of race condition.
    pthread_mutex_lock(&g_mutex);
        g_sum += thread_num;
    pthread_mutex_unlock(&g_mutex);

    pthread_exit(NULL);
    return NULL;
}
