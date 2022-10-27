#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS   8

void *thread_f(void *);

int main(int argc, char *argv[])
{
    int rc = 0;

    // Explicitly creating a "joinable" thread.
    pthread_attr_t attr;
    rc = pthread_attr_init(&attr);
    rc = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_t thread[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; i++)
        rc = pthread_create(
            &thread[i],     // Output the handle to the created thread.
            &attr,          // The attributes of the thread.
            thread_f,       // The function to be executed by the thread.
            (void *) i      // The argument to be passed to the function.
        );
    
    rc = pthread_attr_destroy(&attr);

    void *status;
    for (long i = 0; i < NUM_THREADS; i++)
        rc = pthread_join(thread[i], &status);

    // The thread that calls pthread_exit halts, in this case,
    // the main thread, but the other threads continue to run.
    // It does not block.
    pthread_exit(NULL);

    return 0;
}

void *thread_f(void *arg)
{
    printf("Hello from thread %ld.\n", (long) arg);
    pthread_exit(NULL);
    return NULL;
}
