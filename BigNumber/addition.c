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

	out->len = max(in1->len, in2->len)+1;

	if (in1->sig == ZERO_SIG && in2->sig == ZERO_SIG)
	{
		out->sig = ZERO_SIG;
	}
	else if (in1->sig == POS_SIG && in2->sig == POS_SIG)
	{
		/*
		 input �ΰ��� ��ȣ�� ��� ����̹Ƿ� ����� ��ȣ�� ����� �ϰ� ���� ����
		*/
		out->sig = POS_SIG;
		mpadd(out, in1, in2);
	}
	else if (in1->sig == POS_SIG && in2->sig == ZERO_SIG)
	{
		copy(out, in1);
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
			out->sig = NEG_SIG;
			mpsub(out, in2, in1);
		}
		else
		{
			out->sig = POS_SIG;
			mpsub(out, in1, in2);
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
			out->sig = POS_SIG;
			mpsub(out, in2, in1);
		}
		else
		{
			out->sig = NEG_SIG;
			mpsub(out, in1, in2);
		}
	}
	else if (in1->sig == NEG_SIG && in2->sig == ZERO_SIG)
	{
		copy(out, in1);
	}
	else if (in1->sig == NEG_SIG && in2->sig == NEG_SIG)
	{
		/*
		 input �ΰ� ��� �����̹Ƿ� ����� �����̰�, ������ ����	
		*/
		out->sig = NEG_SIG;
		mpadd(out, in1, in2);
	}
	else if (in1->sig == ZERO_SIG && in2->sig == POS_SIG)
	{
		copy(out, in2);
	}
	else if (in1->sig == ZERO_SIG && in2->sig == NEG_SIG)
	{
		copy(out, in2);
	}

	/* out�� ���� word�� 0���� �������� �����͸� ����� len���� */
	while (!out->dat[out->len - 1])
		out->len--;
	if (!out->len)
	{
		out->sig = ZERO_SIG;
		out->len = 1;
		out->dat[0] = 0;
	}
		
	
	
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