### --------------------------------------------------------------------
### mydc.s
### 20170337 Sojung Son
### assignment 4
### Desk Calculator (dc)
### --------------------------------------------------------------------

	.equ   ARRAYSIZE, 20
	.equ   EOF, -1
	
.section ".rodata"

scanfFormat:
	.asciz "%s"
emptyStack:
	.asciz "dc: stack empty\n"
numberFormat:
	.asciz "%d\n"
errorzero:
	.asciz "zero div error!\n"
### --------------------------------------------------------------------

        .section ".data"

### --------------------------------------------------------------------

        .section ".bss"
buffer:
        .skip  ARRAYSIZE

### --------------------------------------------------------------------

	.section ".text"

	## -------------------------------------------------------------
	## int main(void)
	## Runs desk calculator program.  Returns 0.
	## -------------------------------------------------------------

	.globl  main
	.type   main,@function

main:

	pushl   %ebp
	movl    %esp, %ebp

input:
	## dc number stack initialized. %esp = %ebp
	## scanf("%s", buffer)
	pushl	$buffer
	pushl	$scanfFormat
	call    scanf
	addl    $8, %esp

	## check if user input EOF
	cmpl	$EOF, %eax
	je	quit

	## 	check if buffer[0] is not digit
	movl $0, %eax
	movb buffer(%eax), %al
	pushl %eax ##why do we do this?
	call isdigit
	addl $4, %esp

	cmpl $0, %eax  
	jne yesdigit #if digit, goto yesdigit

#if not, check the first character
	movl $buffer, %eax
	movb (%eax), %al
	##	if (buffer[0] == 'p') 
	cmpb $112, %al
	je isp
	##	if (buffer[0] == 'q') 
	cmpb $113, %al
	je isq
	##	if (buffer[0] == '+') 
	cmpb $43, %al
	je isplus
	##	if (buffer[0] == '-') 
	cmpb $45, %al
	je isminus
	##	if (buffer[0] == '*') 	
	cmpb $42, %al
	je ismull
	##	if (buffer[0] == '/') 
	cmpb $47, %al
	je isdiv
	##	if (buffer[0] == '%') 
	cmpb $37, %al
	je isremain
	##	if (buffer[0] == '^') 
	cmpb $'^', %al
	je ispower
	##	if (buffer[0] == '_') 
	cmpb $'_', %al
	je isunderbar
#imput is strange, so ignore
	jmp input



	## buffer[0] == 'p'
isp:
	## if stack is empty [if (stack.peek() == NULL)] 
	cmpl %ebp, %esp
	jne else1#not empty
	jmp stackisempty1#empty

	##printf("dc: stack empty\n");
	##continue;
stackisempty1:
	pushl $emptyStack
	call printf
	addl $4, %esp
	jmp input

	## stack it not empty
else1:
	##	printf("%d\n", (int)stack.top()); 
	pushl (%esp)
	pushl $numberFormat
	call printf
	addl $8, %esp
	jmp input

	## buffer[0] == 'q'
isq:
	##goto quit;
	je quit

	## buffer[0] == '+'
isplus:
	cmpl %esp, %ebp
	je stackisempty1
	## eax = (int)stack.pop();
	movl %esp, %eax
	movl (%eax), %eax
	addl $4, %esp

	cmpl %esp, %ebp
	jne else2

	##printf("dc: stack empty\n");
	##do not continue
	jmp stackisempty2

	subl $4, %esp
	movl %eax, %esp
	##continue;
	jmp input

stackisempty2:
	pushl $emptyStack
	call printf
	addl $4, %esp
	ret	
	##	ebx = (int)stack.pop(); 
else2:
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	## eax = eax + ebx
	addl %ebx, %eax
	pushl %eax
	jmp input

	## buffer[0] == '-'
isminus:
	cmpl %esp, %ebp
	je stackisempty1
	movl %esp, %eax
	movl (%eax), %eax
	addl $4, %esp
	cmpl %esp, %ebp
	jne else3
	je stackisempty2
	subl $4, %esp
	jmp input
else3:
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	subl %eax, %ebx #ebx = ebx -eax
	pushl %ebx
	jmp input


	## buffer[0] == '*'
ismull:
	cmpl %esp, %ebp
	je stackisempty1
	movl %esp, %eax
	movl (%eax), %eax
	addl $4, %esp
	cmpl %esp, %ebp
	jne else4
	je stackisempty2
	addl $4, %esp
	jmp input
else4:
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	imull %ebx #eax = eax * ebx
	pushl %eax
	jmp input




##############################################
	## buffer[0] == '/'
isdiv:
	cmpl %esp, %ebp
	je stackisempty1
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	cmpl %esp, %ebp
	jne else5
	je stackisempty2
	addl $4, %esp
	jmp input

else5:
	movl %esp, %eax
	movl (%eax), %eax
	addl $4, %esp
	cmpl $0, %ebx
	je errorz
	idiv %ebx # eax = eax/ebx 
	pushl %eax
	jmp input

errorz:
	pushl $errorzero
	call printf
	addl $4, %esp
	jmp quit


#########################################################3

	## buffer[0] == '%'
isremain:
	cmpl %esp, %ebp
	je stackisempty1
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	cmpl %esp, %ebp
	jne else7
	je stackisempty2
	addl $4, %esp
	jmp input

else7:
	movl %esp, %eax
	movl (%eax), %eax
	addl $4, %esp
	cmp $0, %ebx
	je errorz
	idiv %eax #eax= eax/ebx +edx
	pushl %edx
	jmp input


	## buffer[0] == '^'
ispower:
	cmpl %esp, %ebp
	je stackisempty1
	movl %esp, %ebx
	movl (%ebx), %ebx
	addl $4, %esp
	cmpl %esp, %ebp
	jne else6
	je stackisempty2
	addl $4, %esp
	jmp input
else6:
	movl %esp, %ecx
	movl (%ecx), %ecx
	addl $4, %esp
	movl %ecx, %edx
	# movl $1, %ecx
	jmp loop2
loop2:
	cmpl $1, %ebx
	je endloop2
	imul %edx, %ecx
	decl %ebx
	jmp loop2
endloop2:
	movl $0, %edx
	pushl %ecx
	jmp input


	## buffer[0] == '_'
isunderbar:
	movl $buffer, %eax
	addl $1, %eax
	movl (%eax), %eax
	pushl %eax
	call isdigit
	addl $4, %esp
	cmpl $0, %eax
	jne yesdigit2
	jmp input

	## digit(non negative)
yesdigit : 
	# movl $0, %eax
	movl $buffer, %eax
	cmpl $0, %eax
	je digitis0
	pushl %eax
	# atoi, save the result in atoi
	call atoi
	addl $4, %esp
	cmpl $0, %eax
	je input

	pushl %eax
	jmp input
	##		stack.push(no);	/* pushl some register value */
	##	}
	## }

digitis0:
	movl $0, %eax
	pushl %eax
	jmp input

	##digit(negative)
yesdigit2:
	movl $buffer, %ecx
	addl $1, %ecx
	cmpl $0, %ecx
	je digitis0

	push %ecx
	call atoi
	addl $4, %esp

	cmpl $0, %eax
	je input

# make it negative
	movl %eax, %ebx
	subl %ebx, %eax
	subl %ebx, %eax

	pushl %eax
	jmp input


quit:	
	## return 0
	movl    $0, %eax
	movl    %ebp, %esp
	popl    %ebp
	ret


