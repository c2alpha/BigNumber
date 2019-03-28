#include "bignum.h"

/*==================================================================
 * �� �� �� : mpmul
 * �Լ����� : multi-precision ������ ����
 * �Ķ���� : ������ �̿�� 2���� ������, �� ����� ���� ����.
 * ��    �� : none
 * out = in1 * in2
 * in1,in2�� ���̰� ���� n,t���, out�� ���̴� n+t�� �ȴ�.
==================================================================*/

// for i-loop�� in2�� index����, for j-loop�� in1�� index����
void mpmul(D_BINT_t out, D_BINT_t in1, D_BINT_t in2)
{
	int i, j;
	LIMB_t uv[2] = { 0, };//�˰��� �󿡼� u=uv[1] v=uv[0]
	LIMB_t carry = 0;
	D_BINT_t temp;
	LIMB_t temp_dat[MAX_BINT_LEN] = { 0, };
	temp->dat = temp_dat;
	temp->len = in1->len + in2->len;
	//init_output(out);

	if ((in1->sig == ZERO_SIG) || (in2->sig == ZERO_SIG))//input�� ��ȣ�� �� �� 0
	{
		out->sig = ZERO_SIG;
		out->len = 1;
		out->dat[0] = 0;
	}
	else if (in1->sig == in2->sig)//input�� ��ȣ�� ����.(+,+ or -,-)
	{
		temp->sig = POS_SIG;
		for (i = 0; i < in2->len; i++)
		{
			carry = 0;
			for (j = 0; j < in1->len; j++)
			{
				//uv = in1[j]*in2[i]
				spmult(&uv[1],&uv[0], in1->dat[j], in2->dat[i]);//�ε��� ����! �� ���� ���� ����� �� ó�� �ϱ�
				uv[0] = uv[0] + carry;
				if (uv[0] < carry)
					uv[1]++;
				uv[0] = uv[0] + temp->dat[i + j];
				if (uv[0] < temp->dat[i + j])
					uv[1]++;

				//w[i+j] = v
				temp->dat[i + j] = uv[0];
				//c = u
				carry = uv[1];
			}
			// w[i+in1->len] = u
			temp->dat[i + in1->len] = carry;
		}
		copy(out, temp);
	}
	else//input�� ��ȣ�� �ٸ���(+,- or -,+)
	{
		temp->sig = NEG_SIG;
		for (i = 0; i < in2->len; i++)
		{
			carry = 0;
			for (j = 0; j < in1->len; j++)
			{
				spmult(&uv[1],&uv[0], in1->dat[j], in2->dat[i]);
				uv[0] = uv[0] + carry;
				if (uv[0] < carry)
					uv[1]++;
				uv[0] = uv[0] + temp->dat[i + j];
				if (uv[0] < temp->dat[i + j])
					uv[1]++;

				temp->dat[i + j] = uv[0];
				carry = uv[1];
			}
			temp->dat[i + in1->len] = carry;
		}
		copy(out, temp);
	}

	//in1�� n digit, in2�� 1��(=>1 digit) ������ ���
	//����� len�� n+1�� �ƴ� n �̹Ƿ� �ʿ��ϴ�.
	while ((out->len != 0) && (!out->dat[out->len - 1]))
		out->len--;
	if (!out->len)
	{
		out->sig = ZERO_SIG;
		out->len = 1;
		out->dat[0] = 0;
	}


}