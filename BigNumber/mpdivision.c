#include "bignum.h"

//void mpdivide(D_BINT_t q, D_BINT_t r, D_BINT_t u, D_BINT_t v)
//{
//	LIMB_t shift;
//	LIMB_t bitmask, overflow;
//	LIMB_t qhat, rhat, t[2];
//	D_BINT_t temp1, temp2;
//	LIMB_t temp1_dat[300] = { 0, };
//	LIMB_t temp2_dat[300] = { 0, };
//	int qhatOK, cmp;
//	LIMB_t shift_word;
//	temp1->dat = temp1_dat;
//	temp2->dat = temp2_dat;
//	q->sig = POS_SIG;
//	r->sig = POS_SIG;
//	q->len = u->len - v->len + 1;
//	r->len = v->len;
//	memset(q->dat, 0, sizeof(LIMB_t)*q->len);
//	memset(r->dat, 0, sizeof(LIMB_t)*r->len);
//	if (v->sig == ZERO_SIG)
//		return -1;	/* Divide by 0 => 오류*/
//
//	if (u->len < v->len)//v의 길이가 u의 길이보다 길다..( 즉 나누는 수가 더 컸다)
//	{
//		copy(r, v);
//		return 0;
//	}
//
//	if (u->len == v->len)//v와 u의 길이가 같다
//	{
//		cmp = compare2(u, v);
//		if (cmp < 0)
//		{	// v > u
//			copy(r, u);
//			return 0;
//		}
//		else if (cmp == 0)
//		{	// v = u
//			q->len = 1;
//			q->dat[0] = 1;
//			return 0;
//		}
//	}
//	if ((v->len == 1) && (v->dat[0] == 1))
//	{
//		//v=1;
//		copy(q, u);
//		return 0;
//	}
//
//	bitmask = LMSB_ONE;
//	for (shift = 0; shift < BITSZ_WL; shift++)
//	{
//		if (v->dat[v->len - 1] & bitmask)
//			break;
//		bitmask >>= 1;
//	}
//
//	overflow = ShiftLeft_bit(v, v, shift);
//
//	overflow = ShiftLeft_bit(r, u, shift);
//	if (overflow)//바로 위 과정에서 overflow가 발생했다면 그걸 담을 공간이 필요하다
//		copy(temp1, r);
//	
//	t[0] = overflow;//u를 shift하게 되면 추가 워드가 생길 수 있다.
//	for (int i = u_temp->len - 1; i >= v->len; i--)
//	{
//
//	}
//}