typedef long long ll_t;

void store_prod(ll_t* dest, int x, ll_t y)
{
    *dest = x * y;
}

/*
    imull S R[%edx]:R[%eax] <- S x R[%eax]  Signed full multiply
    ------------------------------------------------------------
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
*/
