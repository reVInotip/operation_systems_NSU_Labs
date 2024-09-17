#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    if (signum == 2) // SIGINT
    {
        printf("SIGINT\n");
        exit(0);
    }
}

void *mythread_1(void *arg) {
    int err;
	printf("mythread1 [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

    sigset_t sigset;
    err = sigaddset(&sigset, 2); // SIGINT
    if (err) {
	    printf("main: sigaddset() failed: %s\n", strerror(err));
		return NULL;
	}

    err = pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);
    if (err) {
        printf("main: pthread_sigmask() failed: %s\n", strerror(errno));
		return NULL;
    }

    /*err = sigemptyset(&sigset);
    if (err) {
	    printf("main: sigemptyset() failed: %s\n", strerror(err));
		return NULL;
	}

    struct sigaction sigact = {
        .sa_flags = 0,
        .sa_mask = sigset,
        .sa_restorer = NULL,
        .sa_handler = signal_handler,
        .sa_sigaction = NULL
    };

    err = sigaction(2, &sigact, NULL);
    if (err) {
	    printf("main: sigaction() failed: %s\n", strerror(errno));
		return NULL;
	}*/

    signal(2, signal_handler);

    printf("mythread1: New signal handler initialize!\n");

    sleep(100);

	return NULL;
}

void *mythread_2(void *arg) {
    int err;
	printf("mythread2 [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

    sigset_t sigset;
    err = sigaddset(&sigset, 3); // SIGINT
    if (err) {
	    printf("main: sigaddset() failed: %s\n", strerror(err));
		return NULL;
	}

    int signum = 0;
    while (signum != 3) // SIGQUIT
    {
        printf("mythread2: waiting for quit (SIGQUIT=3) signal!\n");

        err = sigwait(&sigset, &signum);
        if (err) {
            printf("mythread2: sigwait() failed: %s\n", strerror(err));
            return NULL;
        }

        printf("mythread2: recive signal %d\n", signum);
    }

    printf("SIGQUIT\n");
    exit(0);

	return NULL;
}

int main() {
    int err;

    sigset_t sigset;
    err = sigfillset(&sigset);
    if (err) {
	    printf("main: sigfillset() failed: %s\n", strerror(err));
		return -1;
	}

    err = pthread_sigmask(SIG_BLOCK, &sigset, NULL);
    if (err) {
        printf("main: sigfillset() failed: %s\n", strerror(errno));
		return -1;
    }

	pthread_t tid[2];
    pthread_attr_t attr[2];
    void *(*thread_func[2])(void*) = {mythread_1, mythread_2};
    for (int i = 0; i < 2; ++i) {
        err = pthread_attr_init(&attr[i]);
        if (err) {
            printf("main: pthread_attr_init() failed: %s\n", strerror(err));
            return -1;
        }

        err = pthread_attr_setdetachstate(&attr[i], PTHREAD_CREATE_DETACHED);
        if (err) {
            printf("main: pthread_attr_setdetachstate() failed: %s\n", strerror(err));
            return -1;
        }

        printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

        err = pthread_create(&tid[i], &attr[i], thread_func[i], NULL);
        if (err) {
            printf("main: pthread_create() failed: %s\n", strerror(err));
            return -1;
        }

        err = pthread_attr_destroy(&attr[i]);
        if (err)
        {
            printf("main: pthread_attr_destroy() failed: %s\n", strerror(err));
            return -1;
        }
    }

    sleep(100);

	pthread_exit(NULL);
	return 0;
}