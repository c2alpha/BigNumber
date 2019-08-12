#include "bignum.h"
/*==================================================================
 * 함 수 명 : Mont_mul
 * 함수설명 : xyR^-1 계산
 * 파라미터 : mul할 x,y 저장공간 A
 * 출    력 : none
==================================================================*/
void Mont_mul(D_BINT_t A, D_BINT_t x, D_BINT_t y)
{
	x->len = 32;
	y->len = 32;
	//몽고메리 상수
	LIMB_t m[300] = { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
				  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
				  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
				  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
				  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
				  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
				  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
				  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 ,0x0};//32word

	LIMB_t m_prime = 0x71cbd4f9;

	D_BINT_t M;
	M->sig = POS_SIG;
	M->len = 32;
	M->dat = m;
	D_BINT_t U;
	LIMB_t U_dat[300] = { 0 };
	D_BINT_t temp;
	LIMB_t temp_dat[301] = { 0, };
	D_BINT_t xy_temp;
	LIMB_t xy_temp_dat[301] = { 0, };
	D_BINT_t x_temp;
	LIMB_t x_temp_dat[300] = { 0, };
	U->sig = POS_SIG;
	U->len = 1;
	U->dat = U_dat;
	temp->sig = POS_SIG;
	temp->dat = temp_dat;
	temp->len = 33;
	xy_temp->sig = POS_SIG;
	xy_temp->len = 33;
	xy_temp->dat = xy_temp_dat;
	x_temp->sig = POS_SIG;
	x_temp->len = 1;
	x_temp->dat = x_temp_dat;

	A->len = 33;
	A->sig = POS_SIG;
	
	//step 2
	for (int i = 0; i < 32; i++)
	{
		U->dat[0] = (A->dat[0] + (x->dat[i] * y->dat[0]))*m_prime;
		
		//step 2.2
		mpmul(temp, M, U);
		x_temp->dat[0] = x->dat[i];
		mpmul(xy_temp, y, x_temp);
		Addition(xy_temp, xy_temp, temp);
		Addition(A, A, xy_temp);
		for (int j = 0; j <= A->len; j++)
		{
			A->dat[j] = A->dat[j + 1];
		}
		init_input_to_zero(temp);
		init_input_to_zero(xy_temp);

		//A->dat[A->len] = 0;
	}
	A->len--;
	//step 3
	if (compare(A, M)==0)
	{
		Subtraction(A, A, M);
	}


}