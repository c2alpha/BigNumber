#include "bignum.h"
/*==================================================================
 Core Sub
 * 함수명 : mpsub
 * 함수 설명 : Algorithm 14.9의 뺄셈
 * 입력 : 두 양의 정수 in1,in2. 각각 n+1 base b digit. in1>=in2
 * 출력 : none
==================================================================*/
/*	carry가 발생하는 경우
	1. in_1 - carry를 했을 때 carry가 발생한다는 것은 in_1 = 0인 경우밖에 없다.
	   (carry=0인 경우 carry가 발생하지 않고, carry=1일 경우 in_1=0일 때만 carry가 발생한다.)
	   즉, 이 경우에 carry가 발생한다면 해당 word의 연산 결과가 f....f가 된다
	2. in_1 - carry 에서 carry가 발생하지 않았다면 in_1 - carry에서 in_2를 빼주는 과정에서 carry가 발생할 수 있다.
	   in_1-carry-k = 0xffffffff 이 되는(표현 범위를 넘어가는) k가 존재할 것이고 (in2-k) < in2 이므로
	   0xffffffff 에서 in2-k를 뺀 것 이 in2를 뺀 것 보다 더 크다는 것이 carry 조건이다.
	   (in1-carry-k-(in2-k) > f...f - in2 where in1-carry-k == f...f)
*/

//원래꺼
//void mpsub(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
//{
//	/*out = in_1 - in_2*/
//	LIMB_t carry = 0;
//	
//	
//	for (int i = 0; i < out->len - 1; i++)
//	{
//		out->dat[i] = in_1->dat[i] - in_2->dat[i] - carry;
//		carry = ((((in_1->dat[i] - carry) > MASK_WL - carry) || (out->dat[i] > MASK_WL - in_2->dat[i])) ? 1 : 0);
//	}
//
//}

//devide할 때 수정한거
void mpsub(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2)
{
	/*out = in_1 - in_2*/
	LIMB_t carry = 0;

	for (int i = 0; i <= out->len - 1; i++)
	{
		out->dat[i] = in_1->dat[i] - in_2->dat[i] - carry;
		carry = ((((in_1->dat[i] - carry) > MASK_WL - carry) || (out->dat[i] > MASK_WL - in_2->dat[i])) ? 1 : 0);
	}

}