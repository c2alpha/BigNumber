#include "bignum.h"
/*==================================================================
 * �� �� �� : square
 * �Լ����� : multi-precision squaring�� ����
 * �Ķ���� : squaring�� �̿�� 1���� ������, �� ����� ���� ����.
 * ��    �� : none
 * out = in^2
 * in���̰� n�̶��, out�� ���̴� 2n�� �ȴ�.
==================================================================*/
void square(D_BINT_t out, D_BINT_t in)
{
	D_BINT_t temp;
	LIMB_t temp_dat[MAX_BINT_LEN] = { 0, };
	temp->dat = temp_dat;
	temp->len = (in->len) << 1;
	temp->sig = in->sig*in->sig;
	LIMB_t last_pos;
	LIMB_t c, uv[2], carry[2] = { 0, }, MSB, last_carry;//uv[1]=u uv[0]=v.
	//last_carry�� j-loop�� �� ������ �� ���ŵȴ�.
	//c�� uv[1]���� �߻��ϴ� carry�� ����
	//carry[0]�� uv[1]�� �� ����. carry[1]�� c�� �� ����
	last_carry = 0;
	last_pos = 2 * in->len - 1;//j-loop�� ������ �ѹ� �� �� �� ���ŵȴ�.
	for (int i = 0; i < in->len; i++)
	{
		//(uv) = w[2i] + x[i]* x[i], w[2i] = v, c = u
		spmult(&uv[1],&uv[0], in->dat[i], in->dat[i]);
		uv[0] += temp->dat[2*i];
		if (uv[0] < temp->dat[2*i])
			uv[1]++;
		
		c = 0;
		
		if (2 * i == last_pos && last_carry)//for i-loop�� ������ index(i= in->len -1) �� ���� ���� ����.	
		{
			uv[1] += last_carry;
			if (uv[1] < last_carry)
				c++;
			last_carry = 0;
		}
		
		//�˰��� ������ w[2i] = v �ϴ� �۾�
		temp->dat[2*i] = uv[0];
		//�˰��� ������ c = u �ϴ� �۾�
		carry[0] = uv[1];
		carry[1] = c;

		
		c = 0;
		for (int j = i + 1; j < in->len; j++)
		{
			// uv = x[i] * x[j] 
			spmult(&uv[1],&uv[0], in->dat[i], in->dat[j]);
			// 2�� �ϴ� �۾��� shift�� ó��
			MSB = (uv[0] & LMSB_ONE) ? 1 : 0;
			c = (uv[1] & LMSB_ONE) ? 1 : 0;
			uv[0] <<= 1;
			uv[1] <<= 1;
			uv[1] += MSB;
			//uv[0]�� �ֻ��� ��Ʈ�� �������� uv[0]�� �ι� ���� �� uv[1]�� carry�� �־����
			//uv[1]���� �������� �� carry�� c�� ǥ��.
			//uv = uv + carry
			uv[0] += carry[0];
			if (uv[0] < carry[0])
			{
				uv[1]++;
				if (uv[1] == 0)
					c++;
			}

			uv[1] += carry[1];
			if (uv[1] < carry[1])
				c++;

			// uv = uv + w[i+j] 
			uv[0] += temp->dat[i + j];
			if (uv[0] < temp->dat[i + j])
			{
				uv[1]++;
				if (uv[1] == 0)
					c++;
			}
			
			
			
			if (((i + j) == last_pos) && last_carry)
			{
				uv[1] += last_carry;
				if (uv[1] < last_carry)
					c++;
				last_carry = 0;
			}
			
			// w[i+j] = v, c = u 
			temp->dat[i + j] = uv[0];
			carry[0] = uv[1];
			carry[1] = c;
		}
		// w[i+j]�� i+j�� �����ܰ��� i+t�� ���ٸ� 2word�� �ȴ�.
		// w[i+in->len] = u 
		temp->dat[i + in->len] = carry[0];
		//w[i+in->len]���� ����� carry ����
		last_carry = carry[1];
		last_pos = i + in->len;
	}

	copy(out, temp);
	
}

