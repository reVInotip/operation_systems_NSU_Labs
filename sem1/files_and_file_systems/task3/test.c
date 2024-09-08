#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main() {
    printf("pid: %d\n", getpid());
    
    char *data_heap = (char*)malloc(1024 * 1000);
    char *data_map = mmap(NULL, 1024*100, PROT_READ | PROT_EXEC | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    char data_stack[100];
    memset(data_stack, 0, 100);
    memset(data_heap, 0, 1024*1000);

    sleep(100);

    free(data_heap);
    munmap(data_map, 1024*100);
    return 0;
}