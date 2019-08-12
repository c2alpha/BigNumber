#include "bignum.h"

void Mont_exp(D_BINT_t A, D_BINT_t g, D_BINT_t e)
{
	LIMB_t m[300] = { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
					  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
					  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
					  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
					  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
					  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
					  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
					  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 ,0x0 };//32word

	LIMB_t m_prime = 0x71cbd4f9;
	D_BINT_t M;
	M->sig = POS_SIG;
	M->len = 32;
	M->dat = m;

	LIMB_t r_dat[32] = { 0x9e94ad49, 0x413e7002, 0xd72ce995, 0x111c4f98,
							0xf7d85440, 0xe0194003, 0xd8621322, 0xc4a00f25,
							0x86ba1589, 0x4f6007e8, 0xc0b3a665, 0xa8da9365,
							0xc883e469, 0xf81033c9, 0xb8199180, 0xd2aa33c6,
							0x381d1b73, 0x85260db5, 0xa4d1ec01, 0x93b835fc,
							0x328d2dfc, 0x9ce12a24, 0xe7b8e0f6, 0x3f592b1b,
							0xce34baff, 0xfe62c7b7, 0x01b17f04, 0x06a0828e,
							0x1c93f4a0, 0x472232e3, 0xf41022a5, 0x6f7c09ea };
	D_BINT_t r;
	r->sig = POS_SIG;
	r->len = 32;
	r->dat = r_dat;
	D_BINT_t R;
	LIMB_t R_dat[300] = { 0, };
	R->dat = R_dat;
	copy(R, r);

	LIMB_t rs_dat[32] = { 0xf8da9582, 0x3c6d6d83, 0xad4ebc30, 0x8ad54fb8,
							 0x755bb885, 0xc813549d, 0x343e394c, 0x7131c8d5,
							 0xf13c02d1, 0xbb7def93, 0xfe3c41dd, 0x078513fb,
							 0x42024127, 0xea50e087, 0xfe30e82c, 0x1c940257,
							 0xc3934e1c, 0x8c3c4e03, 0xde66d665, 0x3896d3e2,
							 0x657554c4, 0xc08353f4, 0xb896d86b, 0x9b6111f3,
							 0x3375a894, 0x1f858f57, 0x17febedc, 0xa9473f08,
							 0x8aadacbd, 0x5267b014, 0x0cff09ce, 0x731cdf1b };
	D_BINT_t rs;
	rs->sig = POS_SIG;
	rs->len = 32;
	rs->dat = rs_dat;
	D_BINT_t R_Square;
	LIMB_t R_Square_dat[300] = { 0, };
	R_Square->dat = R_Square_dat;
	copy(R_Square, rs);
	

	D_BINT_t x;
	LIMB_t x_dat[300] = { 0, };
	x->dat = x_dat;
	Mont_mul(x, g, R_Square);

	D_BINT_t one;
	LIMB_t one_dat[300] = { 0, };
	one->sig = POS_SIG;
	one->len = 1;
	one->dat = one_dat;
	one->dat[0] = 1;

	copy(A, R);
	D_BINT_t A_temp;
	LIMB_t A_temp_dat[301] = { 0, };
	A_temp->dat = A_temp_dat;
	D_BINT_t res;
	LIMB_t res_dat[301] = { 0, };
	res->dat = res_dat;
	res->sig = POS_SIG;

	LIMB_t i = 0;
	int len = 0;
	len = e->len - 1;
	
	while (len >= 0)
	{
		for (i = 0; i <= 31; i++)
		{
		
			copy(A_temp, A);
			Mont_mul(res, A, A_temp);
			copy(A, res);
			init_input_to_zero(res);
			if ((e->dat[len] & (LMSB_ONE >> i)))
			{
				Mont_mul(res, A, x);
				copy(A, res);
			}
			init_input_to_zero(res);
			init_input_to_zero(A_temp);
		}
		len--;
	}

	/*LIMB_t t = 32 * (e->len);
	LIMB_t k = 0;
	while ((e->dat[e->len - 1] & (LMSB_ONE >> k)) == 0)
	{
		k++;
	}
	t = t - k;
	ShiftLeft_bit(e, e, k);
	LIMB_t i = 0;
	for (i = 0; i <= t; i++)
	{
		copy(A_temp, A);
		Mont_mul(res, A, A_temp);
		print_out(res);
		copy(A, res);
		init_input_to_zero(res);
		if ((e->dat[e->len - 1] & LMSB_ONE) == LMSB_ONE)
		{
			Mont_mul(res, A, x);
			copy(A, res);
			printf("check\n");
		}
		ShiftLeft_bit(e, e, 1);
		init_input_to_zero(res);
		init_input_to_zero(A_temp);
	}*/

	Mont_mul(res, A, one);
	copy(A, res);


}