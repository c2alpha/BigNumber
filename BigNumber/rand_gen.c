#include "bignum.h"
/*==================================================================
 * �Լ��� : rand_gen
 * �Լ� ���� : random ���� ����
 * �Է� : none
 * ��� : none
==================================================================*/
LIMB_t rand_gen()
{
	LIMB_t a = 0;
	LIMB_t temp = 0;
	if (_IS_16BIT_FAST_ == 1)
		a = (rand() & 0xff) << 8 | (rand() & 0xff);
	else if (_IS_32BIT_FAST_ == 1)
		a = (rand() & 0xff) << 24 | (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | (rand() & 0xff);
	else if (_IS_64BIT_FAST_ == 1)
	{
		temp = (rand() & 0xff) << 24 | (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | (rand() & 0xff);
		a = temp << 24 | (rand() & 0xff) << 24 | (rand() & 0xff) << 16 | (rand() & 0xff) << 8 | (rand() & 0xff);
	}
	return a;
}