#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "bignum.h"




int main(void)
{
	srand((unsigned)time(NULL));
	
	

	valid_test();
	/*LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	D_BINT_t a;
	D_BINT_t b;
	D_BINT_t c;
	D_BINT_t d;
	*/
	/* Extreme case */
	/*a->len = 11;
	b->len = 1;
	a->sig = POS_SIG;
	b->sig = NEG_SIG;

	a_dat[0] = 0xffffffff;
	a_dat[1] = 0xffffffff;
	a_dat[2] = 0xffffffff;
	a_dat[3] = 0xffffffff;
	a_dat[4] = 0xffffffff;
	a_dat[5] = 0xffffffff;
	a_dat[6] = 0xffffffff;
	a_dat[7] = 0xffffffff;
	a_dat[8] = 0xffffffff;
	a_dat[9] = 0xffffffff;
	a_dat[10] = 0xffffffff;
	b_dat[0] = 0x1;*/
	//b_dat[1] = 0x2;
	/*b_dat[1] = 0xffffffff;
	b_dat[2] = 0xffffffff;
	b_dat[3] = 0xffffffff;
	b_dat[4] = 0xffffffff;
	b_dat[5] = 0xffffffff;
	b_dat[6] = 0xffffffff;
	b_dat[7] = 0xffffffff;
	b_dat[8] = 0xffffffff;
	b_dat[9] = 0xffffffff;
	b_dat[10] = 0xffffffff;*/
	
	
	//a->dat = a_dat;
	//b->dat = b_dat;
	//c->dat = c_dat;
	//d->dat = d_dat;


	////
	//////general case
	//init_input(a, b);

	//Addition(c, a, b);
	//Subtraction(d, c, a);
	//
	//printf("#########################################################\n");
	//printf("(a)\n");
	//print_out(a);
	//printf("(b)\n");
	//print_out(b);
	//printf("(c = a + b)\n");
	//print_out(c);
	//printf("(d = c - a  <=> d = b)\n");
	//print_out(d);
	//printf("#########################################################\n");
	
	
	//test_AddAndSub(c, a, b);

	/*BINT initialization choice*/
			   

	/*
	b.sig = NEG_SIG;
	b.len = 6;
	b.dat = b_dat;
	*/

	/*
	add(c, a, b);
	*/

	return 0;
}

