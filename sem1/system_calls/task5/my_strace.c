#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdlib.h>

void parent(int child_pid) {
    int status = 0;
    struct user_regs_struct state;
    int err = wait(&status);
    if (err < 0) {
        printf("wait() error: %s\n", strerror(errno));
        exit(1);
    }

    ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
    if (err < 0) {
        printf("ptrace() error: %s\n", strerror(errno));
        exit(1);
    }


    while (!WIFEXITED(status)) {
        ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
        if (err < 0) {
            printf("ptrace() error: %s\n", strerror(errno));
            exit(1);
        }

        wait(&status);
        if (err < 0) {
            printf("wait() error: %s\n", strerror(errno));
            exit(1);
        }

        if (WIFSTOPPED(status) && (WSTOPSIG(status) & 0x80)) {
            ptrace(PTRACE_GETREGS, child_pid, 0, &state);
            if (err < 0) {
                printf("ptrace() error: %s\n", strerror(errno));
                exit(1);
            }

            printf("SYSCALL %lld at %08llx\n", state.orig_rax, state.rip);

            ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
            if (err < 0) {
                printf("ptrace() error: %s\n", strerror(errno));
                exit(1);
            }

            wait(&status);
            if (err < 0) {
                printf("wait() error: %s\n", strerror(errno));
                exit(1);
            }
        }
    }
}

void child() {
    int err = ptrace(PTRACE_TRACEME, 0, 0, 0);
    if (err < 0) {
        printf("ptrace() error: %s\n", strerror(errno));
        exit(2);
    }

    err = execl("/bin/echo", "/bin/echo", "Hello world!", NULL);
    if (err < 0) {
        printf("exec() error: %s\n", strerror(errno));
        exit(2);
    }
}

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork() error: %s\n", strerror(errno));
        exit(1);
    } else if (pid != 0) {
        parent(pid);
    } else {
        child();
    }
}