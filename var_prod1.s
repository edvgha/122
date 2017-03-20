	.file	"var_prod1.c"
	.text
	.globl	var_prod_1d
	.type	var_prod_1d, @function
var_prod_1d:
.LFB0:
	.cfi_startproc
	movl	16(%esp), %eax
	movl	8(%esp), %edx
	movl	(%eax,%edx,4), %eax
	movl	20(%esp), %edx
	movl	12(%esp), %ecx
	imull	(%edx,%ecx,4), %eax
	ret
	.cfi_endproc
.LFE0:
	.size	var_prod_1d, .-var_prod_1d
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
