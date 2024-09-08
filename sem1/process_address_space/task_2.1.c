#include <unistd.h>
#include <stdio.h>

void myFunction() {
    char data[4096];
    myFunction();
}

int main() {
    printf("pid: %d\n", getpid());
    sleep(5);
    printf("a\n");
    myFunction();
    return 0;
}