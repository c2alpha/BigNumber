#include "bignum.h"

/*==================================================================	
* 함수명 : compare
* 함수 설명 : 절댓값의 크기를 비교한다.
* 입력 : D_BINT_t 타입 구조체 2개(in1,in2)
* 출력 : in1>=in2 인 경우 0, in1<in2인 경우 1
			
===================================================================*/

int compare(D_BINT_t in1, D_BINT_t in2)
{
	int check = 0;
		
		for (int i = max(in1->len,in2->len)-1; i >= 0; i--)
		{
			//위쪽 if elseif 구문은 길이만 길다면 절대값이 더 크다고 할 수 있기 때문에 
			//for문을 다 돌지 않고 check를 끝낼 수 있어서 속도면에서 효율적이다.
			//단, sig가 0인 경우는 check하지 않는다. sig가 0으로 같아도 len가 다른 일이 있기때문
			if ((in1->sig == POS_SIG) && (in1->len > in2->len))
				return 0;
			else if ((in1->sig == NEG_SIG) && (in1->len > in2->len))
			{
				return 0;
			}
			
			//마찬가지로 상위 word가 하나라도 크다면 더 큰 값이기 때문에 for문을 다 돌지 않아도
			//check를 할 수 있다.
			if (in1->dat[i] > in2->dat[i])
			{
				return 0;

			}
			else if (in1->dat[i] < in2->dat[i])
			{
				check = 1;
				return check;
			}
				
		}
		return 0;
		
		
}




//asdasd









/* swap으로 쓸 일 있으면 쓰기*/
//void compare(D_BINT_t in1, D_BINT_t in2)
//{
//	
//	for (int i = in1->len-1; i >= 0; i--)
//	{
//		if (in1->dat[i] < in2->dat[i])
//		{
//			D_BINT_t temp;
//			temp->sig = in1->sig;
//			temp->len = in1->len;
//			temp->dat = in1->dat;
//			in1->dat = in2->dat;
//			in1->sig = in2->sig;
//			in1->len = in2->len;
//			in2->dat = temp->dat;
//			in2->sig = temp->sig;
//			in2->len = temp->len;
//			break;
//		}
//			
//	}
//}