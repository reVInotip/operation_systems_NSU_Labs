#include <stdio.h>
#include "dynamic_lib/hello_from_dynamic_lib.h"

int main(void) {
    printf("Hello world (now with dynamic library!)\n");
    HelloFromDynamicLib();
    return 0;
}