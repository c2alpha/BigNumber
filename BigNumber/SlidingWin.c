#include "bignum.h"

void SlidingWindow(D_BINT_t A, D_BINT_t g, D_BINT_t e, LIMB_t k)
{
	//srand((unsigned)time(NULL));
	/*LIMB_t p_dat[32] = { 0x52a37a5d, 0xf9cf4bc9, 0x775b1670, 0x0ccd33ad,
	   0xba9ee123, 0x056179ca, 0xc5db23ec, 0x5e265ead,
	   0x998d2f99, 0x2cae03b4, 0xf9129bb7, 0x44096628,
	   0x62b37479, 0x5bb02a63, 0x292f1d6b, 0xf1cc88ac,
	   0xdaf88429, 0x185367a6, 0x9a7e42c2, 0xe5154b82,
	   0xaaeb4076, 0x7c6ac656, 0x56f31f22, 0xb211ddfb,
	   0xbecdfd37, 0xf7f446aa, 0x6ae0f2e5, 0xf01ac14d,
	   0x1a3a725e, 0xc8bc1fac, 0x654c1851, 0x63cb036a };*/
	LIMB_t p_dat[300] = { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
					  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
					  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
					  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
					  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
					  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
					  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
					  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 ,0x0 };
	//mont_exp를 위해 몽고메리 상수를 p로 해둔거
	D_BINT_t p;
	p->dat = p_dat;
	p->sig = POS_SIG;
	p->len = 32;
	D_BINT_t prime;
	LIMB_t prime_dat[301] = { 0, };
	prime->dat = prime_dat;

	D_BINT_t q, r;
	LIMB_t q_dat[301] = { 0, };
	LIMB_t r_dat[301] = { 0, };
	q->dat = q_dat;
	r->dat = r_dat;


	D_BINT_t gi[257];
	LIMB_t iter = 1;
	LIMB_t gi_dat[256][300] = { 0, };
	int i = 0;
	LIMB_t j = 0;

	D_BINT_t e_temp, g_temp;
	LIMB_t e_temp_dat[300] = { 0, };
	LIMB_t g_temp_dat[300] = { 0, };
	e_temp->dat = e_temp_dat;
	g_temp->dat = g_temp_dat;
	copy(e_temp, e);
	copy(g_temp, g);
	D_BINT_t A_temp;
	LIMB_t A_temp_dat[300] = { 0, };
	A_temp->dat = A_temp_dat;


	iter = iter << (k - 1);
	iter = iter - 1;
	//여기까지 하면 iter=2^(k-1) - 1

	//precomputation에 쓰일 gi를 초기화.
	//iter까지만 하는게 맞지만, iter가 0인 경우
	//g1 g2를 만들지 못함.
	for (i = 0; i <= (2 * iter) + 2; i++)
	{
		gi[i]->sig = POS_SIG;
		gi[i]->len = 1;
		gi[i]->dat = gi_dat[i];
	}

	//step 1 precomputation
	//step 1.1 
	gi[0]->dat[0] = 1;
	copy(gi[1], g);
	mpmul(gi[2], g, g);
	//step 1.2
	for (i = 1; i <= iter; i++)
	{
		mpmul(gi[(2 * i) + 1], gi[(2 * i) - 1], gi[2]);
		if (gi[(2 * i) + 1]->len >= p->len)
		{
			copy(prime, p);
			mpdiv(q, r, gi[(2 * i) + 1], prime);
			copy(gi[(2 * i) + 1], r);
		}
		init_input_to_zero(q);
		init_input_to_zero(r);

	}

	//step 2
	A->sig = POS_SIG;
	A->len = 1;
	A->dat[0] = 1;
	

	//step 3 
	LIMB_t a = 0;
	LIMB_t mask = LMSB_ONE;
	for (i = 1; i < k; i++)
	{
		mask |= LMSB_ONE >> i;
	}
	/*LIMB_t mask = MASK_WL;
	mask << (BITSZ_WL - k);*/
	
	int l = 0;
	LIMB_t t, s;
	t = (32 * e->len);
	//t = 32;
	i = t;
	while (i > 0)
	{
		s = k;
		//알고리즘상 ei확인
		a = LMSB_ONE & e->dat[e->len - 1];
		//a = a >> 1;

		if (a == 0)
		{
			square(A, A);
 			if (A->len >= p->len)
			{
				copy(prime, p);
				mpdiv(q, r, A, prime);
				copy(A, r);
			}
			i--;
			ShiftLeft_bit(e, e, 1);
		}

		else
		{
			a = mask & e->dat[e->len - 1];
			a = a >> (32 - k);
			while ((a&RLSB_ONE) == 0)
			{
				a = a >> 1;
				s--;
			}
			for (j = 0; j < s; j++)
			{
				square(A, A);
				if (A->len >= p->len)
				{
					copy(prime, p);
					mpdiv(q, r, A, prime);
					copy(A, r);
				}
			}
			mpmul(A, A, gi[a]);
			if (A->len >= p->len)
			{
				copy(prime, p);
				mpdiv(q, r, A, prime);
				copy(A, r);
			}
			ShiftLeft_bit(e, e, s);
			i = i - s;
		}



	}
	
	






	//for (j = 0; j < t; j++)
	//{
	//	//step 3.1
	//	for (i = 1; i <= k; i++)
	//	{
	//		//square(A, A);
	//		copy(A_temp, A);
	//		mpmul(A, A, A_temp);
	//		if (A->len >= p->len)
	//		{
	//			copy(prime, p);
	//			mpdiv(q, r, A, prime);
	//			copy(A, r);
	//		}
	//	}
	//	//step 3.2

	//	a = mask & e->dat[e->len - 1];
	//	a = a >> (32 - k);
	//	mpmul(A, A, gi[a]);
	//	if (A->len >= p->len)
	//	{
	//		copy(prime, p);
	//		mpdiv(q, r, A, prime);
	//		copy(A, r);
	//	}
	//	//init_input_to_zero(q);
	//	//init_input_to_zero(r);
	//	ShiftLeft_bit(e, e, k);

	//}
	//if (s > 0)
	//{
	//	for (i = 1; i <= s; i++)
	//	{
	//		//square(A, A);
	//		copy(A_temp, A);
	//		mpmul(A, A, A_temp);
	//		if (A->len >= p->len)
	//		{
	//			copy(prime, p);
	//			mpdiv(q, r, A, prime);
	//			copy(A, r);
	//		}
	//	}

	//	a = mask & e->dat[e->len - 1];
	//	a = a >> (32 - s);
	//	mpmul(A, A, gi[a]);

	//	if (A->len >= p->len)
	//	{
	//		copy(prime, p);
	//		mpdiv(q, r, A, prime);
	//		copy(A, r);
	//	}
	//	//init_input_to_zero(q);
	//	//init_input_to_zero(r);
	//}


	//copy(e, e_temp);
	//copy(g, g_temp);

}