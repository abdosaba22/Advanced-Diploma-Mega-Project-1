/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 SysTICK								*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 6, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */


// #include "Stm32F103xx.h"
#include <MSYSTICK_Interface.h>
#include <MSYSTICK_Private.h>
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>


void STK_voidDelayms(uint32_t Delayms)
{	
	/* Disable Counter*/
	SYSTICK->CSR &= ~(1<<0);
	SYSTICK->CVR=0;
	Delayms*=T_MSTuS; /* to usc*/
	SYSTICK->CSR &= ~(1<<2);/* Choose Clock Source*/
	if(Delayms>T_OV){
		uint8_t counters=Delayms/T_OV;
		Delayms-=(counters*T_OV); /*remove overflow ticks*/
		SYSTICK->RVR=MAX_TICKS;
		/* Enable Counter*/
		SYSTICK->CSR |= 1<<0;
		while(counters>0){
			while( ( ( (SYSTICK->CSR )>>16 ) &1) == 0);
			counters--;
		}
		/* Disable Counter*/
		SYSTICK->CSR &= ~(1<<0);
		SYSTICK->CVR=0; /* Clear current value */
	}
	SYSTICK->RVR=Delayms*TO_TICK;/* Load the value of Delay */
	SYSTICK-> CSR|= 1;/* Enable Counter*/
	while( ( ( (SYSTICK->CSR )>>16 ) &1) == 0);/* Busy waiting until Counter is zero*/
	SYSTICK->CSR &= ~(1<<0);/* Disable Counter*/
}

void STK_voidDelayus(uint32_t Delayus)
{
	/*one over flow */
	SYSTICK->CSR &= ~(1<<0);/* Disable Counter*/
	SYSTICK->CVR=0;
	
	SYSTICK->CSR &= ~(1<<2);/* Choose Clock Source*/
	SYSTICK->RVR=Delayus*TO_TICK;/* Load the value of Delay */
	
	SYSTICK->CSR |= 1;/* Enable Counter*/
	while( ( ( (SYSTICK->CSR )>>16 ) &1) == 0);/* Busy waiting until Counter is zero*/
	SYSTICK->CSR &= ~(1<<0);/* Disable Counter*/
}
