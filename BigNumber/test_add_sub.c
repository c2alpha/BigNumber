#include"bignum.h"
/*==================================================================
 * 함수명 : valid_test
 * 함수 설명 : 다른 함수들이 잘 구현됐는지 test
 * 입력 : none
 * 출력 : none
==================================================================*/
void valid_test()
{

	LIMB_t a_dat[300] = { 0, };
	LIMB_t b_dat[300] = { 0, };
	LIMB_t c_dat[MAX_BINT_LEN] = { 0, };
	LIMB_t d_dat[MAX_BINT_LEN] = { 0, };
	D_BINT_t a;
	D_BINT_t b;
	D_BINT_t c;
	D_BINT_t d;
	
	a->dat = a_dat;
	b->dat = b_dat;
	c->dat = c_dat;
	d->dat = d_dat;

	int valid = 1;
	int run_num = 0;//잘 돌아가는지 확인용 의미 x
	int k = 0;//잘 돌아가는지 확인용 의미 x
	while (valid)
	{

		init_input(a, b);
		run_num++;
		if ((run_num % 100000) == 0)
			printf("%d \n",k++);
		int check = 0;
		Addition(c, a, b);
		Subtraction(d, c, a);
		if (d->sig != b->sig)//sign이 다르면 실패!
		{
			valid = 0;
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			printf("\ninput1 \n");
			print_out(a);
			printf("\ninput2 \n");
			print_out(b);
			printf("\noutput \n");
			print_out(c);
			printf("\n\n");
			print_out(d);
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			break;
		}
		//sign이 0인 경우엔 데이터와 길이 모두 신경쓰지 않고 0 이므로
		//zero sig가 아닌 경우에만 데이터를 비교한다.						
		if (d->sig != ZERO_SIG)
		{
			for (int i = 0; i < b->len; i++)
			{
				check = d->dat[i] - b->dat[i] + check;
			}
		}
		if (check != 0)
		{
			valid = 0;
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
			printf("\ninput1 \n");
			print_out(a);
			printf("\ninput2 \n");
			print_out(b);
			printf("\noutput \n");
			print_out(c);
			printf("\n\n");
			print_out(d);
			printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
		}
		memset(a_dat, 0, sizeof(LIMB_t) * 300);
		memset(b_dat, 0, sizeof(LIMB_t) * 300);
		memset(c_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
		memset(d_dat, 0, sizeof(LIMB_t) * MAX_BINT_LEN);
	}
	
}