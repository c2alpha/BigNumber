#include "bignum.h"
/*==================================================================
 * �� �� �� : mpdiv
 * �Լ����� : ������ ���̸� ������ ������ �������� ��� ������ ���
 * �Ķ���� : ��� �������� ���� ���� �ϳ���, ������ ���̸� ������ ����,������
 * ��    �� : none
==================================================================*/
int mpdiv(D_BINT_t q, D_BINT_t r, D_BINT_t u,D_BINT_t v)
{	
	LIMB_t shift;
	LIMB_t bitmask, overflow;
	LIMB_t qhat, rhat, t[2];
	D_BINT_t word2, word3;
	D_BINT_t qhat_temp;
	LIMB_t shift_word;//ShiftLeft_word�� ����ϱ� ����. u->len�� ������
	D_BINT_t u_temp, v_temp;//normalize�� u,v�� ������ ����,
	D_BINT_t v_temp_neg;//step3.4���� ������ ���� ��� ������ ���ܼ� �߰�
	D_BINT_t u_temp_neg;//step3.4���� ������ ���� ��� ������ ���ܼ� �߰�
	LIMB_t u_neg_tempary[300] = { 0, };
	LIMB_t v_neg_tempary[300] = { 0, };
	LIMB_t u_tempary[300] = { 0, };
	LIMB_t v_tempary[300] = { 0, };
	LIMB_t word2_ary[300] = { 0, };
	LIMB_t word3_ary[300] = { 0, };
	LIMB_t qhat_ary[300] = { 0, };
	LIMB_t ctrl_shift = 0;
	u_temp->dat = u_tempary;
	v_temp->dat = v_tempary;
	v_temp_neg->dat = v_neg_tempary;
	v_temp_neg->sig = NEG_SIG;
	u_temp_neg->dat = u_neg_tempary;
	int cmp;
	q->sig = POS_SIG;
	r->sig = POS_SIG;
	q->len = u->len - v->len + 1;
	r->len = v->len;
	memset(q->dat, 0, sizeof(LIMB_t)*q->len);
	memset(r->dat, 0, sizeof(LIMB_t)*r->len);
	int vlen_check = 0;
	
	//v�� ���̰� 1�� ���� ��� ������ �ʿ��ϴ�.
	if (v->len == 1)
	{
		vlen_check = 1;
		u->len++;
		v->len++;
		D_BINT_t shift_utemp;
		D_BINT_t shift_vtemp;
		LIMB_t shift_utemp_dat[300] = { 0, };
		LIMB_t shift_vtemp_dat[300] = { 0, };
		shift_utemp->dat = shift_utemp_dat;
		shift_vtemp->dat = shift_vtemp_dat;
		copy(shift_utemp, u);
		copy(shift_vtemp, v);
		for (int i = u->len - 1; i >= 0; i--)
		{
			shift_utemp->dat[i + 1] = u->dat[i];
		}
		shift_utemp->dat[0] = 0;
		for (int j = v->len - 1; j >= 0; j--)
		{
			shift_vtemp->dat[j + 1] = v->dat[j];
		}
		shift_vtemp->dat[0] = 0;
		copy(u, shift_utemp);
		copy(v, shift_vtemp);
	}

	
	if (v->sig == ZERO_SIG)
		return -1;	/* Divide by 0 => ����*/
	
	if (u->len < v->len)//v�� ���̰� u�� ���̺��� ���( �� ������ ���� �� �Ǵ�)
	{	
		copy(r, v);
		return 0;
	}

	if (u->len == v->len)//v�� u�� ���̰� ����
	{	
		cmp = compare2(u, v);
		if (cmp < 0)
		{	// v > u
			copy(r, u);
			return 0;
		}
		else if (cmp == 0)
		{	// v = u
			q->len = 1;
			q->dat[0] = 1;
			return 0;
		}
	}
	if ((v->len == 1) && (v->dat[0] == 1))
	{
		//v=1;
		copy(q, u);
		return 0;
	}

	

	//normalize �غ�
	bitmask = LMSB_ONE;
	for (shift = 0; shift < BITSZ_WL; shift++)
	{
		if (v->dat[v->len - 1] & bitmask)
			break;
		bitmask >>= 1;
	}

	// Normalize v 
	overflow = ShiftLeft_bit(v, v, shift);

	// Normalize u(v�� normalize�ص� len�� ��ȭ�� ������ u�� 1�� �þ �� �ִ�.
	// normalize�� ������ v�� �ֻ��� ��Ʈ�� 0���� �� �͵��� ����� �۾��̹Ƿ�.)
	u_temp->len = u->len;
	u_temp->sig = u->sig;

	//overflow = 0;
	overflow = ShiftLeft_bit(u_temp, u, shift);
	if (overflow)//�ٷ� �� �������� overflow�� �߻��ߴٸ� �װ� ���� ������ �ʿ��ϴ�
	{
		u_temp->len++;
		u_temp->dat[u_temp->len - 1] = overflow;
	}
	ctrl_shift = u_temp->len;
	copy(v_temp, v);
	shift_word = ctrl_shift;
	ShiftLeft_word(v_temp, shift_word);

	q->len = u_temp->len - v->len + 1;
	r->len = v->len;
	memset(q->dat, 0, sizeof(LIMB_t)*q->len);
	memset(r->dat, 0, sizeof(LIMB_t)*r->len);

	

	//step2
	if (compare2(u_temp, v_temp) >= 0)
	{
		q->dat[q->len - 1]++;
		Subtraction(u_temp, u_temp, v_temp);
	}
	
	// step 3
	LIMB_t qlen = q->len-1;
	// i= u_temp->len-1 �̿���
	for (int i = u_temp->len-1; i >= v->len; i--)
	{
		ctrl_shift--;
		qlen--;
		//step3.1
		if (u_temp->dat[i] == v->dat[v->len - 1])
		{
			//q->dat[i-v->len]�̿���
			q->dat[qlen] = MASK_WL;
			qhat = MASK_WL;
		}
		else
		{
			t[1] = u_temp->dat[i];
			t[0] = u_temp->dat[i - 1];
			spdiv(&qhat, &rhat, t, v->dat[v->len - 1]);
			q->dat[qlen] = qhat;
		}

		//step3.2
		word2->dat = word2_ary;
		word2->sig = v->sig;
		word2->len = 2;
		/*word2->dat[1] = v_temp->dat[v_temp->len - 1];
		word2->dat[0] = v_temp->dat[v_temp->len - 2];*/
		word2->dat[1] = v->dat[v->len - 1];
		word2->dat[0] = v->dat[v->len - 2];
		word3->dat = word3_ary;
		word3->sig = u_temp->sig;
		word3->len = 3;
		word3->dat[2] = u_temp->dat[i];
		word3->dat[1] = u_temp->dat[i - 1];
		word3->dat[0] = u_temp->dat[i - 2];
		qhat_temp->sig = POS_SIG;
		qhat_temp->len = 1;
		qhat_temp->dat = qhat_ary;
		qhat_temp->dat[0] = qhat;
		mpmul(qhat_temp, qhat_temp, word2);
		//������ compare == 0�̿���
		while (compare2(qhat_temp, word3) == 1)
		{
			qhat--;
			qhat_temp->len = 1;
			qhat_temp->dat[0] = qhat;
			mpmul(qhat_temp, qhat_temp, word2);
			q->dat[qlen]--;
		}

		//step3.3
		D_BINT_t temp_step3;
		LIMB_t temp_step3_dat[300] = { 0, };
		temp_step3->dat = temp_step3_dat;
		copy(temp_step3, u_temp);
		copy(v_temp, v);
		shift_word = ctrl_shift;
		
		ShiftLeft_word(v_temp, shift_word);
		qhat_temp->sig = POS_SIG;
		qhat_temp->len = 1;
		qhat_temp->dat[0] = q->dat[qlen];
		mpmul(v_temp, v_temp, qhat_temp);
		Subtraction(u_temp, temp_step3, v_temp);

		//step3.4
		/*D_BINT_t zero_temp;
		zero_temp->sig = u_temp->sig;
		zero_temp->len = u_temp->len;
		memset(zero_temp->dat, 0, sizeof(LIMB_t) * zero_temp->len);*/
		copy(v_temp, v);
		shift_word = ctrl_shift;
		ShiftLeft_word(v_temp, shift_word);
		copy(v_temp_neg, v_temp);
		
		qhat_temp->sig = POS_SIG;
		qhat_temp->len = 1;
		qhat_temp->dat[0] = q->dat[qlen];
		mpmul(v_temp, v_temp, qhat_temp);
		//mpmul(v_temp_neg, v_temp_neg, qhat_temp);
		if (u_temp->sig==NEG_SIG)
		{
			copy(u_temp_neg, u_temp);
			if (u_temp_neg->len > v_temp_neg->len)
				u_temp_neg->len--;
			Addition(u_temp, u_temp_neg, v_temp_neg);
			q->dat[qlen]--;
			u_temp->sig = POS_SIG;
		}

	}	

	
	copy(r, u_temp);
	//Unnormalize
	ShiftRight_bit(r, r, shift);
	
	r->len = v->len;//���� �� copy(r, u_temp)�κп��� ������ r�� ���̺���
					//����� �� �ֱ� ������ �ʿ���
	
	//v�� ���̰� 1�� ���� ��� v��u�� 0���� ä���� ���̸� 1 �÷ȱ� ������
	//�ٽ� �ٿ������
	if (vlen_check)
	{
		LIMB_t temp0;
		temp0 = r->dat[1];
		r->dat[0] = temp0;
		r->len--;

		D_BINT_t sr_temp;
		LIMB_t sr_temp_dat[300] = { 0, };
		sr_temp->dat = sr_temp_dat;
		sr_temp->len = u->len - 1;
		for (int i = sr_temp->len - 1; i >= 0; i--)
		{
			sr_temp->dat[i] = u->dat[i + 1];
		}
		copy(u, sr_temp);

	}
	for (int i = r->len; i <= 300; i++)
		r->dat[i] = 0;
	return 0;
}




