	.file	"wc209.c"
	.globl	line
	.data
	.align 4
	.type	line, @object
	.size	line, 4
line:
	.long	1
	.globl	word
	.bss
	.align 4
	.type	word, @object
	.size	word, 4
word:
	.zero	4
	.globl	cha
	.align 4
	.type	cha, @object
	.size	cha, 4
cha:
	.zero	4
	.comm	juseokline,4,4
	.globl	i
	.data
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	1
	.globl	j
	.align 4
	.type	j, @object
	.size	j, 4
j:
	.long	1
	.section	.rodata
	.align 8
.LC0:
	.string	"Error: line %d: unterminated comment\n"
.LC1:
	.string	"%d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L3
	cmpl	$47, %eax
	je	.L4
	cmpl	$-1, %eax
	je	.L5
	jmp	.L26
.L4:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	movl	$0, %eax
	call	Juseok
	movl	%eax, i(%rip)
	movl	i(%rip), %eax
	testl	%eax, %eax
	jne	.L29
	movl	word(%rip), %eax
	subl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L29
.L3:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linee
	jmp	.L7
.L5:
	movl	$0, line(%rip)
	movl	$0, word(%rip)
	movl	$0, cha(%rip)
	jmp	.L7
.L26:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L8
	movl	$0, %eax
	call	spacee
	jmp	.L7
.L8:
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L7
.L29:
	nop
.L7:
	jmp	.L10
.L22:
	movsbl	-1(%rbp), %eax
	cmpl	$42, %eax
	je	.L12
	cmpl	$47, %eax
	je	.L13
	cmpl	$10, %eax
	je	.L14
	jmp	.L27
.L13:
	movl	cha(%rip), %edx
	movl	i(%rip), %eax
	addl	%edx, %eax
	movl	%eax, cha(%rip)
	movl	i(%rip), %eax
	cmpl	$1, %eax
	jne	.L10
	movl	$0, %eax
	call	Juseok
	movl	%eax, i(%rip)
	jmp	.L10
.L12:
	movl	cha(%rip), %edx
	movl	i(%rip), %eax
	addl	%edx, %eax
	movl	%eax, cha(%rip)
	movl	i(%rip), %eax
	testl	%eax, %eax
	jne	.L10
	movl	$0, %eax
	call	Juseokend
	movl	%eax, i(%rip)
	jmp	.L10
.L14:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	i(%rip), %eax
	cmpl	$1, %eax
	jne	.L17
	movl	$0, %eax
	call	linee
	jmp	.L10
.L17:
	movl	$0, %eax
	call	linej
	jmp	.L10
.L27:
	movl	cha(%rip), %edx
	movl	i(%rip), %eax
	addl	%edx, %eax
	movl	%eax, cha(%rip)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L30
	movl	i(%rip), %eax
	cmpl	$1, %eax
	jne	.L20
	movl	$0, %eax
	call	spacee
	jmp	.L30
.L20:
	movl	$0, %eax
	call	spacej
.L30:
	nop
.L10:
	call	getchar
	movb	%al, -1(%rbp)
	cmpb	$-1, -1(%rbp)
	je	.L21
	movl	j(%rip), %eax
	cmpl	$1, %eax
	je	.L22
.L21:
	movl	i(%rip), %eax
	testl	%eax, %eax
	jne	.L28
	movl	juseokline(%rip), %edx
	movq	stderr(%rip), %rax
	movl	$.LC0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, %eax
	jmp	.L25
.L28:
	movl	cha(%rip), %ecx
	movl	word(%rip), %edx
	movl	line(%rip), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
.L25:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	Juseok
	.type	Juseok, @function
Juseok:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L33
	cmpl	$10, %eax
	jg	.L34
	cmpl	$-1, %eax
	je	.L35
	jmp	.L32
.L34:
	cmpl	$42, %eax
	je	.L36
	cmpl	$47, %eax
	je	.L37
	jmp	.L32
.L36:
	movl	cha(%rip), %eax
	subl	$1, %eax
	movl	%eax, cha(%rip)
	movl	line(%rip), %eax
	movl	%eax, juseokline(%rip)
	movl	$0, i(%rip)
	movl	$0, %eax
	jmp	.L38
.L37:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	Juseok
	jmp	.L38
.L35:
	movl	$0, j(%rip)
	movl	$1, %eax
	jmp	.L38
.L33:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linee
	movl	i(%rip), %eax
	jmp	.L38
.L32:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L39
	movl	$0, %eax
	call	spacee
	movl	i(%rip), %eax
	jmp	.L38
.L39:
	movl	$1, %eax
.L38:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	Juseok, .-Juseok
	.globl	Juseokend
	.type	Juseokend, @function
Juseokend:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L42
	cmpl	$10, %eax
	jg	.L43
	cmpl	$-1, %eax
	je	.L44
	jmp	.L41
.L43:
	cmpl	$42, %eax
	je	.L45
	cmpl	$47, %eax
	jne	.L41
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$1, i(%rip)
	movl	$0, %eax
	call	spacee
	movl	i(%rip), %eax
	jmp	.L47
.L44:
	movl	$1, j(%rip)
	movl	i(%rip), %eax
	jmp	.L47
.L45:
	movl	$0, %eax
	call	Juseokend
	jmp	.L47
.L42:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linej
	movl	i(%rip), %eax
	jmp	.L47
.L41:
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L48
	movl	$0, %eax
	call	spacej
	movl	i(%rip), %eax
	jmp	.L47
.L48:
	movl	$0, %eax
.L47:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	Juseokend, .-Juseokend
	.globl	linee
	.type	linee, @function
linee:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L51
	cmpl	$47, %eax
	je	.L52
	cmpl	$-1, %eax
	je	.L53
	jmp	.L58
.L52:
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	Juseok
	movl	%eax, i(%rip)
	movl	i(%rip), %eax
	testl	%eax, %eax
	jne	.L59
	movl	word(%rip), %eax
	subl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L59
.L53:
	movl	$0, j(%rip)
	jmp	.L55
.L51:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linee
	jmp	.L55
.L58:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L56
	movl	$0, %eax
	call	spacee
	jmp	.L55
.L56:
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L55
.L59:
	nop
.L55:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	linee, .-linee
	.globl	spacee
	.type	spacee, @function
spacee:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L62
	cmpl	$47, %eax
	je	.L63
	cmpl	$-1, %eax
	je	.L64
	jmp	.L69
.L63:
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	Juseok
	movl	%eax, i(%rip)
	movl	i(%rip), %eax
	testl	%eax, %eax
	jne	.L70
	movl	word(%rip), %eax
	subl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L70
.L64:
	movl	$0, j(%rip)
	jmp	.L66
.L62:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linee
	jmp	.L66
.L69:
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L67
	movl	$0, %eax
	call	spacee
	jmp	.L66
.L67:
	movl	word(%rip), %eax
	addl	$1, %eax
	movl	%eax, word(%rip)
	jmp	.L66
.L70:
	nop
.L66:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	spacee, .-spacee
	.globl	spacej
	.type	spacej, @function
spacej:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L73
	cmpl	$42, %eax
	je	.L74
	cmpl	$-1, %eax
	je	.L75
	jmp	.L78
.L74:
	movl	$0, %eax
	call	Juseokend
	movl	%eax, i(%rip)
	jmp	.L76
.L75:
	movl	$0, j(%rip)
	jmp	.L76
.L73:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linej
	jmp	.L76
.L78:
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L79
	movl	$0, %eax
	call	spacej
.L79:
	nop
.L76:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	spacej, .-spacej
	.globl	linej
	.type	linej, @function
linej:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	getchar
	movb	%al, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$10, %eax
	je	.L82
	cmpl	$42, %eax
	je	.L83
	cmpl	$-1, %eax
	je	.L84
	jmp	.L87
.L83:
	movl	$0, %eax
	call	Juseokend
	movl	%eax, i(%rip)
	jmp	.L85
.L84:
	movl	$0, j(%rip)
	jmp	.L85
.L82:
	movl	line(%rip), %eax
	addl	$1, %eax
	movl	%eax, line(%rip)
	movl	cha(%rip), %eax
	addl	$1, %eax
	movl	%eax, cha(%rip)
	movl	$0, %eax
	call	linej
	jmp	.L85
.L87:
	call	__ctype_b_loc
	movq	(%rax), %rax
	movsbq	-1(%rbp), %rdx
	addq	%rdx, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L88
	movl	$0, %eax
	call	spacej
.L88:
	nop
.L85:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	linej, .-linej
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
