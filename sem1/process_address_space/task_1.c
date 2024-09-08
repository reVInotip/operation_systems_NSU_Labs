#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int global_init = 1;
int global_not_init;
const int global_const;

int* harmfulFunction() {
    int a = 5;
    return &a;
}

void weirdFunction() {
    /*char *buffer = (char*)malloc(100);
    //buffer = "Hello world\n";
    printf("buffer before free: %s\n", buffer);
    free(buffer);
    printf("buffer after free: %s\n", buffer);*/

    char *newBuffer = (char*)malloc(13);
    //newBuffer = "Hello world\n";
    newBuffer[0] = 'H';
    printf("new buffer before shortening: %s\n", newBuffer);
    newBuffer += 6;
    free(newBuffer);
    printf("new buffer after shortening: %s\n", newBuffer);
}

int main() {
    //1
    int local;
    static int static_local;
    const int const_local;

    printf("local: %p\nstatic_local: %p\nconst_local: %p\n", &local, &static_local, &const_local);
    printf("global_init: %p\nglobal_not_init: %p\nglobal_const: %p\n", &global_init, &global_not_init, &global_const);
    printf("pid %d\n", getpid());

    //2
    int *badAddress = harmfulFunction();
    printf("bad local address%p\n", badAddress);

    //3
    //weirdFunction();

    //4
    setenv("ABOBA", "aboba", 0);
    char *env = getenv("ABOBA");
    printf("env before change: %s\n", env);
    setenv("ABOBA", "shrek", 1);
    env = getenv("ABOBA");
    printf("env after change: %s\n", env);
    
    while(1) {
        //do nothing
    }
    return 0;
}