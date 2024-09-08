	.file	"task3.c"
	.text
	.globl	globalVar
	.data
	.align 4
	.type	globalVar, @object
	.size	globalVar, 4
globalVar:
	.long	15
	.text
	.globl	func2
	.type	func2, @function
func2:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$10, -36(%rbp)
	je	.L5
	movabsq	$8031924123371070792, %rax
	movq	%rax, -20(%rbp)
	movl	$6581362, -12(%rbp)
	addl	$1, -36(%rbp)
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	func2
	jmp	.L1
.L5:
	nop
.L1:
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L4
	call	__stack_chk_fail@PLT
.L4:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	func2, .-func2
	.section	.rodata
.LC0:
	.string	"Child process PID: %d\n"
	.text
	.globl	func
	.type	func, @function
func:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	call	getpid@PLT
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	func2
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	func, .-func
	.section	.rodata
.LC1:
	.string	"./a.txt"
.LC2:
	.string	"fail1"
.LC3:
	.string	"fail2"
.LC4:
	.string	"Process PID: %d\n"
.LC5:
	.string	"Child process created!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$66, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -16(%rbp)
	cmpl	$-1, -16(%rbp)
	jne	.L9
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$5, %edi
	call	exit@PLT
.L9:
	movl	-16(%rbp), %eax
	movl	$0, %r9d
	movl	%eax, %r8d
	movl	$131073, %ecx
	movl	$7, %edx
	movl	$4096, %esi
	movl	$0, %edi
	call	mmap@PLT
	movq	%rax, -8(%rbp)
	cmpq	$-1, -8(%rbp)
	jne	.L10
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$5, %edi
	call	exit@PLT
.L10:
	call	getpid@PLT
	movl	%eax, %esi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	addq	$4096, %rax
	movl	$0, %ecx
	movl	$256, %edx
	movq	%rax, %rsi
	leaq	func(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	clone@PLT
	movl	%eax, -12(%rbp)
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-8(%rbp), %rax
	movl	$4, %edx
	movl	$4096, %esi
	movq	%rax, %rdi
	call	msync@PLT
	movl	-16(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
