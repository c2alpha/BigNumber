#include "bignum.h"
/*==================================================================
 * 함수명 : init_input
 * 함수 설명 : 입력으로 들어온 변수들에 값을 지정
 * 입력 : 연산에 이용되기 위하여 초기화될 변수 2개 in1,in2
 * 출력 : none
==================================================================*/
void init_input(D_BINT_t in1, D_BINT_t in2)
{
	in1->sig = (rand() % 3) - 1;
	in2->sig = (rand() % 3) - 1;

	in1->len = (rand() % 300) + 1;
	in2->len = (rand() % 300) + 1; //최소 길이를 1로 제한.


	for (int i = in1->len - 1; i >= 0; i--)
		in1->dat[i] = rand_gen();
	for (int i = in2->len - 1; i >= 0; i--)
		in2->dat[i] = rand_gen();
	/*printf("input data : \n");
	printf("\ninput1 \n");
	print_out(in1);
	printf("\ninput2 \n");
	print_out(in2);
	printf("\n\n\n");*/

}