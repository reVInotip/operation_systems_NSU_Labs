#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


void destroyer(void *arg) {
    printf("Here\n");
    free(arg);
}

void *mythread(void *arg) {
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

    while(1) {
        printf("Hello!\n");
    }

	return NULL;
}

void *mythread_malloc(void *arg) {
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

    char *string = (char *) malloc(sizeof(char) * 13);
    strcpy(string, "hello_world");

    pthread_cleanup_push(destroyer, string);

    while(1) {
        printf("%s\n", string);
    }

    pthread_cleanup_pop(1);

	return NULL;
}

void *mythread_counter(void *arg) {
    int counter = 0;
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

    while(1) {
        ++counter;
        //sleep(1);
    }

	return NULL;
}

int main() {
	pthread_t tid;
	int err;

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

	err = pthread_create(&tid, NULL, mythread_malloc, NULL);
	if (err) {
	    printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}
    //sleep(1);

    err = pthread_cancel(tid);
    if (err) {
	    printf("main: pthread_cancel() failed: %s\n", strerror(err));
		return -1;
	}

	pthread_exit(NULL);
	return 0;
}