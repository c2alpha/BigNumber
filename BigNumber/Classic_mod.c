#include"bignum.h"

void c_mod(D_BINT_t x, D_BINT_t y, D_BINT_t m)
{
	D_BINT_t mul;
	D_BINT_t q;
	D_BINT_t r;
	LIMB_t mul_dat[300] = { 0, };
	LIMB_t q_dat[300] = { 0, };
	LIMB_t r_dat[300] = { 0, };
	q->dat = q_dat;
	r->dat = r_dat;
	mul->dat = mul_dat;
	mpmul(mul, x, y);
	mpdiv(q, r, mul, m);

	printf("\nmul 값임\n");
	print_out(mul);
	printf("\nr 값임\n");
	print_out(r);


}