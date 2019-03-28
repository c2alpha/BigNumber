#include "bignum.h"

/*==================================================================	
* �Լ��� : compare
* �Լ� ���� : ������ ũ�⸦ ���Ѵ�.
* �Է� : D_BINT_t Ÿ�� ����ü 2��(in1,in2)
* ��� : in1>=in2 �� ��� 0, in1<in2�� ��� 1
			
===================================================================*/

int compare(D_BINT_t in1, D_BINT_t in2)
{
	int check = 0;
		
		for (int i = max(in1->len,in2->len)-1; i >= 0; i--)
		{
			//���� if elseif ������ ���̸� ��ٸ� ���밪�� �� ũ�ٰ� �� �� �ֱ� ������ 
			//for���� �� ���� �ʰ� check�� ���� �� �־ �ӵ��鿡�� ȿ�����̴�.
			//��, sig�� 0�� ���� check���� �ʴ´�. sig�� 0���� ���Ƶ� len�� �ٸ� ���� �ֱ⶧��
			if ((in1->sig == POS_SIG) && (in1->len > in2->len))
				return 0;
			else if ((in1->sig == NEG_SIG) && (in1->len > in2->len))
			{
				return 0;
			}
			
			//���������� ���� word�� �ϳ��� ũ�ٸ� �� ū ���̱� ������ for���� �� ���� �ʾƵ�
			//check�� �� �� �ִ�.
			if (in1->dat[i] > in2->dat[i])
			{
				return 0;

			}
			else if (in1->dat[i] < in2->dat[i])
			{
				check = 1;
				return check;
			}
				
		}
		return 0;
		
		
}


//in1==in2 => 1  �ƴϸ� 0 , in1�� in2�� ���̴� ���� ���·� ���ð���
int is_equal(D_BINT_t in1, D_BINT_t in2)
{
	int len;
	len = in2->len;
	

	while (len--)
	{
		
		if (in1->dat[in2->len-1] != in2->dat[in2->len-1])// false
			return 0;	
	}

	return 1;//true
}

//in1>in2 => 1, in1<in2 => -1, in1==in2 => 0
int compare2(D_BINT_t in1, D_BINT_t in2)
{
	//	LIMB_t templen = in1->len; �̿���. ������ �ϸ鼭 �ٲ�
	LIMB_t templen = max(in1->len, in2->len);
	
	while (templen)
	{
		if (in1->dat[templen -1] > in2->dat[templen -1])
			return 1;	
		if (in1->dat[templen - 1] < in2->dat[templen - 1])
			return -1;	
		templen--;
	}

	return 0;	
}



//asdasd









/* swap���� �� �� ������ ����*/
//void compare(D_BINT_t in1, D_BINT_t in2)
//{
//	
//	for (int i = in1->len-1; i >= 0; i--)
//	{
//		if (in1->dat[i] < in2->dat[i])
//		{
//			D_BINT_t temp;
//			temp->sig = in1->sig;
//			temp->len = in1->len;
//			temp->dat = in1->dat;
//			in1->dat = in2->dat;
//			in1->sig = in2->sig;
//			in1->len = in2->len;
//			in2->dat = temp->dat;
//			in2->sig = temp->sig;
//			in2->len = temp->len;
//			break;
//		}
//			
//	}
//}