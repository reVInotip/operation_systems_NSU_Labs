#include <stdio.h>
#include "static_lib/hello_from_static_lib.h"

int main(void) {
    printf("Hello world (now with static library!)\n");
    HelloFromStaticLib();
    return 0;
}