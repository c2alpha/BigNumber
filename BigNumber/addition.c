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
		out->sig = POS_SIG;
		mpadd(out, in1, in2);
	}
	else if (in1->sig == POS_SIG && in2->sig == ZERO_SIG)
	{
		copy(out, in1);
	}
	else if (in1->sig == POS_SIG && in2->sig == NEG_SIG)
	{
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
	int i = out->len - 1;
	int index = 0;
	while (out->dat[i] == 0)
	{
		index++;
		i--;
	}
	out->len = out->len - index;
	
	   
	if (out->len == 0)
		out->sig = ZERO_SIG;
	
	
}