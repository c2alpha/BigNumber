#include"bignum.h"

int valid_test_div()
{
	LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[300] = { 0, };
	LIMB_t d_dat[300] = { 0, };
	LIMB_t b_temp_dat[300] = { 0, };
	LIMB_t c_temp_dat[300] = { 0, };
	LIMB_t q_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t r_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t q_dat_temp[MAX_BINT_LEN] = { 0, };
	LIMB_t r_dat_temp[MAX_BINT_LEN] = { 0, };
	D_BINT_t a;
	D_BINT_t b;
	D_BINT_t b_temp;
	D_BINT_t c;
	D_BINT_t c_temp;
	D_BINT_t d;
	D_BINT_t q;
	D_BINT_t r;
	D_BINT_t q_temp;
	D_BINT_t r_temp;
	b_temp->dat = b_temp_dat;
	c_temp->dat = c_temp_dat;
	q_temp->dat = q_dat_temp;
	r_temp->dat = r_dat_temp;
	a->dat = a_dat;
	b->dat = b_dat;
	c->dat = c_dat;
	d->dat = d_dat;
	q->dat = q_dat;
	r->dat = r_dat;
	a->sig = POS_SIG;
	b->sig = POS_SIG;
	q->sig = POS_SIG;
	r->sig = POS_SIG;
	int valid = 1;
	int run_num = 0;
	
	
	


	run_num++;
		
	printf("%d ",run_num);
	init_input(a);
	init_input(b);
	//b->len = 2;
	/*for (int i = b->len - 1; i >= 0; i--)
		b->dat[i] = rand_gen();*/
	while ((a->len < b->len) || b->len < 2)
		{
			init_input(a);
			init_input(b);
		}
	/*a->len = 5;
	for (int i = a->len - 1; i >= 0; i--)
		a->dat[i] = rand_gen();*/
	a->sig = POS_SIG;
	b->sig = POS_SIG;
	
	/*if (a->len < b->len)
		b->len--;*/
	/*a->sig = POS_SIG;
	b->sig = POS_SIG;*/
	copy(b_temp, b);
	mpdiv(q, r, a, b);
	copy(q_temp, q);
	copy(r_temp, r);
	mpmul(c_temp, b_temp, q);
	copy(c,c_temp);
	Addition(d, c, r);
	if (is_equal(a, d)==0)
	{
		
		printf("\na\n");
		print_out(a);
		printf("\nb\n");
		print_out(b);
		printf("\nc\n");
		print_out(c);
		printf("\nd\n");
		print_out(d);
		printf("\nq_temp\n");
		print_out(q_temp);
		printf("\nq\n");
		print_out(q);
		printf("\nr\n");
		print_out(r_temp);
		return 0;
	}
	return 1;
	
	
}