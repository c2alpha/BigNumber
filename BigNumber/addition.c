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
		/*
		 input 두개의 부호가 모두 양수이므로 결과의 부호를 양수로 하고 덧셈 수행
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
		 기본적으로 절댓값 연산을 하기 때문에 둘의 절댓값을 비교한다.
		 만약 in1의 절댓값이 더 작다면 in2와 in1의 자리를 바꿔 sub를 하고,(결과가 음수)
		 아니라면 그대로 sub를 수행한다.(결과가 양수)
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
		 in1의 절대값이 더 작다면 in2와in1의 자리를 바꾸어 sub 수행.(결과=양수)
		 아니라면 그대 sub수행.(결과=음수)
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
		 input 두개 모두 음수이므로 결과는 음수이고, 덧셈을 수행	
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