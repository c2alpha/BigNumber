#include "bignum.h"

/*==================================================================
 * 함 수 명 : spmul
 * 함수설명 : 1word 곱셈을 수행
 * 파라미터 : 1word의 곱셈 연산에 수행될 in1,in2/ 그 결과를 저장할 u,v
 * 출    력 : none
 * out = in1 * in2
 * 결과는 2word가 될 수 있다.
==================================================================*/


//in1=(x1*b)+x0 in2=(y1*b)+y0  b=2^16 (32비트 표현을 16비트 표현으로 바꿈.)
void spmult(LIMB_t* u,LIMB_t* v, LIMB_t in1, LIMB_t in2)
{
	LIMB_t carry;
	LIMB_t x1, x0, y1, y0;
	//x,y의 하위 16비트 추출
	x0 = in1 & MASK_RHW;
	y0 = in2 & MASK_RHW;
	//x,y의 상위 16비트 추출
	x1 = (in1 & MASK_LHL) >> BITSZ_HL;
	y1 = (in2 & MASK_LHL) >> BITSZ_HL;

	//xi , yi 들이 16비트만 표현하므로, 두 개를 곱한 결과는 32비트 내에서 잘 표현됨.
	LIMB_t mid_val1, mid_val2, mid_val3, mid_val4;
	mid_val1 = x0 * y0;
	mid_val2 = x1 * y0;
	mid_val3 = x0 * y1;
	mid_val4 = x1 * y1;
	
	
	*v = mid_val1;
	LIMB_t temp = mid_val2 + mid_val3;//이제부터 overflow 가능성 생김
	if (temp < mid_val2)//mid_val2 보다 작다 or mid_val3보다 작다 어떤 것으로 해도 상관 없음.
		carry = 1;//mid_val4의 상위 16비트에 더해져야 할 carry
	else
		carry = 0;

	
	carry = (carry << BITSZ_HL) + ((temp&MASK_LHL)>>BITSZ_HL)
		;//위에서 발생한 carry는 mid_val4의 상위 16비트에
		 //더해져야 하고, mid_val2+mid_val3의 상위 16비트는
		 //mid_val4의 하위 16비트에 더해져야 함.=> 그걸 한번에 표현

	*v = *v + ((temp&MASK_RHW) << BITSZ_HL);//mid_val2+mid_val3의 하위 16비트는
											//x0 * y0의 상위16비트와 더해져야 함.
	if (*v < ((temp&MASK_RHW) << BITSZ_HL))
		carry++;

	*u = mid_val4 + carry;


}