	.file	"store_prod.c"
	.text
	.globl	store_prod
	.type	store_prod, @function
store_prod:
.LFB0:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	movl	16(%esp), %eax
	movl	20(%esp), %ecx
	movl	%eax, %edi
	sarl	$31, %edi
	movl	%edi, %esi
	imull	%ecx, %esi
	movl	%eax, %edx
	imull	24(%esp), %edx
	addl	%edx, %esi
	mull	%ecx
	addl	%esi, %edx
	movl	12(%esp), %ecx
	movl	%eax, (%ecx)
	movl	%edx, 4(%ecx)
	popl	%esi
	.cfi_restore 6
	.cfi_def_cfa_offset 8
	popl	%edi
	.cfi_restore 7
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE0:
	.size	store_prod, .-store_prod
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
