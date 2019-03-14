#include "bignum.h"

/*==================================================================
 * �� �� �� : spmul
 * �Լ����� : 1word ������ ����
 * �Ķ���� : 1word�� ���� ���꿡 ����� in1,in2/ �� ����� ������ u,v
 * ��    �� : none
 * out = in1 * in2
 * ����� 2word�� �� �� �ִ�.
==================================================================*/


//in1=(x1*b)+x0 in2=(y1*b)+y0  b=2^16 (32��Ʈ ǥ���� 16��Ʈ ǥ������ �ٲ�.)
void spmult(LIMB_t* u,LIMB_t* v, LIMB_t in1, LIMB_t in2)
{
	LIMB_t carry;
	LIMB_t x1, x0, y1, y0;
	//x,y�� ���� 16��Ʈ ����
	x0 = in1 & MASK_RHW;
	y0 = in2 & MASK_RHW;
	//x,y�� ���� 16��Ʈ ����
	x1 = (in1 & MASK_LHL) >> BITSZ_HL;
	y1 = (in2 & MASK_LHL) >> BITSZ_HL;

	//xi , yi ���� 16��Ʈ�� ǥ���ϹǷ�, �� ���� ���� ����� 32��Ʈ ������ �� ǥ����.
	LIMB_t mid_val1, mid_val2, mid_val3, mid_val4;
	mid_val1 = x0 * y0;
	mid_val2 = x1 * y0;
	mid_val3 = x0 * y1;
	mid_val4 = x1 * y1;
	
	
	*v = mid_val1;
	LIMB_t temp = mid_val2 + mid_val3;//�������� overflow ���ɼ� ����
	if (temp < mid_val2)//mid_val2 ���� �۴� or mid_val3���� �۴� � ������ �ص� ��� ����.
		carry = 1;//mid_val4�� ���� 16��Ʈ�� �������� �� carry
	else
		carry = 0;

	
	carry = (carry << BITSZ_HL) + ((temp&MASK_LHL)>>BITSZ_HL)
		;//������ �߻��� carry�� mid_val4�� ���� 16��Ʈ��
		 //�������� �ϰ�, mid_val2+mid_val3�� ���� 16��Ʈ��
		 //mid_val4�� ���� 16��Ʈ�� �������� ��.=> �װ� �ѹ��� ǥ��

	*v = *v + ((temp&MASK_RHW) << BITSZ_HL);//mid_val2+mid_val3�� ���� 16��Ʈ��
											//x0 * y0�� ����16��Ʈ�� �������� ��.
	if (*v < ((temp&MASK_RHW) << BITSZ_HL))
		carry++;

	*u = mid_val4 + carry;


}