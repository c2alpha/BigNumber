#include"bignum.h"

//u와v를 normalize 하기 위해 비트 단위로 이동, 한 워드 내에서만(최대 31비트이동)
LIMB_t ShiftLeft_bit(D_BINT_t temp,D_BINT_t a, LIMB_t shift)
{
	//D_BINT_t temp;
	/*temp->len = a->len;
	temp->sig = a->sig;*/

	LIMB_t  carry, nextcarry, mask, right_shift;
	mask = ~(MASK_WL >> shift);//bit수에 따라 carry될 bit가 달라짐.

	right_shift = BITSZ_WL - shift;
	carry = 0;
	for (int i = 0; i < a->len; i++)
	{
		nextcarry = (a->dat[i] & mask) >> right_shift;//현재 위치의 상위 비트는 다음 위치의 하위비트가 될 것임
		temp->dat[i] = a->dat[i] << shift | carry;//위의 결과를 밑에다 붙여줌
		carry = nextcarry;
	}
	//y에 대해서는 0이 return 될 것이지만(y를 기준으로 shift횟수 정함.)
	//x에 대해서는 추가적인 공간이 필요할 수 있음.
	return carry;
				
}
LIMB_t ShiftRight_bit(D_BINT_t temp, D_BINT_t a, LIMB_t shift)
{
	//D_BINT_t temp;
	/*temp->len = a->len;
	temp->sig = a->sig;*/
	
	LIMB_t  carry, nextcarry, mask, left_shift;
	mask = ~(MASK_WL << shift);//bit수에 따라 carry될 bit가 달라짐.

	left_shift = BITSZ_WL - shift;
	carry = 0;
	for (int i = a->len-1; i >= 0; i--)
	{
		nextcarry = (a->dat[i] & mask) << left_shift;
		temp->dat[i] = a->dat[i] >> shift | carry;
		carry = nextcarry;
	}
	if (temp->dat[temp->len - 1] == 0)
		temp->len--;
	
	
	return carry;

}

//v를 u의 자리에 맞게 한 워드씩 이동. 알고리즘상 step2에 속함
void ShiftLeft_word(D_BINT_t a,LIMB_t len)
{
	D_BINT_t temp;
	LIMB_t diff;
	LIMB_t tempary[MAX_BINT_LEN] = { 0, };
	temp->dat = tempary;
	temp->sig = a->sig;
	temp->len = len;
	diff = len - a->len;
	for (int i = a->len - 1; i >= 0; i--)
	{
		temp->dat[i + diff] = a->dat[i];
	}
	for (int i = diff - 1; i >= 0; i--)
	{
		temp->dat[i] = 0;
	}
	copy(a, temp);

}

void ShiftLeft(D_BINT_t a, D_BINT_t b, int shift)
{
	LIMB_t dump;
	LIMB_t word, bit;
	D_BINT_t temp;
	LIMB_t temp_dat[300] = { 0, };
	temp->sig = b->sig;
	temp->dat = temp_dat;
	a->sig = b->sig;
	int i;
	if (shift >= BITSZ_WL)
	{
		//word단위 shift. shift가 32보다 크면 해야함
		word = shift / BITSZ_WL;
		for (i = b->len - 1; i >= 0; i--)
		{
			if (i >= word)
				a->dat[i] = b->dat[i - word];

			else
				a->dat[i] = 0;
		}
		a->len = a->len + word;
	}
	else
		copy(a, b);
	bit = shift % BITSZ_WL;
	//word 내에서 shift
	temp->len = a->len;
	if (bit)
	{
		ShiftLeft_bit(temp, a, bit);
		copy(a, temp);
	}
}