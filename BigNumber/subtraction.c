#include "bignum.h"
/*==================================================================
 * 함수명 : Subtraction
 * 함수 설명 : core add와 core sub를 이용하는 일반적인 sub
 * 입력 : 뺄셈에 이용되는 in1,in2 그 결과를 저장할 out
 * 출력 : none

 out = in1 - in2
==================================================================*/

void Subtraction(D_BINT_t out, D_BINT_t in1, D_BINT_t in2)
{
	
	out->len = max(in1->len, in2->len)+1;
	if (in1->sig == ZERO_SIG && in2->sig == ZERO_SIG)
	{
		out->sig = ZERO_SIG;
	}
	else if (in1->sig == POS_SIG && in2->sig == POS_SIG)
	{
		/*
		 둘의 부호가 양수이므로 절대값의 크기를 비교하여
		 in1이 더 작은 경우 in, in2의 자리를 바꾸어 뺄셈을 수행한다(결과의 부호는 음수)
		 반대의 경우 그대로 뺄셈을 수행한다(결과의 부호는 양수)
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
	else if (in1->sig == POS_SIG && in2->sig == ZERO_SIG)
	{
		copy(out, in1);
	}
	else if (in1->sig == POS_SIG && in2->sig == NEG_SIG)
	{
		/*양수에서 음수를 빼는 경우로 부호는 양수이고 두 절대값을 더한것이 결과*/
		out->sig = POS_SIG;
		mpadd(out, in1, in2);

	}
	else if (in1->sig == NEG_SIG && in2->sig == POS_SIG)
	{
		/*음수에서 양수를 빼는 것으로 결과의 부호는 음수이고 절댓값을 더한다.*/
		out->sig = NEG_SIG;
		mpadd(out, in1, in2);
	}
	else if (in1->sig == NEG_SIG && in2->sig == ZERO_SIG)
	{
		copy(out, in1);
	}
	else if (in1->sig == NEG_SIG && in2->sig == NEG_SIG)
	{
		/*
		 in1이 더 작은 경우 두개의 자리를 바꾸어 sub를 수행한다.(결과는 양수)
		 반대의 경우 그대로 뺄셈을 수행한다(결과 음수)
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
	else if (in1->sig == ZERO_SIG && in2->sig == POS_SIG)
	{
		copy(out, in2);
		out->sig = NEG_SIG;
	}
	else if (in1->sig == ZERO_SIG && in2->sig == NEG_SIG)
	{
		copy(out, in2);
		out->sig = POS_SIG;
	}
	
	/* out의 상위 word에 0으로 차있으면 데이터를 지우고 len조정 */
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