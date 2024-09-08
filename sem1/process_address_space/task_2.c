#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    printf("pid: %d\n", getpid());
    sleep(1);
    execve("/home/grisha/Projects/operation_systems_NSU_Labs/process_address_space/executable2", NULL, NULL);
    printf("Hello world\n");
    return 0;
}