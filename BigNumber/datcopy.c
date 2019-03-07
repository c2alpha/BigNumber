#include "bignum.h"
/*==================================================================
 * 함수명 : copy
 * 함수 설명 : 내용을 전부 복사
 * 입력 : 내용을 복사할 목적지 des, 복사될 내용을 담은 sta
 * 출력 : none
==================================================================*/
void copy(D_BINT_t des,D_BINT_t sta)
{	
	des->sig = sta->sig;
	des->len = sta->len;
	memcpy(des->dat, sta->dat, sizeof(LIMB_t)*des->len);
	/*for (int i = 0; i < des->len; i++)
		des->dat[i] = sta->dat[i];*/
}