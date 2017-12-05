#define M 7

typedef int** Marray_t;

void transpose(Marray_t A)
{
    int i, j;
    for (i = 0; i < M; ++i) {
        int* x = A[0] + M * i;
        int* y = A[0] + i;
        for (j = 0; j < i; ++j)  {
            int t = *(x + j);
            *(x + j) = *( y + M * j);
            *(y + M * j) = t;
        }
    }
}
/*
.L8:
	leal	0(,%esi,4), %ebp
	movl	(%edi,%esi,4), %ecx
	xorl	%eax, %eax
	movl	%ebp, (%esp)
	.p2align 4,,10
	.p2align 3
.L3:
	movl	(%esp), %edx
	addl	(%edi,%eax,4), %edx
	movl	(%ecx,%eax,4), %ebx
	movl	(%edx), %ebp
	movl	%ebp, (%ecx,%eax,4)
	addl	$1, %eax
	movl	%ebx, (%edx)
	cmpl	%esi, %eax
	jne	.L3
	addl	$1, %esi
	cmpl	$7, %esi
	jne	.L8
.L1:
	addl	$4, %esp
*/
