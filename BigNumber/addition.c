#include "bignum.h"
/*==================================================================
 * 함수명 : addition
 * 함수 설명 : core add 와 core sub를 이용하는 일반적인 add
 * 입력 : 덧셈에 이용될 in1,in2 그 결과가 저장될 out
 * 출력 : none
	
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

	/* out의 상위 word에 0으로 차있으면 데이터를 지우고 len조정 */
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