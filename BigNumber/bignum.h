#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_
/*input 두개중 큰 input의 size를 뽑아내기 위함.*/
#define max(a,b) (((a) > (b)) ? (a) : (b))
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include<Windows.h>
#ifdef __cplusplus
extern "C"
{
#endif



	/*
	* only one of follows has to be 1 according to system information.
	* by default, _IS_32BIT_FAST_ is set to be 1.
	*/
#define _IS_16BIT_FAST_ 0
#define _IS_32BIT_FAST_ 1
#define _IS_64BIT_FAST_ 0



#define _WORD_BITSZ_32_

#if _IS_16BIT_FAST_ == 1

	typedef uint16_t	LIMB_t;
	typedef LIMB_t*		P_LIMB_t;
	typedef int16_t		SLIMB_t;
	typedef SLIMB_t*	P_SLIMB_t;
	typedef uint8_t		HLIMB_t;
	typedef LIMB_t*		P_HLIMB_t;
	typedef int8_t		SHLIMB_t;
	typedef SHLIMB_t*	P_SHLIMB_t;

	/* about masks*/
#define MASK_WL  	((uint_least16_t)0xffff) /*Whole Limb*/
#define MASK_LHL	((uint_least16_t)0xff00) /*Left Half Limb*/
#define MASK_RHW	((uint_least16_t)0x00ff) /*Right Half Word*/

/* about significant bit */
#define LMSB_ONE	((uint_least16_t)0x8000) /*Left Most Significant Bit One*/
#define RMSB_ONE	((uint_least16_t)0x0080) /*Right Most Significant Bit One*/
#define LLSB_ONE	((uint_least16_t)0x0100) /*Left Least Significant Bit One*/
#define RLSB_ONE	((uint_least16_t)0x0001) /*Right Least Significant Bit One*/

/* about bitsize, byte lenght */
#define BITSZ_WL	16 /*Bit size of Whole Limb*/
#define BITSZ_HL	 8 /*Bit size of Half Limb*/
#define BYTELEN_WL   2 /* Byte length of Whole Limb*/
#define BYTELEN_HL   1 /* Byte length of Half Limb*/

#elif _IS_64BIT_FAST_ == 1

	typedef uint64_t	LIMB_t;
	typedef LIMB_t*		P_LIMB_t;
	typedef int64_t		SLIMB_t;
	typedef SLIMB_t*	P_SLIMB_t;
	typedef uint32_t	HLIMB_t;
	typedef LIMB_t*		P_HLIMB_t;
	typedef int32_t		SHLIMB_t;
	typedef SHLIMB_t*	P_SHLIMB_t;

	/* about masks*/
#define MASK_WL  	((uint_least64_t)0xffffffffffffffff) /*Whole Limb*/
#define MASK_LHL	((uint_least64_t)0xffffffff00000000) /*Left Half Limb*/
#define MASK_RHW	((uint_least64_t)0x00000000ffffffff) /*Right Half Word*/

/* about significant bit */
#define LMSB_ONE	((uint_least64_t)0x8000000000000000) /*Left Most Significant Bit One*/
#define RMSB_ONE	((uint_least64_t)0x0000000080000000) /*Right Most Significant Bit One*/
#define LLSB_ONE	((uint_least64_t)0x0000000100000000) /*Left Least Significant Bit One*/
#define RLSB_ONE	((uint_least64_t)0x0000000000000001) /*Right Least Significant Bit One*/

/* about bitsize, byte lenght */
#define BITSZ_WL	64 /*Bit size of Whole Limb*/
#define BITSZ_HL	32 /*Bit size of Half Limb*/
#define BYTELEN_WL   8 /* Byte length of Half Limb*/
#define BYTELEN_WL   4 /* Byte length of Half Limb*/

#else /* _IS_32BIT_FAST == 1 */

	typedef uint32_t	LIMB_t;
	typedef LIMB_t*		P_LIMB_t;
	typedef int32_t		SLIMB_t;
	typedef SLIMB_t*	P_SLIMB_t;
	typedef uint16_t	HLIMB_t;
	typedef LIMB_t*		P_HLIMB_t;
	typedef int16_t		SHLIMB_t;
	typedef SHLIMB_t*	P_SHLIMB_t;

	/* about masks*/
#define MASK_WL  	((uint_least32_t)0xffffffff) /*Whole Limb*/
#define MASK_LHL	((uint_least32_t)0xffff0000) /*Left Half Limb*/
#define MASK_RHW	((uint_least32_t)0x0000ffff) /*Right Half Word*/

/* about significant bit */
#define LMSB_ONE	((uint_least32_t)0x80000000) /*Left Most Significant Bit One*/
#define RMSB_ONE	((uint_least32_t)0x00008000) /*Right Most Significant Bit One*/
#define LLSB_ONE	((uint_least32_t)0x00010000) /*Left Least Significant Bit One*/
#define RLSB_ONE	((uint_least32_t)0x00000001) /*Right Least Significant Bit One*/

/* about bitsize, byte lenght */
#define BITSZ_WL	32 /*Bit size of Whole Limb*/
#define BITSZ_HL	16 /*Bit size of Half Limb*/
#define BYTELEN_WL   4 /* Byte length of Whole Limb*/
#define BYTELEN_HL   2 /* Byte length of Half Limb*/

#endif

	/* system independent types , definition */
	typedef uint8_t		IODATA_t;	/* IO data(ciphertext, plaintext, key, information) */
	typedef int32_t		RET_VAL_t;	/* basic function return */
	typedef int8_t		TORF_t;		/* true or false */
#undef TRUE
#define TRUE		((TORF_t)1)
#undef FALSE
#define FALSE		((TORF_t)0)
	typedef int8_t SIGN; /* 1:positive,0:zero,-1:negative */
#define POS_SIG		((SIGN) 1)
#define NEG_SIG		((SIGN) -1)
#define ZERO_SIG	((SIGN) 0)
	typedef LIMB_t LEN; /* the number of limbs */

	typedef struct _BINT
	{
		SIGN	 sig;
		P_LIMB_t dat;
		LEN		 len;
	}BINT_t;
	typedef BINT_t	D_BINT_t[1]; /*default data type for BINT*/
	typedef BINT_t* P_BINT_t;

	/* limit information of big integer length */
#define MEM_MARGIN_LIMB 1
#define MAX_BINT_LEN (300 + MEM_MARGIN_LIMB)



#ifdef __cplusplus
}
#endif

#endif /*_CONFIG_H_*/
void mpadd(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2);
void mpsub(D_BINT_t out, D_BINT_t in_1, D_BINT_t in_2);
int compare(D_BINT_t in1, D_BINT_t in2);
void test_AddAndSub(D_BINT_t out, D_BINT_t in1, D_BINT_t in2);
LIMB_t rand_gen();
void print_out(D_BINT_t out);
void copy(D_BINT_t des,D_BINT_t sta);
void Addition(D_BINT_t out, D_BINT_t in1, D_BINT_t in2);
void Subtraction(D_BINT_t out, D_BINT_t in1, D_BINT_t in2);
void init_input(D_BINT_t in);
void valid_test();