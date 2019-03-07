#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "bignum.h"




int main(void)
{
	srand((unsigned)time(NULL));
	
	

	valid_test();
	//LIMB_t a_dat[300] = { 0, };
	//LIMB_t b_dat[300] = { 0, };
	//LIMB_t raw_a_dat[300] = { 0, };
	//LIMB_t raw_b_dat[300] = { 0, };
	//LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	//LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	//D_BINT_t a;
	//D_BINT_t b;
	//D_BINT_t c;
	//D_BINT_t d;
	//D_BINT_t raw_a;
	//D_BINT_t raw_b;
	////BINT_t b;
	////LIMB_t b_dat[6];
	////LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	//a->dat = a_dat;
	//b->dat = b_dat;
	//c->dat = c_dat;
	//d->dat = d_dat;
	//raw_a->dat = raw_a_dat;
	//raw_b->dat = raw_b_dat;
	//init_input(a, b,raw_a,raw_b);
	//
	//
	//gen_add(c, a, b);
	////gen_sub(c, a, b);
	//gen_sub(d, c, a);
	//
	//printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	//printf("\ninput1 \n");
	//print_out(a);
	//printf("\ninput2 \n");
	//print_out(b);
	//printf("\noutput \n");
	//print_out(c);
	//printf("\n\n");
	//print_out(d);
	//printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	//
	
	//test_AddAndSub(c, a, b);

	/*BINT initialization choice*/

	


	
	//a->sig = POS_SIG;
	//a->len = 1;
	//b->sig = POS_SIG;
	//b->len = 2;		
	//a->len = max(a->len, b->len);/*계산의 편의를 위해 input 변수들의 사이즈를 맞춰줌. 짧은 input의 나머지는 0으로 채울 예정.*/
	//b->len = max(a->len, b->len);

	//a->dat = (P_LIMB_t)malloc(sizeof(LIMB_t)*(a->len));
	//assert(a->dat != NULL);
	//for (int i = 0; i < a->len; i++)
	//	a->dat[i] = 0;
	//	
	//b->dat = (P_LIMB_t)malloc(sizeof(LIMB_t)*(b->len));
	//assert(b->dat != NULL);
	//for (int i = 0; i < b->len; i++)
	//	b->dat[i] = 0;
	//
	//c->len = max(a->len, b->len);
	//c->dat = (P_LIMB_t)malloc(sizeof(LIMB_t)*(c->len));
	//assert(c->dat != NULL);
	//for (int i = 0; i < c->len; i++)
	//	c->dat[i] = 0;
	//
	///*data input space(start)*/
	//a->dat[1] = 0x0;
	//a->dat[0] = 0x5;
	//b->dat[1] = 0x0;
	//b->dat[0] = 0x30;
	///*data input space(end)*/

	//compare(a, b);
	////mpadd(c, a, b);
	//mpsub(c, a, b);
	//
	//for (int i = c->len - 1; i >= 0; i--)
	//{
	//	
	//	printf("%08X ", c->dat[i]);
	//}
	






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

