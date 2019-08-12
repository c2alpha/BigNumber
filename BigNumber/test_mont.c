#include "bignum.h"

void valid_test_mont()
{
	LIMB_t m[300] = { 0x616B52B7 ,0xBEC18FFD ,0x28D3166A ,0xEEE3B067 ,
				  0x0827ABBF ,0x1FE6BFFC ,0x279DECDD ,0x3B5FF0DA ,
				  0x7945EA76 ,0xB09FF817 ,0x3F4C599A ,0x57256C9A ,
				  0x377C1B96 ,0x07EFCC36 ,0x47E66E7F ,0x2D55CC39 ,
				  0xC7E2E48C ,0x7AD9F24A ,0x5B2E13FE ,0x6C47CA03 ,
				  0xCD72D203 ,0x631ED5DB ,0x18471F09 ,0xC0A6D4E4 ,
				  0x31CB4500 ,0x019D3848 ,0xFE4E80FB ,0xF95F7D71 ,
				  0xE36C0B5F ,0xB8DDCD1C ,0x0BEFDD5A ,0x9083F615 };//32word
	D_BINT_t M;
	M->sig = POS_SIG;
	M->len = 32;
	M->dat = m;
	D_BINT_t a, b, c, d, e;
	LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[300] = { 0, };
	LIMB_t d_dat[300] = { 0, };
	LIMB_t e_dat[300] = { 0, };
	a->dat = a_dat;
	b->dat = b_dat;
	c->dat = c_dat;
	d->dat = d_dat;
	e->dat = e_dat;

	c->sig = POS_SIG;
	d->sig = POS_SIG;
	e->sig = POS_SIG;
	
	int num_check = 0;
	int valid = 1;
	while (valid)
	{
		num_check++;
		printf("%d ", num_check);
		init_input(a);
		while (compare2(a, M) == 1)
			init_input(a);
		init_input(b);
		while (compare2(b, M) == 1)
			init_input(b);
		/*a->len = 3;
		b->len = 2;
		a->sig = POS_SIG;
		b->sig = POS_SIG;
		for (int i = 0; i < 3; i++)
			a->dat[i] = rand_gen();
		for (int i = 0; i < 2; i++)
			b->dat[i] = rand_gen();*/
		/*a->dat[2] = 0xCB4EEF3C;
		a->dat[1] = 0xB96D9ED3;
		a->dat[0] = 0x0901139B;
		b->dat[1] = 0x0CD40584;
		b->dat[0] = 0xB94BE8C3;*/



		mpmul(c, a, b);

		REDC(d, c);
		/*printf("d \n");
		print_out(d);
		printf("==========================\n");*/
		Mont_mul(e, a, b);
		
		if (is_equal(d, e) == 0)
		{
			valid = 0;
			printf("\na \n");
			print_out(a);
			printf("b \n");
			print_out(b);
			printf("c \n");
			print_out(c);
			printf("d \n");
			print_out(d);
			printf("e \n");
			print_out(e);
			printf("\n========================\n\n");
		}
		memset(a->dat, 0, sizeof(LIMB_t)*300);
		memset(b->dat, 0, sizeof(LIMB_t)*300);
		memset(c->dat, 0, sizeof(LIMB_t)*300);
		memset(d->dat, 0, sizeof(LIMB_t)*300);
		memset(e->dat, 0, sizeof(LIMB_t)*300);

	}
}