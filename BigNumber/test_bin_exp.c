#include "bignum.h"
//exponential test
void valid_bin_ext()
{
	D_BINT_t a, g, e, g_temp, e_temp;
	LIMB_t a_dat[301] = { 0, };
	LIMB_t g_dat[301] = { 0, };
	LIMB_t e_dat[301] = { 0, };
	LIMB_t g_temp_dat[301] = { 0, };
	D_BINT_t A;
	LIMB_t A_dat[301] = { 0, };
	A->dat = A_dat;
	LIMB_t e_temp_dat[301] = { 0, };
	a->dat = a_dat;
	g->dat = g_dat;
	e->dat = e_dat;
	g_temp->dat = g_temp_dat;
	e_temp->dat = e_temp_dat;
	a->sig = POS_SIG;
	g->sig = POS_SIG;
	e->sig = POS_SIG;
	a->len = 1;
	g->len = 1;
	e->len = 1;
	int k = 0;
	int num_check = 0;
	int valid = 1;
	while (valid)
	{

		k = (rand_gen() % 8) + 1;
		
		//printf("%d, %d-sliding\n ", num_check, k);
		printf("%d ", num_check);
		init_input(g);
		//printf("%d ", g->len);
		init_input(e);
		//printf("%d \n", e->len);
		copy(g_temp, g);
		copy(e_temp, e);
		//LtoR(a, g_temp, e_temp);
		Mont_exp(a, g_temp, e_temp);
		copy(g_temp, g);
		copy(e_temp, e);
		SlidingWindow(A, g_temp, e_temp, k);
		//Mont_exp(A, g_temp, e_temp);
		if (is_equal(A, a) == 0)
		{
			printf("Mont\n");
			print_out(a);
			printf("Sliding\n");
			print_out(A);
			printf("g\n");
			print_out(g);
			printf("e\n");
			print_out(e);
			valid = 0;
		}
		init_input_to_zero(g);
		init_input_to_zero(e);
		init_input_to_zero(a);
		init_input_to_zero(A);
		num_check++;

	}
}