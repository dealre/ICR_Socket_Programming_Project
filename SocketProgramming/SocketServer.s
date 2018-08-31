	.file	"SocketServer.c"
	.text
	.globl	error
	.type	error, @function
error:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$0, %edi
	call	exit@PLT
	.cfi_endproc
.LFE5:
	.size	error, .-error
	.section	.rodata
	.align 8
.LC0:
	.string	"ERROR - Missing argument for port"
	.align 8
.LC1:
	.string	"ERROR - Too many arguments for port"
	.align 8
.LC2:
	.string	"Setting server up on port: %s\n"
	.align 8
.LC3:
	.string	"ERROR - Socket creation failed"
	.align 8
.LC4:
	.string	"ERROR - Binding to port failed"
	.align 8
.LC5:
	.string	"ERROR - Accepting connection failed"
.LC6:
	.string	"ERROR - Fork creation failed"
.LC7:
	.string	"ERROR - Reading data failed"
.LC8:
	.string	"Client: %s\n"
.LC9:
	.string	"ERROR - Writing data failed"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$352, %rsp
	movl	%edi, -340(%rbp)
	movq	%rsi, -352(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -340(%rbp)
	jg	.L3
	leaq	.LC0(%rip), %rdi
	call	error
.L3:
	cmpl	$2, -340(%rbp)
	jle	.L4
	leaq	.LC1(%rip), %rdi
	call	error
.L4:
	movq	-352(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, -328(%rbp)
	movl	$0, %edx
	movl	$1, %esi
	movl	$2, %edi
	call	socket@PLT
	movl	%eax, -324(%rbp)
	cmpl	$0, -324(%rbp)
	jns	.L5
	leaq	.LC3(%rip), %rdi
	call	error
.L5:
	leaq	-304(%rbp), %rax
	movl	$16, %esi
	movq	%rax, %rdi
	call	bzero@PLT
	movq	-352(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -320(%rbp)
	movw	$2, -304(%rbp)
	movl	$0, -300(%rbp)
	movl	-320(%rbp), %eax
	movzwl	%ax, %eax
	movl	%eax, %edi
	call	htons@PLT
	movw	%ax, -302(%rbp)
	leaq	-304(%rbp), %rcx
	movl	-324(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	bind@PLT
	testl	%eax, %eax
	jns	.L6
	leaq	.LC4(%rip), %rdi
	call	error
.L6:
	movl	-324(%rbp), %eax
	movl	$4, %esi
	movl	%eax, %edi
	call	listen@PLT
	movl	$16, -332(%rbp)
	leaq	-332(%rbp), %rdx
	leaq	-288(%rbp), %rcx
	movl	-324(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	accept@PLT
	movl	%eax, -316(%rbp)
	cmpl	$0, -316(%rbp)
	jns	.L7
	leaq	.LC5(%rip), %rdi
	call	error
.L7:
	call	fork@PLT
	movl	%eax, -312(%rbp)
	cmpl	$0, -312(%rbp)
	jns	.L8
	leaq	.LC6(%rip), %rdi
	call	error
.L8:
	cmpl	$0, -312(%rbp)
	je	.L9
.L11:
	leaq	-272(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero@PLT
	leaq	-272(%rbp), %rcx
	movl	-316(%rbp), %eax
	movl	$256, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	movl	%eax, -308(%rbp)
	cmpl	$0, -308(%rbp)
	jns	.L10
	leaq	.LC7(%rip), %rdi
	call	error
.L10:
	leaq	-272(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-272(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero@PLT
	jmp	.L11
.L9:
	cmpl	$0, -312(%rbp)
	jne	.L12
.L14:
	leaq	-272(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero@PLT
	movq	stdin(%rip), %rdx
	leaq	-272(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	fgets@PLT
	leaq	-272(%rbp), %rcx
	movl	-316(%rbp), %eax
	movl	$256, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	movl	%eax, -308(%rbp)
	cmpl	$0, -308(%rbp)
	jns	.L13
	leaq	.LC9(%rip), %rdi
	call	error
.L13:
	leaq	-272(%rbp), %rax
	movl	$256, %esi
	movq	%rax, %rdi
	call	bzero@PLT
	jmp	.L14
.L12:
	movl	-316(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	-324(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L16
	call	__stack_chk_fail@PLT
.L16:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
