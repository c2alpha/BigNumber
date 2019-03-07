#include "bignum.h"
/*==================================================================
 * �Լ��� : print_out
 * �Լ� ���� : ������ ���
 * �Է� : ����� ������ ���� ���� 1��
 * ��� : none
==================================================================*/
void print_out(D_BINT_t out)
{
	if (out->sig == ZERO_SIG)
	{
		printf("Sig : Zero \n");
		printf("Len : %d \n", out->len);
		printf("data = 0\n");
	}

	else if (out->sig == POS_SIG)
	{
		printf("Sig : Pos \n");
		printf("Len : %d \n", out->len);
		printf("data = ");
		for (int i = out->len - 1; i >= 0; i--)
			printf("%08X ", out->dat[i]);
		printf("\n\n\n");
	}

	else
	{
		printf("Sig : Neg \n");
		printf("Len : %d \n", out->len);
		printf("data = ");
		for (int i = out->len - 1; i >= 0; i--)
			printf("%08X ", out->dat[i]);
		printf("\n\n\n");
	}
	
	
}