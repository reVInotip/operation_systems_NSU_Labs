#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int globalVar = 15;

int main() {
    int localVar = 6;
    printf("Process PID: %d\n", getpid());
    printf("Local var: %d, address: %p\nGlobal var: %d, address: %p\n", localVar, &localVar, globalVar, &globalVar);
    int pid = fork();
    if (pid == -1) {
        printf("Fork error");
    } else if (pid == 0) {
        printf("Child process PID: %d, parent process PID: %d\n", getpid(), getppid());
        printf("(In child process) Local var: %d, address: %p\n(In child process) Global var: %d, address: %p\n", localVar, &localVar, globalVar, &globalVar);
        globalVar = 9;
        localVar = 2;
        printf("(In child process) Apdated local var: %d, address: %p\n(In child process) Apdated global var: %d, address: %p\n", localVar, &localVar, globalVar, &globalVar);
        exit(5);
    } else {
        printf("(In parent process) Local var: %d, address: %p\n(In parent process) Global var: %d, address: %p\n", localVar, &localVar, globalVar, &globalVar);
        sleep(30); 
        int wstatus;
        waitpid(pid, &wstatus, WUNTRACED);
        if (__WCOREDUMP(wstatus)) {
            printf("Child process core dumped\n");
        } else if (WIFSIGNALED(wstatus)) {
            printf("%d\n", WTERMSIG(wstatus));
        } else if (WIFEXITED(wstatus)) {
            printf("Exit status: %d", WEXITSTATUS(wstatus));
        }
    }
}