#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    //setenv("A", "a", 0);
    char *env = getenv("A");
    printf("env before change: %s\n", env);
    setenv("A", "shrek", 1);
    env = getenv("A");
    printf("env after change: %s\n", env);
}