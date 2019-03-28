#include "bignum.h"
#define LOW(x) ((LIMB_t)((x) & 0xFFFF))
#define HIGH(x) ((LIMB_t)((x) >> BITSZ_HL & 0xFFFF))
#define TOHIGH(x) ((LIMB_t)((x) << BITSZ_HL))
/*==================================================================
 * �� �� �� : spdiv
 * �Լ����� : 2word ������ 1word�� �����Ͽ� ��� �������� ����Ѵ�.
 * �Ķ���� : ��� �������� ���� ���� �ϳ���, 2word�� �������� 1word�� ����
 * ��    �� : none
 * single-precision mul ó�� �� word�� 16��Ʈ�� �ɰ��� �����Ѵ�.
==================================================================*/
void spdiv(LIMB_t *q, LIMB_t *r, LIMB_t u[2], LIMB_t v)
{	
	
	LIMB_t qhat, rhat, t, v0, v1, u0, u1, u2, u3;
	LIMB_t temp[2], q2;
	LIMB_t qv0, qv1, qv;
	temp[0] = u[0], temp[1] = u[1];
	//�� ���带 16��Ʈ�� �ɰ��� ����.
	v0 = LOW(v);
	v1 = HIGH(v);
	u0 = LOW(u[0]);
	u1 = HIGH(u[0]);
	u2 = LOW(u[1]);
	u3 = HIGH(u[1]);	


	

	/*
	  qhat = (u3u2) / v1
	  rhat = (u3u2) - qhat*v1
	*/ 
	t = temp[1];
	qhat = t / v1;
	rhat = t - qhat * v1;

	//v0�� ���� Ȯ��. �� ������ �ϸ� qhat�� q�� ���̸� ���� �� ����.(�ִ� 1���̳��Ե�)
	t = TOHIGH(rhat) | u1;

	/* ��ü div���� step2�� ���� y�ֻ��� >= x�ֻ��� ���� �˰� �ְ�,
	spdiv�� ������ ���� step3.1���� y�ֻ��� > x�ֻ��� �� ����.
	���� 1word/16��Ʈ�� ���� �� �ִ� ���� 2^16�̴�.
	��, �� ���� t�� ���� 16��Ʈ�� v1�� ������ �Ͼ��.
	(����, �̷� ��� t�� ���� 16��Ʈ�� v1���� Ŭ ������.) */
	if ( (qhat==MASK_RHW + 1)||(qhat * v0 > t))//MASK_RHW+1 => 16��Ʈ�� base
	{
		qhat--;//b-1�� ����
		rhat += v1;
		t = TOHIGH(rhat) | u1;
		//��� rhat�� 16��Ʈ ���� �־���ϴµ�, �װ� �Ѿ�ٴ� ���� ���� �� �۾����� �ȵǴ°� �ǹ���
		//���� 16��Ʈ ���� �ִٸ� �װɰ����� �� �� �� �׽�Ʈ
		if ((rhat < (MASK_RHW + 1)) && (qhat * v0 > t))
			qhat--;
	}
	
	//	(u3u2u1) = (u3u2u1) - qhat*(v1v0)
	// ������ qhat�� q���� ū�� Ȯ���Ѵ�.
	// v0�� ���� Ȯ���� �����Ƿ� qhat�� q�� ���̴� �غ��� 1
	LIMB_t buffer = temp[1];
	temp[1] = HIGH(temp[1]);	// (0u3) 
	temp[0] = TOHIGH(LOW(buffer)) | u1;	// (u2u1) 
	
	// u = u - qhat*(v1v0)
	qv0 = qhat * v0;
	qv1 = qhat * v1;
	qv = TOHIGH(LOW(qv1)) + qv0;
	temp[0] -= qv;
	if (temp[0] > MASK_WL - qv)
		temp[1]--;	//carry;
	temp[1] -= HIGH(qv1);
	
	if (HIGH(temp[1]) != 0)
	{	
		qhat--;
		temp[0] += v;
		temp[1] = 0;
		// �� if���� ���Դٸ� qhat�� ��Ȯ�� q�� �ȴ�.
		// �׷� ���, �������� �� ���� �ȿ� ���� �ϹǷ�
		// ���� ������ temp[1]�� 0���� ������ش�.
	}

	//���� ���� 16��Ʈ�� ���ݱ��� ó���� ������ qhat������ ä���.
	//���⼭�� qhat�� ���� q�� ����.
	*q = TOHIGH(qhat);

	
	// qhat = (u2u1) / v1 
	// ��, (u2u1)�� �� ������ �����ϰ� ���� ������ ���̴�.
	// ó�� ������ (u2u1) �ƴ�
	t = temp[0];
	qhat = t / v1;
	rhat = t - qhat * v1;

	t = TOHIGH(rhat) | u0;
	if ((qhat == MASK_RHW + 1) || (qhat * v0 > t))
	{
		qhat--;
		rhat += v1;
		t = TOHIGH(rhat) | u0;
		
		if ((rhat < (MASK_RHW + 1)) && (qhat * v0 > t))
			qhat--;
	}

	temp[1] = HIGH(temp[0]);	
	temp[0] = TOHIGH(LOW(temp[0])) | u0;	
	
	 //u = u - qhat*(v1v0)
	qv0 = qhat * v0;
	qv1 = qhat * v1;
	qv = TOHIGH(LOW(qv1)) + qv0;
	temp[0] -= qv;
	if (temp[0] > MASK_WL - qv)
		temp[1]--;	//carry;
	temp[1] -= HIGH(qv1);
	
	if (HIGH(temp[1]) != 0)
	{	
		qhat--;
		temp[0] += v;
		temp[1] = 0;
	}

	*q |= LOW(qhat);
	*r = temp[0];
	
}
