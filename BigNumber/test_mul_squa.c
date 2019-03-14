#include "bignum.h"

void valid_test_mul()
{
	LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t e_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t f_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t g_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t h_dat[MAX_BINT_LEN] = { 0, };

	D_BINT_t a;
	D_BINT_t b;
	D_BINT_t c;
	D_BINT_t d;
	D_BINT_t e;
	D_BINT_t f;
	D_BINT_t g;
	D_BINT_t h;
	a->dat = a_dat;
	b->dat = b_dat;
	c->dat = c_dat;
	d->dat = d_dat;
	e->dat = e_dat;
	f->dat = f_dat;
	g->dat = g_dat;
	h->dat = h_dat;
	int valid = 1;
	int run_num = 0;
	while (valid)
	{
		init_input(a);
		init_input(b);
		run_num++;
		if ((run_num % 100000) == 0)
			printf("+ ");
		//printf("%d\n", run_num);
		int check = 1;
		Addition(c, a, b);
		Subtraction(d, a, b);
		mpmul(e, c, d);
		square(f, a);
		square(g, b);
		Subtraction(h, f, g);
		/*printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		printf("\na \n");
		print_out(a);
		printf("\nb \n");
		print_out(b);
		printf("\nc \n");
		print_out(c);
		printf("\nd \n");
		print_out(e);
		printf("\nf \n");
		print_out(f);
		printf("\ng \n");
		print_out(g);
		printf("\nh \n");
		print_out(h);
		
		printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
*/
			   		 	  	  	

		if (e->sig != h->sig)
		{
			valid = 0;
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			printf("\na \n");
			print_out(a);
			printf("\nb \n");
			print_out(b);
			printf("\nc \n");
			print_out(c);
			printf("\nd \n");
			print_out(d);
			printf("\ne \n");
			print_out(e);
			printf("\nf \n");
			print_out(f);
			printf("\ng \n");
			print_out(g);
			printf("\nh \n");
			print_out(h);
		}
		check = is_equal(e, h);
		if (check != 1)
		{
			valid = 0;
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			printf("\na \n");
			print_out(a);
			printf("\nb \n");
			print_out(b);
			printf("\nc \n");
			print_out(c);
			printf("\nd \n");
			print_out(d);
			printf("\ne \n");
			print_out(e);
			printf("\nf \n");
			print_out(f);
			printf("\ng \n");
			print_out(g);
			printf("\nh \n");
			print_out(h);
			
		}
		memset(a_dat, 0, sizeof(LIMB_t) * 300);
		memset(b_dat, 0, sizeof(LIMB_t) * 300);
		memset(c_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(d_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(e_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(f_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(g_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(h_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
	}
}