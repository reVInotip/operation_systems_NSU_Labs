#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main() {
    printf("pid: %d\n", getpid());
    sleep(10);
    printf("a\n");
    
    char *data = (char*)mmap(NULL, 4096 * 10, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    sleep(5);
    munmap(data + 4096 * 4, 4096 * 2);
    sleep(5);

    return 0;
}