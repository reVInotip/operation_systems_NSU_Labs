#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("pid: %d\n", getpid());
    sleep(10);
    printf("a\n");
    
    int *data[200];
    for (int i = 0; i < 200; ++i) {
        data[i] = (int*)malloc(1024 * 1000);
        sleep(1);
    }

    for (int i = 0; i < 200; ++i) {
        free(data[i]);
    }
    return 0;
}