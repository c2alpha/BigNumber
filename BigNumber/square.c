#include "bignum.h"
/*==================================================================
 * 함 수 명 : square
 * 함수설명 : multi-precision squaring을 수행
 * 파라미터 : squaring에 이용될 1개의 변수와, 그 결과를 담을 공간.
 * 출    력 : none
 * out = in^2
 * in길이가 n이라면, out의 길이는 2n이 된다.
==================================================================*/
void square(D_BINT_t out, D_BINT_t in)
{
	D_BINT_t temp;
	LIMB_t temp_dat[MAX_BINT_LEN] = { 0, };
	temp->dat = temp_dat;
	temp->len = (in->len) << 1;
	temp->sig = in->sig*in->sig;
	LIMB_t last_pos;
	LIMB_t c, uv[2], carry[2] = { 0, }, MSB, last_carry;//uv[1]=u uv[0]=v.
	//last_carry는 j-loop가 다 돌았을 때 갱신된다.
	//c는 uv[1]에서 발생하는 carry를 저장
	//carry[0]는 uv[1]이 들어갈 공간. carry[1]은 c가 들어갈 공간
	last_carry = 0;
	last_pos = 2 * in->len - 1;//j-loop가 완전히 한번 다 돌 때 갱신된다.
	for (int i = 0; i < in->len; i++)
	{
		//(uv) = w[2i] + x[i]* x[i], w[2i] = v, c = u
		spmult(&uv[1],&uv[0], in->dat[i], in->dat[i]);
		uv[0] += temp->dat[2*i];
		if (uv[0] < temp->dat[2*i])
			uv[1]++;
		
		c = 0;
		
		if (2 * i == last_pos && last_carry)//for i-loop의 마지막 index(i= in->len -1) 일 때만 진입 가능.	
		{
			uv[1] += last_carry;
			if (uv[1] < last_carry)
				c++;
			last_carry = 0;
		}
		
		//알고리즘 상으로 w[2i] = v 하는 작업
		temp->dat[2*i] = uv[0];
		//알고리즘 상으로 c = u 하는 작업
		carry[0] = uv[1];
		carry[1] = c;

		
		c = 0;
		for (int j = i + 1; j < in->len; j++)
		{
			// uv = x[i] * x[j] 
			spmult(&uv[1],&uv[0], in->dat[i], in->dat[j]);
			// 2배 하는 작업을 shift로 처리
			MSB = (uv[0] & LMSB_ONE) ? 1 : 0;
			c = (uv[1] & LMSB_ONE) ? 1 : 0;
			uv[0] <<= 1;
			uv[1] <<= 1;
			uv[1] += MSB;
			//uv[0]의 최상위 비트가 차있으면 uv[0]을 두배 했을 때 uv[1]로 carry가 있어야함
			//uv[1]역시 마찬가지 그 carry는 c로 표시.
			//uv = uv + carry
			uv[0] += carry[0];
			if (uv[0] < carry[0])
			{
				uv[1]++;
				if (uv[1] == 0)
					c++;
			}

			uv[1] += carry[1];
			if (uv[1] < carry[1])
				c++;

			// uv = uv + w[i+j] 
			uv[0] += temp->dat[i + j];
			if (uv[0] < temp->dat[i + j])
			{
				uv[1]++;
				if (uv[1] == 0)
					c++;
			}
			
			
			
			if (((i + j) == last_pos) && last_carry)
			{
				uv[1] += last_carry;
				if (uv[1] < last_carry)
					c++;
				last_carry = 0;
			}
			
			// w[i+j] = v, c = u 
			temp->dat[i + j] = uv[0];
			carry[0] = uv[1];
			carry[1] = c;
		}
		// w[i+j]는 i+j가 이전단계의 i+t와 같다면 2word가 된다.
		// w[i+in->len] = u 
		temp->dat[i + in->len] = carry[0];
		//w[i+in->len]에서 생기는 carry 저장
		last_carry = carry[1];
		last_pos = i + in->len;
	}

	copy(out, temp);
	
}

