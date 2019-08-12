#include"bignum.h"

void valid_test_gcd()
{
	D_BINT_t x, y, g, x_temp, y_temp;

	//ext bin을 위한 애들
	D_BINT_t ext_x, ext_y, a, b, g1, a_temp, b_temp, temp;
	LIMB_t temp_dat[300] = { 0, };
	
	LIMB_t a_temp_dat[300] = { 0, };
	LIMB_t b_temp_dat[300] = { 0, };
	LIMB_t ext_x_dat[300] = { 0, };
	LIMB_t ext_y_dat[300] = { 0, };
	LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t g1_dat[300] = { 0, };
	
	temp->dat = temp_dat;
	a_temp->dat = a_temp_dat;
	b_temp->dat = b_temp_dat;
	ext_x->dat = ext_x_dat;
	ext_y->dat = ext_y_dat;
	a->dat = a_dat;
	b->dat = b_dat;
	g1->dat = g1_dat;
	a->sig = POS_SIG;
	a->len = 1;
	b->sig = POS_SIG;
	b->len = 1;
	g1->sig = POS_SIG;
	g1->len = 1;
	//ext bin을 위한 애들

	LIMB_t x_dat[300] = { 0, };
	LIMB_t y_dat[300] = { 0, };
	LIMB_t g_dat[300] = { 0, };
	LIMB_t x_temp_dat[300] = { 0, };
	LIMB_t y_temp_dat[300] = { 0, };
	x_temp->dat = x_temp_dat;
	y_temp->dat = y_temp_dat;
	x->sig = POS_SIG;
	y->sig = POS_SIG;
	g->sig = POS_SIG;
	
	x->dat = x_dat;
	y->dat = y_dat;
	g->dat = g_dat;
	int num = 0;


	int valid = 1;

	while (valid)
	{
		num++;
		init_input(x);
		init_input(y);
		//x->dat[0] = x->dat[0] & 0x0fffffff;
		//y->dat[0] = y->dat[0] & 0x0fffffff;
		copy(x_temp, x);
		copy(y_temp, y);
		copy(ext_x, x);
		copy(ext_y, y);

		bin_gcd(g, x_temp, y_temp);
		ext_bin_gcd(g1, ext_x, ext_y, a, b);
		if (num % 50000 == 0)
		{
			printf("%d ", num);
		}
		if (compare2(g, g1) != 0)
		{
			valid = 0;
			printf("%d \n", num);
			printf("x\n");
			print_out(x);
			printf("y\n");
			print_out(y);
			printf("gcd\n");
			print_out(g);
			printf("ext gcd\n");
			print_out(g1);
		}
		mpmul(a_temp, a, x);
		
		mpmul(b_temp, b, y);
		
		Addition(temp, a_temp, b_temp);
		if (is_equal(temp, g) == 0)
		{
			valid = 0;
			printf("x\n");
			print_out(x);
			printf("y\n");
			print_out(y);
			printf("gcd\n");
			print_out(g);
			printf("ext gcd\n");
			print_out(g1);
			printf("a\n");
			print_out(a);
			printf("b\n");
			print_out(b);
			printf("ax\n");
			print_out(a_temp);
			printf("by\n");
			print_out(b_temp);
			printf("ax+by\n");
			print_out(temp);
		}
		

		memset(a->dat, 0, sizeof(LIMB_t) * 300);
		memset(b->dat, 0, sizeof(LIMB_t) * 300);
		memset(x->dat, 0, sizeof(LIMB_t) * 300);
		memset(y->dat, 0, sizeof(LIMB_t) * 300);
		memset(x_temp->dat, 0, sizeof(LIMB_t) * 300);
		memset(y_temp->dat, 0, sizeof(LIMB_t) * 300);
		memset(g->dat, 0, sizeof(LIMB_t) * 300);
		memset(g1->dat, 0, sizeof(LIMB_t) * 300);
		memset(ext_x->dat, 0, sizeof(LIMB_t) * 300);
		memset(ext_y->dat, 0, sizeof(LIMB_t) * 300);
		memset(a->dat, 0, sizeof(LIMB_t) * 300);
		memset(b->dat, 0, sizeof(LIMB_t) * 300);
		memset(a_temp->dat, 0, sizeof(LIMB_t) * 300);
		memset(b_temp->dat, 0, sizeof(LIMB_t) * 300);
		memset(temp->dat, 0, sizeof(LIMB_t) * 300);


		
	}
}