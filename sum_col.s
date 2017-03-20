	.file	"sum_col.c"
	.text
	.globl	sum_col
	.type	sum_col, @function
sum_col:
.LFB0:
	.cfi_startproc
	pushl	%esi
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	movl	12(%esp), %ebx
	leal	(%ebx,%ebx), %esi
	addl	%esi, %ebx
	leal	3(%esi), %eax
	testl	%eax, %eax
	jle	.L4
	sall	$2, %ebx
	movl	20(%esp), %edx
	movl	16(%esp), %eax
	leal	(%eax,%edx,4), %ecx
	addl	$3, %esi
	movl	$0, %eax
	movl	$0, %edx
.L3:
	addl	(%ecx), %eax
	addl	$1, %edx
	addl	%ebx, %ecx
	cmpl	%esi, %edx
	jne	.L3
	jmp	.L2
.L4:
	movl	$0, %eax
.L2:
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	sum_col, .-sum_col
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
