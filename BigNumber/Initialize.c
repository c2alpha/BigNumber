#include "bignum.h"
/*==================================================================
 * �Լ��� : init_input
 * �Լ� ���� : �Է����� ���� �����鿡 ���� ����
 * �Է� : ���꿡 �̿�Ǳ� ���Ͽ� �ʱ�ȭ�� ���� 2�� in1,in2
 * ��� : none
==================================================================*/
void init_input(D_BINT_t in1, D_BINT_t in2)
{
	in1->sig = (rand() % 3) - 1;
	in2->sig = (rand() % 3) - 1;

	in1->len = (rand() % 300) + 1;
	in2->len = (rand() % 300) + 1; //�ּ� ���̸� 1�� ����.


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