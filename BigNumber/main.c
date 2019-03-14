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
	//valid_test();
	//valid_test_mul();
	//mult test-start

	LIMB_t a_dat[300] = { 0, };
	//LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	//LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	D_BINT_t a;
	//D_BINT_t b;
	D_BINT_t c;
	//D_BINT_t d;
	a->dat = a_dat;
	//b->dat = b_dat;
	c->dat = c_dat;
	init_input(a);
	START_WATCH;
	for (int i = 0; i < 300000; i++)
		mpmul(c, a, a);
	STOP_WATCH;
	PRINT_TIME("mul 시간임 ");
	START_WATCH;
	for (int i = 0; i < 300000; i++)
		square(c, a);
	STOP_WATCH;
	PRINT_TIME("square 시간임 ")
	//square(c, a);
	//d->dat = d_dat;
	////B928E77A 80A24B0D C41C4818
	//a_dat[0] = 0xAD70E1DC;
	//a_dat[1] = 0xCEA0FBE3;
	//a_dat[2] = 0xD436FB5F;
	//a->len = 3;
	//b->len = 3;
	//b->dat = b_dat;
	//b_dat[0] = 0x3F2E932A;
	//b_dat[1] = 0xCEA0FBE4;
	//b_dat[2] = 0xD436FB5F;
	//a->sig = NEG_SIG;
	//b->sig = NEG_SIG;
	//c->dat = c_dat;
	//multi(c, a, b);
	//printf("#########################################################\n");
			//printf("(a)\n");
			//print_out(a);
	//		printf("(b)\n");
	//		print_out(b);
			//printf("(c = a * a)\n");
			//print_out(c);
	//		//printf("(d = a^2)\n");
	//		//print_out(c);
	//		printf("#########################################################\n");
	//FC792991 2189B6EB 4AA9CD8B
	//2FDCA641
	//66E14C26 3A48B070 3602B312
	//AD97E9EF 5A559D4A
	/*a->len = 3;
	b->len = 3;
	a->dat = a_dat;
	b->dat = b_dat;
	a_dat[0] = 0xffffffff;
	a_dat[1] = 0xffffffff;
	a_dat[2] = 0xffffffff;
	b_dat[0] = 0xfff515ff;
	b_dat[1] = 0xfffeafff;
	b_dat[2] = 0x15751fff;
	a->sig = POS_SIG;
	b->sig = POS_SIG;
	c->dat = c_dat;*/
	//int valid = 20;
	//int check = 0;
	//int num = 0;
	//while (valid)
	//{
	//	num++;
	////	valid--;
	//	init_input(a);
	//	//init_input(b);
	//	multi(c, a, a);
	//	square(d, a);
	//	if (num % 10000 == 0)
	//		printf("+ ");
	//	if (d->sig != c->sig)
	//	{
	//		valid = 0;
	//		printf("#########################################################\n");
	//		printf("(a)\n");
	//		print_out(a);
	//		//printf("(b)\n");
	//	//	print_out(b);
	//		printf("(c = a * a)\n");
	//		print_out(c);
	//		printf("(d = a^2)\n");
	//		print_out(c);
	//		printf("#########################################################\n");
	//	}
	//	for (int i = 0; i < c->len; i++)
	//	{
	//		check = c->dat[i] - d->dat[i];
	//	}
	//	if (check != 0)
	//	{
	//		valid = 0;
	//		printf("#########################################################\n");
	//		printf("(a)\n");
	//		print_out(a);
	//		//printf("(b)\n");
	//		print_out(b);
	//		printf("(c = a * a)\n");
	//		print_out(c);
	//		printf("(d = a^2)\n");
	//		print_out(c);
	//		printf("#########################################################\n");
	//	}
	//}


	/*LIMB_t a;
	LIMB_t b;
	LIMB_t c[2];
	a = 0xad525;
	b = 0xf32ae5c1;
	spmult(c, a, b);
	printf("a=%08x\n", a);
	printf("b=%08x\n", b);
	printf("c=");
	for (int i = 1; i >= 0; i--)
	{
		printf("%08x ", c[i]);
	}*/

		/*printf("#########################################################\n");
		printf("(a)\n");
		print_out(a);
		printf("(b)\n");
		print_out(b);
		printf("(c = a * b)\n");
		print_out(c);
		printf("#########################################################\n");
	*/

	//mult test-end

	//valid_test();
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
	
	
	

	

	return 0;
}


