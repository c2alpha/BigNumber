#include "bignum.h"
#define LOW(x) ((LIMB_t)((x) & 0xFFFF))
#define HIGH(x) ((LIMB_t)((x) >> BITSZ_HL & 0xFFFF))
#define TOHIGH(x) ((LIMB_t)((x) << BITSZ_HL))
/*==================================================================
 * 함 수 명 : spdiv
 * 함수설명 : 2word 나누기 1word를 수행하여 몫과 나머지를 계산한다.
 * 파라미터 : 몫과 나머지를 담을 공간 하나씩, 2word의 피제수와 1word의 제수
 * 출    력 : none
 * single-precision mul 처럼 한 word를 16비트씩 쪼개서 수행한다.
==================================================================*/
void spdiv(LIMB_t *q, LIMB_t *r, LIMB_t u[2], LIMB_t v)
{	
	
	LIMB_t qhat, rhat, t, v0, v1, u0, u1, u2, u3;
	LIMB_t temp[2], q2;
	LIMB_t qv0, qv1, qv;
	temp[0] = u[0], temp[1] = u[1];
	//한 워드를 16비트씩 쪼개는 과정.
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

	//v0에 대한 확인. 이 과정을 하면 qhat과 q의 차이를 줄일 수 있음.(최대 1차이나게됨)
	t = TOHIGH(rhat) | u1;

	/* 전체 div에서 step2를 거쳐 y최상위 >= x최상위 임을 알고 있고,
	spdiv로 들어오는 것은 step3.1에서 y최상위 > x최상위 일 때다.
	따라서 1word/16비트를 했을 때 최대 몫은 2^16이다.
	단, 이 경우는 t의 상위 16비트가 v1과 같을때 일어난다.
	(또한, 이런 경우 t의 하위 16비트는 v1보다 클 수없다.) */
	if ( (qhat==MASK_RHW + 1)||(qhat * v0 > t))//MASK_RHW+1 => 16비트의 base
	{
		qhat--;//b-1로 셋팅
		rhat += v1;
		t = TOHIGH(rhat) | u1;
		//사실 rhat은 16비트 내에 있어야하는데, 그걸 넘어갔다는 것은 몫이 더 작아지면 안되는걸 의미함
		//만약 16비트 내에 있다면 그걸가지고 한 번 더 테스트
		if ((rhat < (MASK_RHW + 1)) && (qhat * v0 > t))
			qhat--;
	}
	
	//	(u3u2u1) = (u3u2u1) - qhat*(v1v0)
	// 아직도 qhat이 q보다 큰지 확인한다.
	// v0에 대한 확인을 했으므로 qhat과 q의 차이는 해봤자 1
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
		// 이 if문에 들어왔다면 qhat은 정확한 q가 된다.
		// 그럴 경우, 나머지는 한 워드 안에 들어가야 하므로
		// 상위 워드인 temp[1]은 0으로 만들어준다.
	}

	//몫의 상위 16비트를 지금까지 처리한 과정의 qhat값으로 채운다.
	//여기서의 qhat은 실제 q와 같다.
	*q = TOHIGH(qhat);

	
	// qhat = (u2u1) / v1 
	// 단, (u2u1)은 위 과정을 진행하고 남은 나머지 값이다.
	// 처음 설정된 (u2u1) 아님
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
