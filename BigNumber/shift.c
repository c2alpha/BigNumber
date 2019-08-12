#include"bignum.h"

//u��v�� normalize �ϱ� ���� ��Ʈ ������ �̵�, �� ���� ��������(�ִ� 31��Ʈ�̵�)
LIMB_t ShiftLeft_bit(D_BINT_t temp,D_BINT_t a, LIMB_t shift)
{
	//D_BINT_t temp;
	/*temp->len = a->len;
	temp->sig = a->sig;*/

	LIMB_t  carry, nextcarry, mask, right_shift;
	mask = ~(MASK_WL >> shift);//bit���� ���� carry�� bit�� �޶���.

	right_shift = BITSZ_WL - shift;
	carry = 0;
	for (int i = 0; i < a->len; i++)
	{
		nextcarry = (a->dat[i] & mask) >> right_shift;//���� ��ġ�� ���� ��Ʈ�� ���� ��ġ�� ������Ʈ�� �� ����
		temp->dat[i] = a->dat[i] << shift | carry;//���� ����� �ؿ��� �ٿ���
		carry = nextcarry;
	}
	//y�� ���ؼ��� 0�� return �� ��������(y�� �������� shiftȽ�� ����.)
	//x�� ���ؼ��� �߰����� ������ �ʿ��� �� ����.
	return carry;
				
}
LIMB_t ShiftRight_bit(D_BINT_t temp, D_BINT_t a, LIMB_t shift)
{
	//D_BINT_t temp;
	/*temp->len = a->len;
	temp->sig = a->sig;*/
	
	LIMB_t  carry, nextcarry, mask, left_shift;
	mask = ~(MASK_WL << shift);//bit���� ���� carry�� bit�� �޶���.

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

//v�� u�� �ڸ��� �°� �� ���徿 �̵�. �˰���� step2�� ����
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
		//word���� shift. shift�� 32���� ũ�� �ؾ���
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
	//word ������ shift
	temp->len = a->len;
	if (bit)
	{
		ShiftLeft_bit(temp, a, bit);
		copy(a, temp);
	}
}