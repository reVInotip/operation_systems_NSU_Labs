#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

void *mythread(void *arg) {
    /*int err;

    err = pthread_detach(pthread_self());
    if (err) {
        printf("mythread: pthread_detach() failed: %s\n", strerror(err));
        return NULL;
    }*/

	printf("mythread [%d %ld %d]: Hello from mythread!\n", getpid(), pthread_self(), gettid());
	return NULL;
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

    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err) {
        printf("main: pthread_attr_setdetachstate() failed: %s\n", strerror(err));
		return -1;
    }

    while(1) {
        err = pthread_create(&tid, &attr, mythread, NULL);
        if (err) {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return -1;
        }
        sleep(5);
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
