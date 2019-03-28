#include "bignum.h"

/*==================================================================
 * 함 수 명 : mpmul
 * 함수설명 : multi-precision 곱셈을 수행
 * 파라미터 : 곱셈에 이용될 2개의 변수와, 그 결과를 담을 공간.
 * 출    력 : none
 * out = in1 * in2
 * in1,in2의 길이가 각각 n,t라면, out의 길이는 n+t가 된다.
==================================================================*/

// for i-loop는 in2의 index조절, for j-loop는 in1의 index조절
void mpmul(D_BINT_t out, D_BINT_t in1, D_BINT_t in2)
{
	int i, j;
	LIMB_t uv[2] = { 0, };//알고리즘 상에서 u=uv[1] v=uv[0]
	LIMB_t carry = 0;
	D_BINT_t temp;
	LIMB_t temp_dat[MAX_BINT_LEN] = { 0, };
	temp->dat = temp_dat;
	temp->len = in1->len + in2->len;
	//init_output(out);

	if ((in1->sig == ZERO_SIG) || (in2->sig == ZERO_SIG))//input의 부호가 둘 다 0
	{
		out->sig = ZERO_SIG;
		out->len = 1;
		out->dat[0] = 0;
	}
	else if (in1->sig == in2->sig)//input의 부호가 같다.(+,+ or -,-)
	{
		temp->sig = POS_SIG;
		for (i = 0; i < in2->len; i++)
		{
			carry = 0;
			for (j = 0; j < in1->len; j++)
			{
				//uv = in1[j]*in2[i]
				spmult(&uv[1],&uv[0], in1->dat[j], in2->dat[i]);//인덱스 조심! 꼭 제일 위에 써놓은 것 처럼 하기
				uv[0] = uv[0] + carry;
				if (uv[0] < carry)
					uv[1]++;
				uv[0] = uv[0] + temp->dat[i + j];
				if (uv[0] < temp->dat[i + j])
					uv[1]++;

				//w[i+j] = v
				temp->dat[i + j] = uv[0];
				//c = u
				carry = uv[1];
			}
			// w[i+in1->len] = u
			temp->dat[i + in1->len] = carry;
		}
		copy(out, temp);
	}
	else//input의 부호가 다르다(+,- or -,+)
	{
		temp->sig = NEG_SIG;
		for (i = 0; i < in2->len; i++)
		{
			carry = 0;
			for (j = 0; j < in1->len; j++)
			{
				spmult(&uv[1],&uv[0], in1->dat[j], in2->dat[i]);
				uv[0] = uv[0] + carry;
				if (uv[0] < carry)
					uv[1]++;
				uv[0] = uv[0] + temp->dat[i + j];
				if (uv[0] < temp->dat[i + j])
					uv[1]++;

				temp->dat[i + j] = uv[0];
				carry = uv[1];
			}
			temp->dat[i + in1->len] = carry;
		}
		copy(out, temp);
	}

	//in1이 n digit, in2가 1로(=>1 digit) 들어왔을 경우
	//결과의 len은 n+1이 아닌 n 이므로 필요하다.
	while ((out->len != 0) && (!out->dat[out->len - 1]))
		out->len--;
	if (!out->len)
	{
		out->sig = ZERO_SIG;
		out->len = 1;
		out->dat[0] = 0;
	}


}