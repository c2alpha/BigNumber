#include "bignum.h"
/*==================================================================
 Core Sub
 * �Լ��� : mpsub
 * �Լ� ���� : Algorithm 14.9�� ����
 * �Է� : �� ���� ���� in1,in2. ���� n+1 base b digit. in1>=in2
 * ��� : none
==================================================================*/
/*	carry�� �߻��ϴ� ���
	1. in_1 - carry�� ���� �� carry�� �߻��Ѵٴ� ���� in_1 = 0�� ���ۿ� ����.
	   (carry=0�� ��� carry�� �߻����� �ʰ�, carry=1�� ��� in_1=0�� ���� carry�� �߻��Ѵ�.)
	   ��, �� ��쿡 carry�� �߻��Ѵٸ� �ش� word�� ���� ����� f....f�� �ȴ�
	2. in_1 - carry ���� carry�� �߻����� �ʾҴٸ� in_1 - carry���� in_2�� ���ִ� �������� carry�� �߻��� �� �ִ�.
	   in_1-carry-k = 0xffffffff �� �Ǵ�(ǥ�� ������ �Ѿ��) k�� ������ ���̰� (in2-k) < in2 �̹Ƿ�
	   0xffffffff ���� in2-k�� �� �� �� in2�� �� �� ���� �� ũ�ٴ� ���� carry �����̴�.
	   (in1-carry-k-(in2-k) > f...f - in2 where in1-carry-k == f...f)
*/

//������
//void mpsub(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
//{
//	/*out = in_1 - in_2*/
//	LIMB_t carry = 0;
//	
//	
//	for (int i = 0; i < out->len - 1; i++)
//	{
//		out->dat[i] = in_1->dat[i] - in_2->dat[i] - carry;
//		carry = ((((in_1->dat[i] - carry) > MASK_WL - carry) || (out->dat[i] > MASK_WL - in_2->dat[i])) ? 1 : 0);
//	}
//
//}

//devide�� �� �����Ѱ�
void mpsub(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
{
	/*out = in_1 - in_2*/
	LIMB_t carry = 0;

	for (int i = 0; i <= out->len - 1; i++)
	{
		out->dat[i] = in_1->dat[i] - in_2->dat[i] - carry;
		carry = ((((in_1->dat[i] - carry) > MASK_WL - carry) || (out->dat[i] > MASK_WL - in_2->dat[i])) ? 1 : 0);
	}

}