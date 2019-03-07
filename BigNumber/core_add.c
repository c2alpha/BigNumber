#include "bignum.h"
/*==================================================================
 Core Add
 * 함수명: mpadd
 * 함수 설명 : Algorithm 14.7의 덧셈
 * 입력 : 두 양의 정수 in_1,in_2 n+1개의 base b digit을 가짐
 * 출력 : none
==================================================================*/
/*	carry가 발생하는 경우는 2가지로 나뉜다
	 1. in_1->dat[i] + carry를 했을 때 carry가 발생하기 위해선 carry=1인 경우밖에 없다
		(carry=0이었다면 in_1->dat[i]은 이미 표현범위 안에 있으므로 carry가 발생할 수 없고
	    carry=1이었다면 in_1->dat[i] + carry이 표현범위를 넘어가야 하는데 그런 경우는 f로 가득찬 경우뿐)
		즉, 이 경우에 carry가 발생한다는 것은 해당 위치의 연산 결과가 0이 되는 경우.
	 2. out->dat[i] = in_1->dat[i] + in_2->dat[i] + carry 을 모두 계산했을 때 carry가 발생한다는 것은
		in_1->dat[i] + carry 까지 계산했을 때 carry가 발생하지 않았고 그 이후 in_2->dat[i]를 더해줄 때
		발생했다는 의미가 된다. in_1->dat[i] + carry + k 가 0이 되는(표현 범위를 넘어가는) k가 존재하고
		in_2->dat[i] - (k) < in_2->dat[i]이 성립하므로 in_1->dat[i] + in_2->dat[i] + carry < in_2->dat[i]
*/
void mpadd(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
{
	/* out = in_1 + in_2*/
	LIMB_t carry = 0;
	for (int i = 0; i < out->len ; i++)
	{
		out->dat[i] = in_1->dat[i] + in_2->dat[i] + carry;
		carry = ((((in_1->dat[i] + carry) < carry) || (out->dat[i] < in_2->dat[i])) ? 1 : 0);
		
	}
	if (carry)
		out->dat[out->len] = carry;
}