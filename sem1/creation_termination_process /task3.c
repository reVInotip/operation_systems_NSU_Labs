#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int globalVar = 15;


void func2(int a) {
    if (a == 10) {
        return;
    }
    char arr[12] = "Hello world";
    printf("%s\n", arr);
    printf("Return address: %p\n", __builtin_return_address(0));
    printf("Counter address: %p\n", &a);
    ++a;
    func2(a);
}

int func(void *args) {
    printf("Child process PID: %d\n", getpid());
    func2(0);
    return 0;
}

int main() {
    int f = open("./a.txt", O_RDWR | O_CREAT);
    if (f == -1) {
        printf("fail1\n");
        exit(5);
    }
    
    void *stack = mmap(0, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_STACK, f, 0);
    if (stack == MAP_FAILED) {
        printf("fail2\n");
        exit(5);
    }

    printf("Process PID: %d\n", getpid());
    int pid = clone(func, ((char*)stack) + 4096, CLONE_VM, NULL);
    printf("Child process created!\n");
    msync(stack, 4096, MS_SYNC);
    close(f);
}