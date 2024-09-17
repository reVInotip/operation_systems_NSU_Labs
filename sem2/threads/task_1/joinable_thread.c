#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void *mythread(void *arg) {
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());
    sleep(3);
    printf("mythread exit!\n");

	return (void *) 42;
}

void *mythread_string(void *arg) {
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());
    sleep(3);
    char *retval = (char *)malloc(sizeof(char) * 13);
    strcpy(retval, "hello world");
    printf("mythread exit!\n");

	return (void *) retval;
}

int main() {
	pthread_t tid;
    pthread_attr_t attr;
	int err;

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

    err = pthread_attr_init(&attr);
    if (err) {
        printf("main: pthread_attr_init() failed: %s\n", strerror(err));
		return -1;
    }

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    if (err) {
        printf("main: pthread_attr_setdetachstate() failed: %s\n", strerror(err));
		return -1;
    }

	err = pthread_create(&tid, &attr, mythread_string, NULL);
	if (err) {
	    printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}

    err = pthread_attr_destroy(&attr);
    if (err)
    {
        printf("main: pthread_attr_destroy() failed: %s\n", strerror(err));
		return -1;
    }

    void *retval = 0;
    err = pthread_join(tid, &retval);
    if (err) {
        printf("main: pthread_join() failed: %s\n", strerror(err));
		return -1;
    }

    printf("Thread exit and return value: %s\n", ((char *) retval));
    free(retval);

	pthread_exit(NULL);
	return 0;
}
