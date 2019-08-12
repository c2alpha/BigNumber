#include "bignum.h"
/*==================================================================
 * �Լ��� : Subtraction
 * �Լ� ���� : core add�� core sub�� �̿��ϴ� �Ϲ����� sub
 * �Է� : ������ �̿�Ǵ� in1,in2 �� ����� ������ out
 * ��� : none

 out = in1 - in2
==================================================================*/

void Subtraction(D_BINT_t out, D_BINT_t in1, D_BINT_t in2)
{
	
	//out->len = max(in1->len, in2->len) + 1;
	D_BINT_t temp;
	LIMB_t temp_dat[300] = { 0, };
	temp->dat = temp_dat;
	

	//div �� �� �����Ѱ�... ������ add�� �Ѿ�� ��� ������ �ִ� ���̸� �÷Ǵµ�,
	//��ǻ� ������ �ø� �ʿ䰡 ���� 
	temp->len = max(in1->len, in2->len);
	if (in1->sig == ZERO_SIG && in2->sig == ZERO_SIG)
	{
		temp->sig = ZERO_SIG;
	}
	else if (in1->sig == POS_SIG && in2->sig == POS_SIG)
	{
		/*
		 ���� ��ȣ�� ����̹Ƿ� ���밪�� ũ�⸦ ���Ͽ�
		 in1�� �� ���� ��� in, in2�� �ڸ��� �ٲپ� ������ �����Ѵ�(����� ��ȣ�� ����)
		 �ݴ��� ��� �״�� ������ �����Ѵ�(����� ��ȣ�� ���)
		*/
		if (compare(in1, in2))
		{
			temp->sig = NEG_SIG;
			mpsub(temp, in2, in1);
		}
		else
		{
			temp->sig = POS_SIG;
			mpsub(temp, in1, in2);
		}
	}
	else if (in1->sig == POS_SIG && in2->sig == ZERO_SIG)
	{
		copy(temp, in1);
	}
	else if (in1->sig == POS_SIG && in2->sig == NEG_SIG)
	{
		/*������� ������ ���� ���� ��ȣ�� ����̰� �� ���밪�� ���Ѱ��� ���*/
		temp->sig = POS_SIG;
		mpadd(temp, in1, in2);

	}
	else if (in1->sig == NEG_SIG && in2->sig == POS_SIG)
	{
		/*�������� ����� ���� ������ ����� ��ȣ�� �����̰� ������ ���Ѵ�.*/
		temp->sig = NEG_SIG;
		mpadd(temp, in1, in2);
	}
	else if (in1->sig == NEG_SIG && in2->sig == ZERO_SIG)
	{
		copy(temp, in1);
	}
	else if (in1->sig == NEG_SIG && in2->sig == NEG_SIG)
	{
		/*
		 in1�� �� ���� ��� �ΰ��� �ڸ��� �ٲپ� sub�� �����Ѵ�.(����� ���)
		 �ݴ��� ��� �״�� ������ �����Ѵ�(��� ����)
		*/
		if (compare(in1, in2))
		{
			temp->sig = POS_SIG;
			mpsub(temp, in2, in1);
		}
		else
		{
			temp->sig = NEG_SIG;
			mpsub(temp, in1, in2);
		}
	}
	else if (in1->sig == ZERO_SIG && in2->sig == POS_SIG)
	{
		copy(temp, in2);
		temp->sig = NEG_SIG;
	}
	else if (in1->sig == ZERO_SIG && in2->sig == NEG_SIG)
	{
		copy(temp, in2);
		temp->sig = POS_SIG;
	}
	
	/* out�� ���� word�� 0���� �������� �����͸� ����� len���� */
	//�������Ҷ� �ּ�ó���ϱ�!
	int len;
	len = temp->len - 1;
	while ((len >= 0) && (!temp->dat[len]))
	{
		len--;
		temp->len--;
	}
	if (!temp->len)
	{
		temp->sig = ZERO_SIG;
		temp->len = 1;
		temp->dat[0] = 0;
	}
	copy(out, temp);
	
	
	/*int i = out->len - 1;
	int index = 0;
	while (out->dat[i] == 0)
	{
		index++;
		i--;
	}
	out->len = out->len - index;
		
	if (out->len == 0)
		out->sig = ZERO_SIG;*/

	
}