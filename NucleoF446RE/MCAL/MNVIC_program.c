/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 NVIC								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 18, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MNVIC_private.h"
#include "MNVIC_interface.h"

// Variables
static u8 G_u8PRIGroup; /* Note it must be in MSCB Driver and extern it here  */

STD_error_t MNVIC_stderrEnableINT	(u8 ARG_u8IRQNum)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ)
	{
		u8 L_u8RegNum = ARG_u8IRQNum >> MNVIC_IRQ_REGSHIFT; /* 2^5 = 32 divide by 32 */
		u8 L_u8BitNum = (ARG_u8IRQNum & MNVIC_IRQ_BITSMASK); /* 5-LSB indicate bit location from 0:31 */
		NVIC->ISER[L_u8RegNum] = MNVIC_BITMASK<<L_u8BitNum; /* set bit */
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MNVIC_stderrDisableINT	(u8 ARG_u8IRQNum)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ)
	{
		u8 L_u8RegNum = ARG_u8IRQNum >> MNVIC_IRQ_REGSHIFT; /* 2^5 = 32 divide by 32 */
		u8 L_u8BitNum = (ARG_u8IRQNum & MNVIC_IRQ_BITSMASK); /* 5-LSB indicate bit location from 0:31 */
		NVIC->ICER[L_u8RegNum] = MNVIC_BITMASK<<L_u8BitNum; /* set bit */
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MNVIC_stderrSetPendingFlag	(u8 ARG_u8IRQNum)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ)
	{
		u8 L_u8RegNum = ARG_u8IRQNum >> MNVIC_IRQ_REGSHIFT; /* 2^5 = 32 divide by 32 */
		u8 L_u8BitNum = (ARG_u8IRQNum & MNVIC_IRQ_BITSMASK); /* 5-LSB indicate bit location from 0:31 */
		NVIC->ISPR[L_u8RegNum] = MNVIC_BITMASK<<L_u8BitNum; /* set bit */
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}

STD_error_t MNVIC_stderrClearPendingFlag(u8 ARG_u8IRQNum)
{
	STD_error_t L_stderrState=E_OK;
	if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ)
	{
		u8 L_u8RegNum = ARG_u8IRQNum >> MNVIC_IRQ_REGSHIFT; /* 2^5 = 32 divide by 32 */
		u8 L_u8BitNum = (ARG_u8IRQNum & MNVIC_IRQ_BITSMASK); /* 5-LSB indicate bit location from 0:31 */
		NVIC->ICPR[L_u8RegNum] = MNVIC_BITMASK<<L_u8BitNum; /* set bit */
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MNVIC_stderrGetActiveFlag	(u8 *ARG_pu8ActiveFlagValue, u8 ARG_u8IRQNum)
{
	STD_error_t L_stderrState=E_OK;
	/* check null pointer */
	if (ARG_pu8ActiveFlagValue != NULL_POINTER)
	{
		if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ)
		{
			u8 L_u8RegNum = ARG_u8IRQNum >> MNVIC_IRQ_REGSHIFT; /* 2^5 = 32 divide by 32 */
			u8 L_u8BitNum = (ARG_u8IRQNum & MNVIC_IRQ_BITSMASK); /* 5-LSB indicate bit location from 0:31 */
			*ARG_pu8ActiveFlagValue= (NVIC->IABR[L_u8RegNum] >> L_u8BitNum) & MNVIC_BITMASK; /* Read bit*/
		}
		else
		{
			L_stderrState=E_NOK;
		}
		
	}
	else
	{
		L_stderrState = E_NULL_POINTER;
	}
	
	return L_stderrState;	
}

STD_error_t MSCB_stderrSetPriorityGrouping	(u8 ARG_u8PRIGroup)
{
	STD_error_t L_stderrState=E_OK;
	
	if (ARG_u8PRIGroup <= BitsGroup0_Sub4) 
	{
		G_u8PRIGroup = ARG_u8PRIGroup; /* save the value in Global to be used in Set pir func */
		/* Assign the value with VECKEY at the same time */
		MSCB_AIRCR =  MSCB_AIRCR_VECTKEY | (ARG_u8PRIGroup<<MSCB_PRIGROUP_BIT0);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MNVIC_stderrSetIRQPriority		(u8 ARG_u8IRQNum, u8 ARG_u8GroupPriority, u8 ARG_u8SubPriority)
{
	STD_error_t L_stderrState=E_OK;
	/* Check ARGs Value */
	if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ )
	{
		u8 L_u8IRQPriority;
		switch(G_u8PRIGroup)
		{
		case BitsGroup4_Sub0: 
			L_u8IRQPriority = ( (ARG_u8GroupPriority&MNVIC_PIR4BIT_MASK) ); /* there is no Sub piriority */
			break;
		case BitsGroup3_Sub1: 
			L_u8IRQPriority = ( ((ARG_u8GroupPriority&MNVIC_PIR3BIT_MASK)<<1) | ((ARG_u8SubPriority&MNVIC_PIR1BIT_MASK)<<0) ); /* (3-LSB << 1)  | (1-LSB<<0)  */
			break;
		case BitsGroup2_Sub2: 
			L_u8IRQPriority = ( ((ARG_u8GroupPriority&MNVIC_PIR2BIT_MASK)<<2) | ((ARG_u8SubPriority&MNVIC_PIR2BIT_MASK)<<0) ); /* (2-LSB << 2)  | (2-LSB<<0)  */
			break;
		case BitsGroup1_Sub3:
			L_u8IRQPriority = ( ((ARG_u8GroupPriority&MNVIC_PIR1BIT_MASK)<<3) | ((ARG_u8SubPriority&MNVIC_PIR2BIT_MASK)<<0) ); /* (1-LSB << 3)  | (3-LSB<<0)  */
			break;
		case BitsGroup0_Sub4:
			L_u8IRQPriority = ( (ARG_u8SubPriority&MNVIC_PIR4BIT_MASK) ); /* there is no Group piriority */
			break;
		default: break;
		}
		/* Assign the piriority which is 4 bits to IPR Reg << 4 */
		NVIC->IPR[ARG_u8IRQNum] = L_u8IRQPriority<<MNVIC_IRQ_PIR_SHIFTBITS ;
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}
/* 
 *	the priority will be in 4 bits like Priority 8 = 0b1000
 *	if we choose BitsGroup2_Sub2 then the 2-MSB 
 *	0b10 for Group and 2-LSB 0b00 for Sub 
 */	
// STD_error_t MNVIC_stderrSetIRQPriority		(u8 ARG_u8IRQNum , u8 ARG_u8IRQPriority)
// {
	// /* need to be handeled with 3 ARGs not 2 add another one for Group */
	// STD_error_t L_stderrState=E_OK;
	// /* Check ARGs Value */
	// if(ARG_u8IRQNum <= FMPI2C1_ERROR_IRQ && ARG_u8IRQPriority <= IRQ_Priority15)
	// {
		// /* in case of the user know the dedicated bits */
		// NVIC->IPR[ARG_u8IRQNum] = ARG_u8IRQPriority<<MNVIC_IRQ_PIR_SHIFTBITS ;
	// }
	// else
	// {
		// L_stderrState=E_NOK;
	// }
	
	// return L_stderrState;
// }
