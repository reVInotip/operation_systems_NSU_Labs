.data

msg:
    .ascii "Hello world!\n"
    len = . - msg

.text
    .global _start

_start:
# sys_wrtie
    movq $4, %rax
    movq $1, %rbx
    movq $msg, %rcx
    movq $len, %rdx
    int $0x80

# exit
    movq $60, %rax
    xorq %rdi, %rdi
    syscall
