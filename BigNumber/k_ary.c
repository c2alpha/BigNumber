#include "bignum.h"
clock_t elapsed;
float sec;
#define START_WATCH \
{\
 elapsed = -clock(); \
}\

#define STOP_WATCH \
{\
 elapsed += clock();\
 sec = (float)elapsed/CLOCKS_PER_SEC;\
}\

#define PRINT_TIME(qstr) \
{\
 printf("\n[%s: %.10f s]\n",qstr,sec);\
}\

void k_ary(D_BINT_t A, D_BINT_t g, D_BINT_t e, LIMB_t k)
{
	//srand((unsigned)time(NULL));
	LIMB_t p_dat[32] = { 0x52a37a5d, 0xf9cf4bc9, 0x775b1670, 0x0ccd33ad,
	   0xba9ee123, 0x056179ca, 0xc5db23ec, 0x5e265ead,
	   0x998d2f99, 0x2cae03b4, 0xf9129bb7, 0x44096628,
	   0x62b37479, 0x5bb02a63, 0x292f1d6b, 0xf1cc88ac,
	   0xdaf88429, 0x185367a6, 0x9a7e42c2, 0xe5154b82,
	   0xaaeb4076, 0x7c6ac656, 0x56f31f22, 0xb211ddfb,
	   0xbecdfd37, 0xf7f446aa, 0x6ae0f2e5, 0xf01ac14d,
	   0x1a3a725e, 0xc8bc1fac, 0x654c1851, 0x63cb036a };
	D_BINT_t p;
	p->dat = p_dat;
	p->sig = POS_SIG;
	p->len = 32;
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
	LIMB_t gi_dat[257][300] = { 0, };
	LIMB_t i = 0;
	LIMB_t j = 0;

	
	iter = iter << k;
	iter = iter - 1;
	//여기까지 하면 iter=2^k - 1

	//precomputation에 쓰일 gi를 초기화.
	for (i = 0; i <= iter; i++)
	{
		gi[i]->sig = POS_SIG;
		gi[i]->len = 1;
		gi[i]->dat = gi_dat[i];
	}

	//step 1 precomputation
	
	gi[0]->dat[0] = 1;//step 1.1 

	//step 1.2
	for (i = 1; i <= iter; i++)
	{
		mpmul(gi[i], gi[i - 1], g);
		if (gi[i]->len >= p->len)
		{
			copy(prime, p);
			mpdiv(q, r, gi[i], prime);
			copy(gi[i], r);
		}
		//init_input_to_zero(q);
		//init_input_to_zero(r);
	}

	//스피드테스트를 위한 반복문
	//START_WATCH;
	//for (int z = 0; z < 1000; z++)
	//{

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
		LIMB_t t, s;
		t = (32 * e->len) / k;
		s = (32 * e->len) - (k * t);
		for (j = 0; j < t; j++)
		{
			//step 3.1
			for (i = 1; i <= k; i++)
			{
				//square(A, A);
				copy(A_temp, A);
				mpmul(A, A, A_temp);
				if (A->len >= p->len)
				{
					copy(prime, p);
					mpdiv(q, r, A, prime);
					copy(A, r);
				}
			}
			//step 3.2
			
			a = mask & e->dat[e->len - 1];
			a = a >> (32 - k);
			mpmul(A, A, gi[a]);
			if (A->len >= p->len)
			{
				copy(prime, p);
				mpdiv(q, r, A, prime);
				copy(A, r);
			}
			//init_input_to_zero(q);
			//init_input_to_zero(r);
			ShiftLeft_bit(e, e, k);

		}
		if (s > 0)
		{
			for (i = 1; i <= s; i++)
			{
				//square(A, A);
				copy(A_temp, A);
				mpmul(A, A, A_temp);
				if (A->len >= p->len)
				{
					copy(prime, p);
					mpdiv(q, r, A, prime);
					copy(A, r);
				}
			}
			
			a = mask & e->dat[e->len - 1];
			a = a >> (32 - s);
			mpmul(A, A, gi[a]);

			if (A->len >= p->len)
			{
				copy(prime, p);
				mpdiv(q, r, A, prime);
				copy(A, r);
			}
			//init_input_to_zero(q);
			//init_input_to_zero(r);
		}


		copy(e, e_temp);
		copy(g, g_temp);
	//}
	/*STOP_WATCH;
	printf("\nfor k=%d", k);
	PRINT_TIME("k-ary");*/

}
