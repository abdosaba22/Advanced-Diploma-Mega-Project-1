/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 EXT Interrupt						*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MEXTI_private.h"
#include "MEXTI_interface.h"

// Variables
static void(*G_pvoidfCallbackFuncArr[MEXTI_NUM])(void)={NULL_POINTER}; /* Global array of ptr to Func */


STD_error_t MEXTI_stderrConfig 				(const MEXTI_PinConfig_t* ARG_pconfigPinConfig)
{
	STD_error_t L_stderrState=E_OK;
	/* check NULL pointer */
	if(NULL_POINTER == ARG_pconfigPinConfig || NULL_POINTER == ARG_pconfigPinConfig->CallBackFunc )
	{
		L_stderrState=E_NULL_POINTER;
	}
	else
	{	/* check the ARGs value */
		if( MEXTI_LIN22 >= ARG_pconfigPinConfig->Exti_Num)
		{
			/*Choose Trigger Type*/
			switch(ARG_pconfigPinConfig->Trigger)
			{
			case MEXTI_RAISING_TRIGGER:
				/* SET Rising Clear Falling */
				EXTI->RTSR |= 1<< ARG_pconfigPinConfig->Exti_Num;
				EXTI->FTSR &= ~(1<< ARG_pconfigPinConfig->Exti_Num);		
				break;
			case MEXTI_FALLING_TRIGGER:
				/* SET Falling Clear Rising */
				EXTI->FTSR |= 1<< ARG_pconfigPinConfig->Exti_Num;
				EXTI->RTSR &= ~(1<< ARG_pconfigPinConfig->Exti_Num);
				break;
			case MEXTI_RIS_FALL_TRIGGER:
				/* SET Falling SET Rising */
				EXTI->RTSR |= 1<< ARG_pconfigPinConfig->Exti_Num;
				EXTI->FTSR |= 1<< ARG_pconfigPinConfig->Exti_Num; 	  
				break;
			default: L_stderrState = E_NOK;
			}
			/* we can also Mask and or with mode value instead of if-cond */
			/* check the start configuration mode of EXTI enable or disable */
			if( MEXTI_ENABLE ==ARG_pconfigPinConfig->Mode)
			{
				EXTI->IMR |= 1 << ARG_pconfigPinConfig->Exti_Num ;
			}
			else
			{
				EXTI->IMR &= ~(1 << ARG_pconfigPinConfig->Exti_Num );
			}
		
			/* Save the CallBack Function to The Global Array*/
			G_pvoidfCallbackFuncArr[ARG_pconfigPinConfig->Exti_Num] = ARG_pconfigPinConfig->CallBackFunc;
		
		}
		else 
		{
			L_stderrState = E_NOK;
		}
		
	}

	return L_stderrState;
}

/* in case we need to change the trigger mode in Run time */
STD_error_t MEXTI_stderrSetTrigger			(u8  ARG_u8MEXTILineNum ,u8 ARG_u8TriggerMode )
{
	STD_error_t L_stderrState=E_OK;

	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		switch(ARG_u8TriggerMode)
		{
		case MEXTI_RAISING_TRIGGER:
			/* SET Rising Clear Falling */
			EXTI->RTSR |= 	1<< ARG_u8MEXTILineNum;
			EXTI->FTSR &= ~(1<< ARG_u8MEXTILineNum); 
			break;
		case MEXTI_FALLING_TRIGGER:
			/* SET Falling Clear Rising */
			EXTI->FTSR |= 	1<< ARG_u8MEXTILineNum;
			EXTI->RTSR &= ~(1<< ARG_u8MEXTILineNum); 
			break;
		case MEXTI_RIS_FALL_TRIGGER:
			/* SET Falling SET Rising */
			EXTI->RTSR |= 	1<< ARG_u8MEXTILineNum;
			EXTI->FTSR |= 	1<< ARG_u8MEXTILineNum; 	 
			break;
		default: L_stderrState = E_NOK;
		}
			
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MEXTI_stderrClearPendingFlag	(u8  ARG_u8MEXTILineNum)
{
	STD_error_t L_stderrState=E_OK;
	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<ARG_u8MEXTILineNum; /* 0 doesn't affect */
	
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MEXTI_stderrGetPendingFlag		(u8* ARG_PenValue, u8 ARG_u8MEXTILineNum)
{
	STD_error_t L_stderrState=E_OK;
	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/* Read PR[x] bit */
		*ARG_PenValue= (EXTI->PR >> ARG_u8MEXTILineNum) & 1 ;
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MEXTI_stderrIntEnable			(u8  ARG_u8MEXTILineNum)
{
	STD_error_t L_stderrState=E_OK;
	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/* Set bit enable  */
		EXTI->IMR |= 1<<ARG_u8MEXTILineNum;
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}


STD_error_t MEXTI_stderrIntDisable			(u8  ARG_u8MEXTILineNum)
{
	STD_error_t L_stderrState=E_OK;

	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/* Clear bit enable  */
		EXTI->IMR &= ~(1<<ARG_u8MEXTILineNum);
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;
}	

/* just set bit in SWIER */
STD_error_t MEXTI_stderrSWTrigger			(u8  ARG_u8MEXTILineNum)
{
	STD_error_t L_stderrState=E_OK;

	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/* Clear bit enable  */
		EXTI->SWIER |= 1<<ARG_u8MEXTILineNum;
	}
	else
	{
		L_stderrState=E_NOK;
	}
	
	return L_stderrState;	
}

STD_error_t MSYSCFG_stderrSelEXTI_Line(u8 ARG_u8MEXTILineNum, u8 ARG_u8Port)
{
	STD_error_t L_stderrState=E_OK;

	if(MEXTI_LIN22 >= ARG_u8MEXTILineNum )
	{
		/*Choose The Port to Have the EXTI*/
		u8 L_u8RegNum =  ARG_u8MEXTILineNum >> MSYSCFG_EXTI_SHIFT;
		u8 L_u8BitNum = (ARG_u8MEXTILineNum & MSYSCFG_Bit_MASK) << MSYSCFG_EXTI_SHIFT ; /* read 2-LSB in LINE NUM then Mul by 4 shift << 2 */

		SYSCFG->EXTICR[L_u8RegNum] &= ~(EXTI_PORT_MASK<<L_u8BitNum);
		SYSCFG->EXTICR[L_u8RegNum] |= (ARG_u8Port<<L_u8BitNum);

	}
	else
	{
		L_stderrState=E_NOK;
	}

	return L_stderrState;
}


void EXTI0_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(G_pvoidfCallbackFuncArr[MEXTI_LIN0] !=NULL_POINTER)
	{
		/*Clear Pending Flag*/
		MEXTI_stderrClearPendingFlag(MEXTI_LIN0);
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN0]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI1_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(G_pvoidfCallbackFuncArr[MEXTI_LIN1] !=NULL_POINTER)
	{
		/*Clear Pending Flag*/
		MEXTI_stderrClearPendingFlag(MEXTI_LIN1);
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN1]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI2_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(G_pvoidfCallbackFuncArr[MEXTI_LIN2] !=NULL_POINTER)
	{
		/*Clear Pending Flag*/
		MEXTI_stderrClearPendingFlag(MEXTI_LIN2);
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN2]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI3_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(G_pvoidfCallbackFuncArr[MEXTI_LIN3] !=NULL_POINTER)
	{
		/*Clear Pending Flag*/
		MEXTI_stderrClearPendingFlag(MEXTI_LIN3);
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN3]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI4_IRQHandler (void)
{
	/*Make Sure That CallBack Function No Null*/
	if(G_pvoidfCallbackFuncArr[MEXTI_LIN4] !=NULL_POINTER)
	{
		/*Clear Pending Flag*/
		MEXTI_stderrClearPendingFlag(MEXTI_LIN4);
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN4]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI9_5_IRQHandler (void)
{
	/* MACRO TO READ PF5  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR5_Pos) ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR5_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN5]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF6  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR6_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR6_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN6]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF7  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR7_Pos)  )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR7_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN7]();
	}
	else {	/* Do nothing MISRA Rule */}

	/* MACRO TO READ PF8  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR8_Pos) ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR8_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN8]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF9  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR9_Pos) ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR9_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN9]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}


void EXTI15_10_IRQHandler(void)
{
	/* MACRO TO READ PF10  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR10_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR10_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN10]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF11  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR11_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR11_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN11]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF12  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR12_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR12_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN12]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF13  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR13_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR13_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN13]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF14  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR14_Pos) )
	{
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR14_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN14]();
	}
	else {	/* Do nothing MISRA Rule */}
	
	/* MACRO TO READ PF15  */
	if( 1== MEXTIX_FLAG(EXTI->PR,MEXTI_PR_PR15_Pos) ){
		/*Clear Pending Flag*/
		EXTI->PR = 1<<MEXTI_PR_PR15_Pos;
		/*Call The Call Back Function*/
		G_pvoidfCallbackFuncArr[MEXTI_LIN15]();
	}
	else {	/* Do nothing MISRA Rule */}
	
}
