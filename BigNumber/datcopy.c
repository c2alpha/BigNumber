#include "bignum.h"
/*==================================================================
 * �Լ��� : copy
 * �Լ� ���� : ������ ���� ����
 * �Է� : ������ ������ ������ des, ����� ������ ���� sta
 * ��� : none
==================================================================*/
void copy(D_BINT_t des,D_BINT_t sta)
{	
	des->sig = sta->sig;
	des->len = sta->len;
	memcpy(des->dat, sta->dat, sizeof(LIMB_t)*des->len);
	/*for (int i = 0; i < des->len; i++)
		des->dat[i] = sta->dat[i];*/
}