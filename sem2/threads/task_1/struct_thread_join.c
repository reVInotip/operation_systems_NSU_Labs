#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

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
	return NULL;
}

int main() {
	pthread_t tid;
	int err;
    struct my_struct args = {.a = 5, .b = "hello world"};

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

	err = pthread_create(&tid, NULL, mythread, &args);
	if (err) {
	    printf("main: pthread_create() failed: %s\n", strerror(err));
		return -1;
	}

    err = pthread_join(tid, NULL);
    if (err) {
        printf("main: pthread_join() failed: %s\n", strerror(err));
		return -1;
    }

	pthread_exit(NULL);
	return 0;
}