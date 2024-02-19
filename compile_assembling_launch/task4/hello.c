#include <stdio.h>
#include <dlfcn.h>
#include "dynamic_runtime_lib/hello_from_dynamic_runtime_lib.h"

int main(void) {
    void* handler = dlopen("/home/grisha/Projects/operation_systems_NSU_Labs/compile_assembling_launch/task4/dynamic_runtime_lib/libruntimedynamic.so", RTLD_LAZY);
    if (!handler) {
        fprintf(stderr, "%s", dlerror());
        return 1;
    }
    printf("Hello world (now with dynamic runtime library!)\n");
    char* (*result)() = dlsym(handler, "HelloFromDynamicRuntimeLib");
    printf("%s\n", (*result)());
    dlclose(handler);
    return 0;
}