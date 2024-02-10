#include <stdio.h>
#include <dlfcn.h>
#include "dynamic_runtime_lib/hello_from_dynamic_runtime_lib.h"

int main(void) {
    void* handler = dlopen("/home/grisha/Рабочий стол/НГУ/Бакалавриат/2 курс/operation_systems_NSU_Labs/compile_assembling_launch/task4/dynamic_runtime_lib/libruntimedynamic.so", RTLD_NOW);
    if (!handler) {
        fprintf(stderr, "%s", dlerror());
        return 1;
    }
    printf("Hello world (now with dynamic runtime library!)\n");
    void* result = dlsym(handler, "HelloFromDynamicRuntimeLib");
    char* error = dlerror();
    if (!error) {
        fprintf(stderr, "%s", error);
        return 1;
    }
    dlclose(handler);
    return 0;
}