#include "bignum.h"

void ext_bin_gcd(D_BINT_t gcd, D_BINT_t x, D_BINT_t y, D_BINT_t a, D_BINT_t b)
{
	LIMB_t k = 0;
	D_BINT_t u, v, temp1, temp2;
	LIMB_t u_dat[300] = { 0, };
	LIMB_t v_dat[300] = { 0, };
	LIMB_t temp1_dat[300] = { 0, };
	LIMB_t temp2_dat[300] = { 0, };
	u->dat = u_dat;
	v->dat = v_dat;
	temp1->dat = temp1_dat;
	temp2->dat = temp2_dat;
	D_BINT_t A, B, C, D;
	LIMB_t A_dat[300] = { 0, };
	LIMB_t B_dat[300] = { 0, };
	LIMB_t C_dat[300] = { 0, };
	LIMB_t D_dat[300] = { 0, };
	A->dat = A_dat;
	B->dat = B_dat;
	C->dat = C_dat;
	D->dat = D_dat;
	gcd->len = 1;
	gcd->sig = POS_SIG;
	gcd->dat[0] = 1;
	A->len = 1;
	B->len = 1;
	C->len = 1;
	D->len = 1;

	//step 2
	while (is_even(x) && is_even(y))
	{
		ShiftRight_bit(x, x, 1);
		ShiftRight_bit(y, y, 1);
		k++;
	}

	//step 3
	copy(u, x);
	copy(v, y);
	A->dat[0] = 1;
	B->dat[0] = 0;
	C->dat[0] = 0;
	D->dat[0] = 1;
	A->sig = POS_SIG;
	B->sig = ZERO_SIG;
	C->sig = ZERO_SIG;
	D->sig = POS_SIG;
	int num = 0;
Label:
	
	//step 4
	while (is_even(u))
	{
		//step 4.1
		ShiftRight_bit(u, u, 1);
		
		//step 4.2
		if (is_even(A) && is_even(B))
		{
			ShiftRight_bit(A, A, 1);
			ShiftRight_bit(B, B, 1);
		}
		else
		{
			/*Addition(temp1, A, y);
			ShiftRight_bit(A, temp1, 1);
			Subtraction(temp2, B, x);
			ShiftRight_bit(B, temp2, 1);
			init_input_to_zero(temp1);
			init_input_to_zero(temp2);*/
			Addition(A, A, y);
			ShiftRight_bit(A, A, 1);
			Subtraction(B, B, x);
			ShiftRight_bit(B, B, 1);
		}
	}

	//step 5
	while (is_even(v))
	{
		//step 5.1
		ShiftRight_bit(v, v, 1);

		//step 5.2
		if (is_even(C) && is_even(D))
		{
			ShiftRight_bit(C, C, 1);
			ShiftRight_bit(D, D, 1);
		}
		else
		{
			/*Addition(temp1, C, y);
			ShiftRight_bit(C, temp1, 1);
			Subtraction(temp2, D, x);
			ShiftRight_bit(D, temp2, 1);
			init_input_to_zero(temp1);
			init_input_to_zero(temp2);*/
			Addition(C, C, y);
			ShiftRight_bit(C, C, 1);
			Subtraction(D, D, x);
			ShiftRight_bit(D, D, 1);
		}
	}

	//step 6
	if (compare(u, v) == 0)
	{
		Subtraction(u, u, v);
		Subtraction(A, A, C);
		Subtraction(B, B, D);
		/*if (B->sig == POS_SIG)
		{
			Addition(A, A, y);
			Subtraction(B, B, x);
		}*/
	}
	else
	{
		Subtraction(v, v, u);
		Subtraction(C, C, A);
		Subtraction(D, D, B);
		/*if (D->sig == POS_SIG)
		{
			Addition(C, C, y);
			Subtraction(D, D, x);
		}*/
	}
	

	//step 7
	if (u->sig == ZERO_SIG)
	{
		init_input_to_zero(a);
		copy(a, C);
		init_input_to_zero(b);
		copy(b, D);
		ShiftLeft(gcd, v, k);
		/*if (D->sig = NEG_SIG)
		{
			Addition(b, b, x);
		}*/
	}
	else
		goto Label;
	
	
}