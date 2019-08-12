#include "bignum.h"

void RtoL(D_BINT_t A, D_BINT_t g, D_BINT_t e)
{
	D_BINT_t q_A, r_A, q_S, r_S;
	LIMB_t qA_dat[301] = { 0, };
	LIMB_t rA_dat[301] = { 0, };
	LIMB_t qS_dat[301] = { 0, };
	LIMB_t rS_dat[301] = { 0, };
	q_A->dat = qA_dat;
	r_A->dat = rA_dat;
	q_S->dat = qS_dat;
	r_S->dat = rS_dat;
	D_BINT_t prime;
	LIMB_t prime_dat[301] = { 0, };
	prime->dat = prime_dat;
	
	/*D_BINT_t fuck;
	LIMB_t fuck_dat[301] = { 0, };
	fuck->dat = fuck_dat;
	D_BINT_t q, r;
	LIMB_t q_dat[301] = { 0, };
	LIMB_t r_dat[301] = { 0, };
	q->dat = q_dat;
	r->dat = r_dat;*/


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

	D_BINT_t S, S_temp;
	LIMB_t S_dat[300] = { 0, };
	LIMB_t S_temp_dat[300] = { 0, };
	S->dat = S_dat;
	S_temp->dat = S_temp_dat;
	copy(S, g);
	A->len = 1;
	A->sig = POS_SIG;
	A->dat[0] = 1;
	int phase = 1;
	while (e->sig != ZERO_SIG)
	{
		if (is_even(e) == 0)//e°¡ È¦¼ö¸é
		{
			mpmul(A, A, S);
			
		}
		ShiftRight_bit(e, e, 1);
		if (e->len <= 1 && e->dat[0] == 0)
			e->sig = ZERO_SIG;
		if (e->sig != ZERO_SIG)
		{
			/*copy(S_temp, S);
			mpmul(S, S, S_temp);*/
			square(S, S);
		}
		if (A->len >= p->len)
		{
			copy(prime, p);
			mpdiv(q_A, r_A, A, prime);
			copy(A, r_A);
		}
		if (S->len >= p->len)
		{
			copy(prime, p);
			mpdiv(q_S, r_S, S, prime);
			copy(S, r_S);
			
		}
		if (A->len == p->len)
		{
			if (compare2(A, p) == 1)
			{
				copy(prime, p);
				mpdiv(q_A, r_A, A, prime);
				copy(A, r_A);
			}
		}
		if (S->len == p->len)
		{
			if (compare2(A, p) == 1)
			{
				copy(prime, p);
				mpdiv(q_S, r_S, S, prime);
				copy(S, r_S);
			}
		}
		init_input_to_zero(q_A);
		init_input_to_zero(r_A);
		init_input_to_zero(q_S);
		init_input_to_zero(r_S);
		
		
	
		
		

	}
	
}