	.file	"var_prod.c"
	.text
	.globl	var_prod_ele
	.type	var_prod_ele, @function
var_prod_ele:
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
	movl	24(%esp), %esi
	movl	40(%esp), %ebp
	testl	%esi, %esi
	jle	.L4
	movl	%esi, %eax
	imull	%esi, %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	movl	32(%esp), %ebx
	movl	%esi, %edi
	imull	36(%esp), %edi
	leal	0(,%esi,4), %eax
	imull	%eax, %edi
	addl	28(%esp), %edi
	movl	$0, %eax
	movl	$0, %edx
.L3:
	movl	%ebp, %ecx
	addl	(%ebx), %ecx
	imull	(%edi,%edx,4), %ecx
	addl	%ecx, %eax
	addl	$1, %edx
	addl	(%esp), %ebx
	cmpl	%edx, %esi
	jne	.L3
	jmp	.L2
.L4:
	movl	$0, %eax
.L2:
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
	.size	var_prod_ele, .-var_prod_ele
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
