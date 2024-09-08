#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main() {
    printf("Process PID: %d\n", getpid());
    int pid = fork();
    if (pid == -1) {
        printf("Fork error");
    } else if (pid == 0) {
        sleep(5); 
        printf("New process PID: %d\n", getppid());
    } else {
        exit(0);
    }
}