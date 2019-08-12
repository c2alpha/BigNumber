#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

int main(void)
{
	srand((unsigned)time(NULL));
	
	//int valid = 1;
	////	int run_num = 0;
	//	/*while (valid)
	//	{
	//		run_num++;
	//		if (run_num % 500000 == 0)
	//			printf("%d ", run_num);
	//		valid=valid_test_div();
	//	}*/
	//int run_num = 0;
	//while (valid)
	//{
	//	LIMB_t a_dat[300] = { 0, };
	//	LIMB_t b_dat[300] = { 0, };
	//	LIMB_t c_dat[300] = { 0, };
	//	LIMB_t d_dat[300] = { 0, };
	//	LIMB_t b_temp_dat[300] = { 0, };
	//	LIMB_t c_temp_dat[300] = { 0, };
	//	LIMB_t q_dat[MAX_BINT_LEN] = { 0, };
	//	LIMB_t r_dat[MAX_BINT_LEN] = { 0, };
	//	LIMB_t q_dat_temp[MAX_BINT_LEN] = { 0, };
	//	LIMB_t r_dat_temp[MAX_BINT_LEN] = { 0, };
	//	D_BINT_t a;
	//	D_BINT_t b;
	//	D_BINT_t b_temp;
	//	D_BINT_t c;
	//	D_BINT_t c_temp;
	//	D_BINT_t d;
	//	D_BINT_t q;
	//	D_BINT_t r;
	//	D_BINT_t q_temp;
	//	D_BINT_t r_temp;
	//	b_temp->dat = b_temp_dat;
	//	c_temp->dat = c_temp_dat;
	//	q_temp->dat = q_dat_temp;
	//	r_temp->dat = r_dat_temp;
	//	a->dat = a_dat;
	//	b->dat = b_dat;
	//	c->dat = c_dat;
	//	d->dat = d_dat;
	//	q->dat = q_dat;
	//	r->dat = r_dat;
	//	a->sig = POS_SIG;
	//	b->sig = POS_SIG;
	//	q->sig = POS_SIG;
	//	r->sig = POS_SIG;
	//	run_num++;
	//	//if (run_num % 500000 == 0)
	//		printf("%d ", run_num);
	//	init_input(a);
	//	a->len = 64;
	//	for (int i = 0; i < a->len; i++)
	//		rand_gen(a);
	//	b->len = 32;
	//	for (int i = 0; i < b->len; i++)
	//		b->dat[i] = rand_gen();
	//	//init_input(b);
	//	//while ((a->len <= b->len))
	//	//{
	//	//	init_input(a);
	//	//	init_input(b);
	//	//}
	//	a->sig = POS_SIG;
	//	b->sig = POS_SIG;
	//	/*if (a->len < b->len)
	//		b->len--;*/
	//		/*a->sig = POS_SIG;
	//		b->sig = POS_SIG;*/
	//	copy(b_temp, b);
	//	mpdiv(q, r, a, b);
	//	copy(q_temp, q);
	//	copy(r_temp, r);
	//	mpmul(c_temp, b_temp, q);
	//	copy(c, c_temp);
	//	Addition(d, c, r);
	//	if (is_equal(a, d) == 0)
	//	{
	//		valid = 0;
	//		printf("\na\n");
	//		print_out(a);
	//		printf("\nb\n");
	//		print_out(b);
	//		printf("\nc\n");
	//		print_out(c);
	//		printf("\nd\n");
	//		print_out(d);
	//		printf("\nq_temp\n");
	//		print_out(q_temp);
	//		printf("\nq\n");
	//		print_out(q);
	//		printf("\nr\n");
	//		print_out(r_temp);
	//	}
	//}

	//valid_test_mul();
	//ext bin을 위한 애들
	//valid_bin_ext();
	
	D_BINT_t a, g, e, g_temp, e_temp;
	LIMB_t a_dat[300] = { 0, };
	LIMB_t g_dat[300] = { 0, };
	LIMB_t e_dat[300] = { 0, };
	LIMB_t g_temp_dat[300] = { 0, };
	D_BINT_t A;
	LIMB_t A_dat[300] = { 0, };
	A->dat = A_dat;
	LIMB_t e_temp_dat[300] = { 0, };
	a->dat = a_dat;
	g->dat = g_dat;
	e->dat = e_dat;
	g_temp->dat = g_temp_dat;
	e_temp->dat = e_temp_dat;
	a->sig = POS_SIG;
	g->sig = POS_SIG;
	e->sig = POS_SIG;
	g->len = 1;
	e->len = 1;
	g->dat[0] = 0xF357055B;
	e->dat[0] = 0x15;

	//init_input(g);
	//printf("g\n");
	//print_out(g);

	//init_input(e);
	//printf("e\n");
	//print_out(e);
	//LIMB_t k = 8;
	//copy(g_temp, g);
	//copy(e_temp, e);
	//LtoR(A, g_temp, e_temp);
	//printf("LtoR\n");
	//print_out(A);
	//copy(g_temp, g);
	//copy(e_temp, e);
	////Mont_exp(a, g, e);
	//SlidingWindow(a, g_temp, e_temp, k);
	//if (is_equal(A, a) == 0)
	//{
	//	printf("Not Equal!!!!\n");
	//	printf("LtoR\n");
	//	print_out(A);
	//	printf("sliding\n");
	//	print_out(a);
	//	/*printf("g\n");
	//	print_out(g);
	//	printf("e\n");
	//	print_out(e);*/
	//}
	//else
	//	printf("Equal!!!\n");
	//

	init_input(g);
	e->sig = POS_SIG;
	LIMB_t k = 5;
	for (int i = 0; i < 10; i++)
	{
		e->len = (i * 5) + 30;
		for (int j = 0; j < e->len; j++)
		{
			e->dat[j] = rand_gen();
		}
		printf("\nexponential size = %d-words\n", e->len);
		START_WATCH;
		for (int i = 0; i < 200; i++)
		{
			copy(g_temp, g);
			copy(e_temp, e);
			SlidingWindow(a, g_temp, e_temp, k);

		}
		STOP_WATCH;
		PRINT_TIME("Window size = 5 ");
		init_input_to_zero(a);
		START_WATCH;
		for (int i = 0; i < 200; i++)
		{
			copy(g_temp, g);
			copy(e_temp, e);
			Mont_exp(a, g_temp, e_temp, k);
		}
		STOP_WATCH;
		PRINT_TIME("Mont_exp ");
		init_input_to_zero(a);
	}
	
	
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("1-ary ");
	//init_input_to_zero(a);*/

	//k = 2;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 2 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("2-ary ");
	//init_input_to_zero(a);*/

	//k = 3;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 3 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("3-ary ");
	//init_input_to_zero(a);*/

	//k = 4;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 4 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("4-ary ");
	//init_input_to_zero(a);*/

	//k = 5;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 5 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("5-ary ");
	//init_input_to_zero(a);*/

	//k = 6;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 6 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("6-ary ");
	//init_input_to_zero(a);*/

	//k = 7;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 7 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("7-ary ");
	//init_input_to_zero(a);*/

	//k = 8;
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	SlidingWindow(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Window size = 8 ");
	//init_input_to_zero(a);
	///*START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("8-ary ");*/
	//
	//START_WATCH;
	//for (int i = 0; i < 500; i++)
	//{
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	Mont_exp(a, g_temp, e_temp, k);

	//}
	//STOP_WATCH;
	//PRINT_TIME("Mont_exp ");




















	///*printf("LtoR\n");
	//print_out(a);*/

	//
	
	//
	////modified_k_ary(A, g_temp, e_temp, k);
	//k = 2;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{
	//	
	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("2-ary");
	///*k = 2;
	//START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 2-ary");*/

	//k = 3;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("3-ary");
	//k = 3;
	///*START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 3-ary");*/

	//k = 4;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("4-ary");
	//k = 4;
	///*START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 4-ary");*/


	//k = 5;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("5-ary");
	//k = 5;
	///*START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 5-ary");*/


	//k = 6;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("6-ary");
	//k = 6;
	///*START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 6-ary");*/

	//k = 7;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("7-ary");
	//k = 7;
	///*START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	modified_k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("modified 7-ary");*/

	//k = 8;
	//START_WATCH;
	//for (int i = 0; i < 100; i++)
	//{

	//	copy(g_temp, g);
	//	copy(e_temp, e);
	//	k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("8-ary");
	//k = 8;
	/*START_WATCH;
	for (int i = 0; i < 1000; i++)
	{

		copy(g_temp, g);
		copy(e_temp, e);
		modified_k_ary(A, g_temp, e_temp, k);
	}
	STOP_WATCH;
	PRINT_TIME("modified 8-ary");*/



	//k = 9;
	//START_WATCH;
	//for (int i = 0; i < 1000; i++)
	//{

	//copy(g_temp, g);
	//copy(e_temp, e);
	//k_ary(A, g_temp, e_temp, k);
	//}
	//STOP_WATCH;
	//PRINT_TIME("8-ary");









		/*k = 9;
		copy(g_temp, g);
		copy(e_temp, e);
		k_ary(A, g_temp, e_temp, k);

		k = 10;
		copy(g_temp, g);
		copy(e_temp, e);
		k_ary(A, g_temp, e_temp, k);

		k = 11;
		copy(g_temp, g);
		copy(e_temp, e);
		k_ary(A, g_temp, e_temp, k);
		k = 12;
		copy(g_temp, g);
		copy(e_temp, e);
		k_ary(A, g_temp, e_temp, k);
		k = 13;
		copy(g_temp, g);
		copy(e_temp, e);
		k_ary(A, g_temp, e_temp, k);*/

	/*printf("%d-ary\n",k);
	print_out(A);
	if (is_equal(A, a))
		printf("\n\nEQUAL!!!!!!!!!!!!!!!!!!\n\n");
	else
		printf("\n\nNOT EQUAL@@@@@@@@@@@@@@@@@\n\n");*/
	
	
			

	



	return 0;
}


