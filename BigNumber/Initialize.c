#include "bignum.h"
/*==================================================================
 * 함수명 : init_input
 * 함수 설명 : 입력으로 들어온 변수들에 값을 지정
 * 입력 : 연산에 이용되기 위하여 초기화될  in
 * 출력 : none
==================================================================*/
void init_input(D_BINT_t in)
{
	in->sig = (rand() % 3) - 1;
	in->len = (rand() % 3) + 30;
	if (in->sig == ZERO_SIG)
	{
		in->len = 1;
		in->dat[0] = 0;
	}
	else
	{
		for (int i = in->len - 1; i >= 0; i--)
			in->dat[i] = rand_gen();
	}
}


void init_input_to_zero(D_BINT_t in)
{
	in->sig = ZERO_SIG;
	in->len = 1;
	memset(in->dat, 0, sizeof(LIMB_t)*in->len);
}

//연산의 결과물이 들어갈 공간을 초기화 한다. 
//최대 길이를 모두 0으로 채운다.
void init_output(D_BINT_t out)
{

	memset(out->dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
}
