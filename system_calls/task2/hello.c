#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int countWriteenBytes = write(1, "Hello world!", 12);
    if (countWriteenBytes != 12) {
        fprintf(stderr, "Something went wrong!, ret=%d: %s", countWriteenBytes, strerror(errno));
    }
    return 0;
}