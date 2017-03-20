	.file	"store_ele.c"
	.text
	.globl	store_ele
	.type	store_ele, @function
store_ele:
.LFB0:
	.cfi_startproc
	movl	8(%esp), %eax
	leal	(%eax,%eax,4), %edx
	leal	(%eax,%edx,2), %edx
	imull	$99, 4(%esp), %eax
	addl	%edx, %eax
	addl	12(%esp), %eax
	movl	A(,%eax,4), %edx
	movl	16(%esp), %eax
	movl	%edx, (%eax)
	movl	$1980, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	store_ele, .-store_ele
	.comm	A,1980,32
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
