#include "bignum.h"
/*==================================================================
 Core Add
 * �Լ���: mpadd
 * �Լ� ���� : Algorithm 14.7�� ����
 * �Է� : �� ���� ���� in_1,in_2 n+1���� base b digit�� ����
 * ��� : none
==================================================================*/
/*	carry�� �߻��ϴ� ���� 2������ ������
	 1. in_1->dat[i] + carry�� ���� �� carry�� �߻��ϱ� ���ؼ� carry=1�� ���ۿ� ����
		(carry=0�̾��ٸ� in_1->dat[i]�� �̹� ǥ������ �ȿ� �����Ƿ� carry�� �߻��� �� ����
	    carry=1�̾��ٸ� in_1->dat[i] + carry�� ǥ�������� �Ѿ�� �ϴµ� �׷� ���� f�� ������ ����)
		��, �� ��쿡 carry�� �߻��Ѵٴ� ���� �ش� ��ġ�� ���� ����� 0�� �Ǵ� ���.
	 2. out->dat[i] = in_1->dat[i] + in_2->dat[i] + carry �� ��� ������� �� carry�� �߻��Ѵٴ� ����
		in_1->dat[i] + carry ���� ������� �� carry�� �߻����� �ʾҰ� �� ���� in_2->dat[i]�� ������ ��
		�߻��ߴٴ� �ǹ̰� �ȴ�. in_1->dat[i] + carry + k �� 0�� �Ǵ�(ǥ�� ������ �Ѿ��) k�� �����ϰ�
		in_2->dat[i] - (k) < in_2->dat[i]�� �����ϹǷ� in_1->dat[i] + in_2->dat[i] + carry < in_2->dat[i]
*/
void mpadd(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
{
	/* out = in_1 + in_2*/
	LIMB_t carry = 0;
	for (int i = 0; i < out->len ; i++)
	{
		out->dat[i] = in_1->dat[i] + in_2->dat[i] + carry;
		carry = ((((in_1->dat[i] + carry) < carry) || (out->dat[i] < in_2->dat[i])) ? 1 : 0);
		
	}
	if (carry)
		out->dat[out->len] = carry;
}