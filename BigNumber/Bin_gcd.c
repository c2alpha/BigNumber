#include"bignum.h"
//#define is_even(x) (!((x->dat[0])&RLSB_ONE))

LIMB_t bin_gcd(D_BINT_t gcd, D_BINT_t x, D_BINT_t y)
{
	LIMB_t k = 0;
	D_BINT_t x_temp, y_temp, t;
	LIMB_t x_temp_dat[300] = { 0, };
	LIMB_t y_temp_dat[300] = { 0, };
	LIMB_t t_dat[300] = { 0, };
	t->dat = t_dat;
	x_temp->dat = x_temp_dat;
	y_temp->dat = y_temp_dat;
	gcd->len = 1;
	gcd->sig = POS_SIG;
	gcd->dat[0] = 1;
	//x>=y 조건 만족시기키 위함
	if (compare2(x, y) < 0)
	{
		copy(t, x);
		init_input_to_zero(x);
		copy(x, y);
		init_input_to_zero(y);
		copy(y, t);
		init_input_to_zero(t);
	}

	//step 2 x,y가 가지고 있는 2를 다 뽑아냄
	while (is_even(x) && is_even(y))
	{
		/*copy(x_temp, x);
		copy(y_temp, y);
		ShiftRight_bit(x, x_temp, 1);
		ShiftRight_bit(y, y_temp, 1);*/
		ShiftRight_bit(x, x, 1);
		ShiftRight_bit(y, y, 1);
		k++;
		/*init_input_to_zero(x_temp);
		init_input_to_zero(y_temp);*/
	}

	//step 3
	while (x->sig != ZERO_SIG)
	{
		//step 3.1
		while (is_even(x))
		{
		/*	copy(x_temp, x);
			ShiftRight_bit(x, x_temp, 1);*/
			ShiftRight_bit(x, x, 1);
			//init_input_to_zero(x_temp);
		}
		//step3.2
		while (is_even(y))
		{
			/*copy(y_temp, y);
			ShiftRight_bit(y, y_temp, 1);*/
			ShiftRight_bit(y, y, 1);
			//init_input_to_zero(y_temp);
		}
		//step 3.3
		if (compare(x, y))
			Subtraction(t, y, x);
		else
			Subtraction(t, x, y);
		ShiftRight_bit(t, t, 1);
		//step 3.4
		if (!compare(x, y))
		{
			init_input_to_zero(x);
			copy(x, t);
			init_input_to_zero(t);
		}
		else
		{
			init_input_to_zero(y);
			copy(y, t);
			init_input_to_zero(t);
		}
		
	}
	ShiftLeft(gcd, y, k);
	
	return 0;
	

}