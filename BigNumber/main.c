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
	/*LIMB_t qhat;
	LIMB_t rhat;
	LIMB_t u[2], v;
	u[1] = 0xffffffff;
	u[0] = 0xffffffff;
	v = 0xffffffff;
	spdiv(&qhat, &rhat, u, v);
	printf("%08X,  %08X",qhat, rhat);*/
	int valid = 1;
//	int run_num = 0;
	/*while (valid)
	{
		run_num++;
		if (run_num % 500000 == 0)
			printf("%d ", run_num);
		valid=valid_test_div();
	}*/
	int run_num = 0;
	while (valid)
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
		run_num++;
		if(run_num%500000==0)
			printf("%d ",run_num);
		init_input(a);
		/*a->len = 28;
		for (int i = 0; i < a->len; i++)
			rand_gen(a);*/
		/*b->len = 1;
		for (int i = 0; i < b->len; i++)
			b->dat[i] = rand_gen();*/
		init_input(b);
		while ((a->len <= b->len) )
		{
			init_input(a);
			init_input(b);
		}
		
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
		copy(c, c_temp);
		Addition(d, c, r);
		if (is_equal(a, d) == 0)
		{
			valid = 0;
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
		}
		
	}
	
	LIMB_t in1_dat[300] = { 0, };
	LIMB_t in2_dat[300] = { 0, };
	LIMB_t qua_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t rem_dat[MAX_BINT_LEN] = { 0, };
	//LIMB_t m_dat[300] = { 0, };
	////LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	D_BINT_t in1;
	D_BINT_t in2;
	D_BINT_t qua;
	D_BINT_t rem;
	in1->dat = in1_dat;
	in2->dat = in2_dat;
	qua->dat = qua_dat;
	rem->dat = rem_dat;
	in1->len = 1;
	in2->len = 1;
	in1->sig = POS_SIG;
	in2->sig = POS_SIG;
	in1->dat[6] = 0xFFFFFFFF;
	in1->dat[5] = 0xFFFFFFFF;
	in1->dat[4] = 0xFFFFFFFF;
	in1->dat[3] = 0xFFFFFFFF;
	in1->dat[2] = 0xFFFFFFFF;
	in1->dat[1] = 0xFFFFFFFF;
	in1->dat[0] = 0xFFFFFFFe;
	in2->dat[1] = 0xFFFFFFFF;
	in2->dat[0] = 0xFFFFFFFF;
	//D_BINT_t m;
	//////D_BINT_t d;
	//a->sig = POS_SIG;
	//b->sig = POS_SIG;
	//q->sig = POS_SIG;
	//r->sig = POS_SIG;
	//m->sig = POS_SIG;
	//a->dat = a_dat;
	//b->dat = b_dat;
	//q->dat = q_dat;
	//r->dat = r_dat;
	//m->dat = m_dat;
	//m->len = 2;
	//a->len = 4;
	//b->len = 2;
	
	//a->dat[6] = 0x9b63b038;
	//a->dat[5] = 0x1e19cd76;
	//a->dat[4] = 0xaca45476;
	/*a->dat[3] = 0xC0F3F7BF;
	a->dat[2] = 0xDA65A4F4;
	a->dat[1] = 0xC63B8B43;
	a->dat[0] = 0x18D16CF4;*/
	//a->dat[0] = 0x1245CA12;
	//b->dat[3] = 0xD8901E1F;
	//b->dat[2] = 0xF1BA671A;
	/*b->dat[1] = 0x83BBED23;
	b->dat[0] = 0xF4888CA4;
	m->dat[1] = 0xfec3917a;
	m->dat[0] = 0xfed3294a;*/
	//c_mod(a, b, m);

	/*D_BINT_t in1, in2, out;
	LIMB_t in1_dat[300] = { 0, };
	LIMB_t in2_dat[300] = { 0, };
	LIMB_t out_dat[300] = { 0, };
	in1->dat = in1_dat;
	in2->dat = in2_dat;
	out->dat = out_dat;
	in1->sig = POS_SIG;
	in2->sig = POS_SIG;
	in1->len = 4;
	in2->len = 2;
	in1->dat[3] = 0xd6bdd556;
	in1->dat[2] = 0xe7a50d20;
	in1->dat[1] = 0xe2c12c2a;
	in1->dat[0] = 0x2a3cde68;
	in2->dat[2] = 0x6909c48a;
	in2->dat[1] = 0x88E864FD;
	in2->dat[0] = 0xC084E8D9;
	
	Addition(out, in1, in2);
	printf("\nasdzvafasfaf\n\n");
	print_out(out);*/

	//a->dat[3] = 0x788CC3F6;
	//a->dat[2] = 0x455328DE;
	//a->dat[1] = 0x8EBB68EF;
	//a->dat[0] = 0x22E4785F;
	//
	////b->dat[3] = 0xD8901E1F;
	////b->dat[2] = 0xF1BA671A;
	//b->dat[1] = 0x9BB261D6;
	//b->dat[0] = 0x8ECC4C80;


	//a->dat[4] = 0xffffffff;
	/*a->dat[3] = 0xffffffff;
	a->dat[2] = 0xffffffff;
	a->dat[1] = 0xffffffff;
	a->dat[0] = 0xffffffff;

	b->dat[1] = 0xffffffff;
	b->dat[0] = 0xffffffff;
*/

	//5cdfea5823ae6789f57ea369ced357a4
	//4234000012345678
	/*a->dat[3] = 0x5cdfea58;
	a->dat[2] = 0x23ae6789;
	a->dat[1] = 0xf57ea369;
	a->dat[0] = 0xced357a4;

	b->dat[1] = 0x42340000;
	b->dat[0] = 0x12345678;*/

	//안되는거
	/*a->dat[4] = 0xf45817de;
	a->dat[3] = 0x5cdfea58;
	a->dat[2] = 0x23ae6789;
	a->dat[1] = 0xf57ea369;
	a->dat[0] = 0xced357a4;
	b->dat[1] = 0x42340000;
	b->dat[0] = 0x12345678;*/
	//spdiv(q, r, a, b);
	mpdiv(qua, rem, in1, in2);
	printf("in1\n");
	print_out(in1);
	printf("in2\n");
	print_out(in2);
	printf("몫\n");
	print_out(qua);
	printf("나머지\n");
	print_out(rem);




	//init_input(a);
	//START_WATCH;
	//for (int i = 0; i < 300000; i++)
	//	mpmul(c, a, a);
	//STOP_WATCH;
	//PRINT_TIME("mul 시간임 ");
	//START_WATCH;
	//for (int i = 0; i < 300000; i++)
	//	square(c, a);
	//STOP_WATCH;
	//PRINT_TIME("square 시간임 ")
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


