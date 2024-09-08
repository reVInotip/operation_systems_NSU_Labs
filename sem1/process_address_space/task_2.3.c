#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>

void goodbye() {
    printf("Goodbye\n");
    exit(3);
}

int main() {
    printf("pid: %d\n", getpid());
    sleep(10);
    printf("a\n");
    
    int *data = (int*)mmap(NULL, 4096, PROT_NONE, MAP_ANONYMOUS, 0, 0);

    signal(SIGSEGV, goodbye);
    //printf("%d\n", data[0]);
    data[0] = 5;

    return 0;
}