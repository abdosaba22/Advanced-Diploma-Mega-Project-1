/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 SysTick							*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 September 22, 2023					*/
/* **************************************************** */


/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MSYSTICK_interface.h"
#include "MSYSTICK_private.h"

/****************************/
static void (*G_pvoidCallBackFunc)(void);
/******************************/
volatile u32 G_u32TimeInms; /* used in func Milles */
volatile u32 G_u32TimeInS; /* used in ISR */
/******************************/
static volatile u8 G_u8CountMode;

STD_error_t MSTK_stderrInit(u8 ARG_u8ClockSrc)
{	
	STD_error_t L_stderrState = E_OK;
	if( ARG_u8ClockSrc <=1 )
	{
		/* Disable Counter & Clear 3-LSB */
		SYSTICK->CSR &= ~(0x07<<MSTK_BIT_ENABLE);
		/* Choose Clock Source */
		SYSTICK->CSR |= (ARG_u8ClockSrc << MSTK_BIT_CLKSOURCE);		
	}
	else
	{
		L_stderrState = E_NOK;
	}
	
	return L_stderrState;
}

STD_error_t MSTK_stderrStart_IT	(u32 ARG_u32Ticks, u8 ARG_u8Periodic, void (*ARG_pvoidfuncUserFunction)(void) )
{	
	STD_error_t L_stderrState = E_OK;

	if(ARG_pvoidfuncUserFunction != NULL_POINTER )
	{
		G_pvoidCallBackFunc= ARG_pvoidfuncUserFunction;
	
		SYSTICK->RVR= ARG_u32Ticks; /* Load the value of Ticks */
	
		SYSTICK-> CSR |= 0x03 ;/* Enable Counter & Interrupt request */
		
		G_u8CountMode = ARG_u8Periodic;
	}
	else
	{
		L_stderrState = E_NULL_POINTER;
	}

	return L_stderrState;	
}

/* used in case we use periodic and IRQ every 1ms */
u32 MSTK_u32Millis(void)
{
	return G_u32TimeInms;
}

void MSTK_voidBusyDelay(u32 ARG_u32Ticks)
{	
	SYSTICK->RVR= 2000000;
	SYSTICK->RVR= ARG_u32Ticks;/* Load the value of Ticks */
	
	SYSTICK-> CSR|= 1;/* Enable Counter*/
	
	while( ( ( (SYSTICK->CSR )>>16 ) &1) == 0);/* Busy waiting until Counter is zero*/
	
	MSTK_voidStop();
}

void MSTK_voidStop(void)
{
	SYSTICK->CSR &= ~(3<<0);/* Disable Counter & Disable Interrupt */
	
	SYSTICK->RVR = 0;
	SYSTICK->CVR = 0;
}

u32 MSTK_u32GetElapsedTime(void)
{
	/* Variable Stores Elapsed Time */
	u32 L_u32ElapsedTime;
	
	/*Calculate Elapsed Time*/
	L_u32ElapsedTime = (SYSTICK->RVR) - (SYSTICK -> CVR);
	
	/*Return Elapsed Time*/
	return L_u32ElapsedTime;
}

u32 MSTK_u32GetRemainingTime(void)
{
	/* Variable Stores Remaining Time*/
	u32 L_u32RemainingTime;
	
	/*Calculate Remaining Time*/
	L_u32RemainingTime = SYSTICK -> CVR ;
	
	/*Return Remaining Time*/
	return L_u32RemainingTime;
}

void SysTick_Handler(void)
{
	
	if (G_u8CountMode == MSTK_SINGLE_INTERVAL)
	{
		MSTK_voidStop();
	}
	else
	{
		if(G_u32TimeInS == 58)
		{
			/* Callback notification */
			G_pvoidCallBackFunc();
			G_u32TimeInS = 0;
		}
		G_u32TimeInms++; /* used for return n of ms in case we use ISR every 1ms */
		G_u32TimeInS++;
		/* wtite any value in VAL Clear interrupt flag */
		SYSTICK->CVR = 0;
	}
	

}
