#include "bignum.h"

void LtoR(D_BINT_t A, D_BINT_t g, D_BINT_t e)
{
	LIMB_t p_dat[32] = { 0x52a37a5d, 0xf9cf4bc9, 0x775b1670, 0x0ccd33ad,
	   0xba9ee123, 0x056179ca, 0xc5db23ec, 0x5e265ead,
	   0x998d2f99, 0x2cae03b4, 0xf9129bb7, 0x44096628,
	   0x62b37479, 0x5bb02a63, 0x292f1d6b, 0xf1cc88ac,
	   0xdaf88429, 0x185367a6, 0x9a7e42c2, 0xe5154b82,
	   0xaaeb4076, 0x7c6ac656, 0x56f31f22, 0xb211ddfb,
	   0xbecdfd37, 0xf7f446aa, 0x6ae0f2e5, 0xf01ac14d,
	   0x1a3a725e, 0xc8bc1fac, 0x654c1851, 0x63cb036a };
	/*LIMB_t p_dat[300] = { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
					  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
					  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
					  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
					  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
					  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
					  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
					  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 ,0x0 };*/
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

	D_BINT_t A_temp;
	LIMB_t A_temp_dat[300] = { 0, };
	A_temp->dat = A_temp_dat;


	A->sig = POS_SIG;
	A->len = 1;
	A->dat[0] = 1;
	LIMB_t i = 0;
	LIMB_t t = 0;
	LIMB_t k = 0;
	LIMB_t iter = 0;
	LIMB_t check = 0;
	//t = (e->len) * 32;//일단 word길이만큼 최대로 bit수 잡아주고
	////마지막 word의 최상위부터 1이 나올때까지 줄여준다.

//	while ((e->dat[e->len - 1] & (LMSB_ONE >> k)) == 0)
//	{
//		t--;
//		k++;
//	}
//	i = t;
//	if (i < 32)
//		check = i % BITSZ_WL;//최상위워드는 32비트가 꽉 차지 않았을 수 있다
//	else
//		check = 32;
//	LIMB_t mask = (LMSB_ONE >> k);
//	k = 0;
//	for (iter=0; iter<check; iter++)
//	{
//		copy(A_temp, A);
//		mpmul(A, A, A_temp);
//		if ((e->dat[e->len - 1] & (mask >> k)))
//			mpmul(A, A, g);
//		
//		k++;
//		if (A->len >= p->len)
//		{
//			copy(prime, p);
//			mpdiv(q, r, A, prime);
//			copy(A, r);
//		}
//		init_input_to_zero(q);
//		init_input_to_zero(r);
//		
//		
//	
//	}
//	/*printf("asdasdasd\n");
//	print_out(A);
//*/
//
//	int len = 0;
//	LIMB_t len_check = 1;
//	if (e->len >= 2)
//		len = e->len - 2;
//	else
//		len_check = 0;
//
//	if (len_check)
//	{
//		
//		while (len>=0)
//		{
//			
//			for (i = 0; i <= 31; i++)
//			{
//				copy(A_temp, A);
//				mpmul(A, A, A_temp);
//				if ((e->dat[len] & (LMSB_ONE >> i)))
//				{
//					mpmul(A, A, g);
//				}
//
//				if (A->len >= p->len)
//				{
//					copy(prime, p);
//					mpdiv(q, r, A, prime);
//					copy(A, r);
//				}
//				init_input_to_zero(q);
//				init_input_to_zero(r);
//				
//
//			}
//			len--;
//
//		}
//	}

	int len = 0;
	len = e->len - 1;
	while (len >= 0)
	{
		for (i = 0; i <= 31; i++)
		{
			/*copy(A_temp, A);
			mpmul(A, A, A_temp);*/
			square(A, A);
			if ((e->dat[len] & (LMSB_ONE >> i)))
			{
				mpmul(A, A, g);
			}
			if (A->len >= p->len)
			{
				copy(prime, p);
				mpdiv(q, r, A, prime);
				copy(A, r);
			}
			init_input_to_zero(q);
			init_input_to_zero(r);
		}
		len--;
	}	

	//최상위 워드에 0이 차있다면 지워주는 작업
	len = A->len - 1;
	while ((len >= 0) && (!A->dat[len]))
	{
		len--;
		A->len--;

	}
	if (!A->len)
	{
		A->sig = ZERO_SIG;
		A->len = 1;
		A->dat[0] = 0;
	}
	
	
	
	



}