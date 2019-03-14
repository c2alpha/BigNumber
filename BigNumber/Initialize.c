#include "bignum.h"
/*==================================================================
 * �Լ��� : init_input
 * �Լ� ���� : �Է����� ���� �����鿡 ���� ����
 * �Է� : ���꿡 �̿�Ǳ� ���Ͽ� �ʱ�ȭ��  in
 * ��� : none
==================================================================*/
void init_input(D_BINT_t in)
{
	in->sig = (rand() % 3) - 1;
	in->len = (rand() % 3) + 30;
	if (in->sig == ZERO_SIG)
	{
		in->len = 1;
		in->dat[0] = 0;
	}
	else
	{
		for (int i = in->len - 1; i >= 0; i--)
			in->dat[i] = rand_gen();
	}
}


void init_input_to_zero(D_BINT_t in)
{
	in->sig = ZERO_SIG;
	in->len = 1;
	memset(in->dat, 0, sizeof(LIMB_t)*in->len);
}

//������ ������� �� ������ �ʱ�ȭ �Ѵ�. 
//�ִ� ���̸� ��� 0���� ä���.
void init_output(D_BINT_t out)
{

	memset(out->dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
}
