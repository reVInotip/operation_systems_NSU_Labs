#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

struct my_struct
{
    int a;
    char *b;
};

void *mythread(void *arg) {
    struct my_struct *args = (struct my_struct *)arg;
	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());
    sleep(5);
    printf("mythread args: [%d %s]\n", args->a, args->b);
    free(args);
	return NULL;
}

int main() {
	pthread_t tid;
	int err;
    struct my_struct *args = (struct my_struct *) malloc(sizeof(struct my_struct));
    pthread_attr_t attr;

    args->a = 5;
    args->b = "hello_world";

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

    err = pthread_attr_init(&attr);
    if (err) {
        printf("main: pthread_attr_init() failed: %s\n", strerror(err));
		return -1;
    }

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err) {
        printf("main: pthread_attr_setdetachstate() failed: %s\n", strerror(err));
		return -1;
    }

	err = pthread_create(&tid, &attr, mythread, args);
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

	pthread_exit(NULL);
	return 0;
}