#include "bignum.h"
/*==================================================================
 * �Լ��� : addition
 * �Լ� ���� : core add �� core sub�� �̿��ϴ� �Ϲ����� add
 * �Է� : ������ �̿�� in1,in2 �� ����� ����� out
 * ��� : none
	
 out = in1 + in2
==================================================================*/

void Addition(D_BINT_t out, D_BINT_t in1, D_BINT_t in2)
{
	//������ �� �� �ٲ�(������ �� �� �Ʒ���)
	D_BINT_t temp;
	LIMB_t temp_dat[300] = { 0, };
	temp->dat = temp_dat;

	temp->len = max(in1->len, in2->len);
	
	//out->len = max(in1->len, in2->len) + 1;

	if (in1->sig == ZERO_SIG && in2->sig == ZERO_SIG)
	{
		temp->sig = ZERO_SIG;
	}
	else if (in1->sig == POS_SIG && in2->sig == POS_SIG)
	{
		/*
		 input �ΰ��� ��ȣ�� ��� ����̹Ƿ� ����� ��ȣ�� ����� �ϰ� ���� ����
		*/
		temp->sig = POS_SIG;
		mpadd(temp, in1, in2);
	}
	else if (in1->sig == POS_SIG && in2->sig == ZERO_SIG)
	{
		copy(temp, in1);
	}
	else if (in1->sig == POS_SIG && in2->sig == NEG_SIG)
	{
		/*
		 �⺻������ ���� ������ �ϱ� ������ ���� ������ ���Ѵ�.
		 ���� in1�� ������ �� �۴ٸ� in2�� in1�� �ڸ��� �ٲ� sub�� �ϰ�,(����� ����)
		 �ƴ϶�� �״�� sub�� �����Ѵ�.(����� ���)
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
	else if (in1->sig == NEG_SIG && in2->sig == POS_SIG)
	{
		/*
		 in1�� ���밪�� �� �۴ٸ� in2��in1�� �ڸ��� �ٲپ� sub ����.(���=���)
		 �ƴ϶�� �״� sub����.(���=����)
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
	else if (in1->sig == NEG_SIG && in2->sig == ZERO_SIG)
	{
		copy(temp, in1);
	}
	else if (in1->sig == NEG_SIG && in2->sig == NEG_SIG)
	{
		/*
		 input �ΰ� ��� �����̹Ƿ� ����� �����̰�, ������ ����	
		*/
		temp->sig = NEG_SIG;
		mpadd(temp, in1, in2);
	}
	else if (in1->sig == ZERO_SIG && in2->sig == POS_SIG)
	{
		copy(temp, in2);
	}
	else if (in1->sig == ZERO_SIG && in2->sig == NEG_SIG)
	{
		copy(temp, in2);
	}

	/* out�� ���� word�� 0���� �������� �����͸� ����� len���� */
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