#include "bignum.h"
/*==================================================================
 * 함 수 명 : REDC
 * 함수설명 : T를 Montgomery redcuction
 * 파라미터 : TR^-1 담을 공간 A, T
 * 출    력 : none
==================================================================*/
void REDC(D_BINT_t A, D_BINT_t T)
{
	//몽고메리 상수
	LIMB_t m[300]= { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
				  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
				  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
				  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
				  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
				  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
				  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
				  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 };//32word

	LIMB_t m_prime = 0x71cbd4f9;

	D_BINT_t M;
	M->sig = POS_SIG;
	M->len = 32;
	M->dat = m;
	D_BINT_t U;
	LIMB_t U_dat[300] = { 0 };
	D_BINT_t temp;
	LIMB_t temp_dat[300] = { 0, };
	U->sig = POS_SIG;
	U->len = 1;
	U->dat = U_dat;
	temp->sig = POS_SIG;
	temp->dat = temp_dat;
	


	//step 1
	//T가 2n word일 때 A는 2n+1 word여야 함.
	copy(A, T);
	A->len++;
	A->dat[A->len - 1] = 0;
	temp->len = A->len;

	//step 2
	for (LIMB_t i = 0; i <= 31; i++)
	{
		//step 2.1
		U->dat[0] = A->dat[i] * m_prime;
			//mod b 는 그냥 한 워드에 담기게 한다는 의미로 해석
			//일반 곱하기로 하면 b를 넘어가는 부분은 알아서 짤림.
		
		//step 2.2
		mpmul(temp, M, U);
		padding(temp, i);
		Addition(A, A, temp);
	}

	//step 3
	LIMB_t res_dat[300] = { 0, };
	D_BINT_t res;
	res->dat = res_dat;
	res->len = 32;
	res->sig = POS_SIG;
	LIMB_t A_len;
	A_len = A->len - 1;
	for (int i = 31; i >= 0; i--)
	{
		res->dat[i] = A->dat[A_len];
		A_len--;
	}
	
	copy(A, res);
	//step 4
	if (compare(A, M) == 0)
		Subtraction(A, A, M);


}

void padding(D_BINT_t a, LIMB_t len)
{
	D_BINT_t temp;
	
	LIMB_t tempary[300] = { 0, };
	temp->dat = tempary;
	temp->sig = a->sig;
	temp->len = len + a->len;
	
	for (int i = 0; i < a->len; i++)
	{
		temp->dat[i + len] = a->dat[i];
		
	}
	for (int i = 0; i < len; i++)
	{
		temp->dat[i] = 0;
	}
	copy(a, temp);

}