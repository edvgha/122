	.file	"transpose.c"
	.text
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$4, %esp
	.cfi_def_cfa_offset 24
	movl	24(%esp), %ebp
	movl	$28, %edi
	movl	$0, %esi
	jmp	.L2
.L5:
	movl	0(%ebp), %ecx
	leal	0(,%esi,4), %edx
	testl	%esi, %esi
	jle	.L3
	addl	%ecx, %edx
	movl	$0, %eax
	addl	%edi, %ecx
	movl	%edi, (%esp)
.L4:
	movl	(%ecx,%eax,4), %ebx
	movl	(%edx), %edi
	movl	%edi, (%ecx,%eax,4)
	movl	%ebx, (%edx)
	addl	$1, %eax
	addl	$28, %edx
	cmpl	%esi, %eax
	jne	.L4
	movl	(%esp), %edi
.L3:
	addl	$28, %edi
.L2:
	addl	$1, %esi
	cmpl	$7, %esi
	jne	.L5
	addl	$4, %esp
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 16
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	transpose, .-transpose
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
