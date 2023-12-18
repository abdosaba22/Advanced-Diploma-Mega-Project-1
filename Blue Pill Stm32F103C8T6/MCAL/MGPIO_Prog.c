/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 GPIO									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 10, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

// #include "Stm32f103xx.h"

#include <MGPIO_Interface.h>
#include <MGPIO_Private.h>
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>




/* STM32F103C8t6 port A to port D*/

/* Static Array of 4 Pointers --> The GPIO Ports */
static GPIO_RegDef_t * GPIOPortArray[3] = {
	GPIOA, GPIOB, GPIOC};

uint8_t GPIO_u8PinInit(Port_t Port, PinNum_t Pin, PinMode_t Mode)
{
	uint8_t LocalErrorState=OK;
		if(Port <= PORTG && Pin <= PIN15)
		{
			if(Mode == I_PULL_DOWN  ) {
				Mode>>=1;
				GPIOPortArray[Port]->BRR  |= (ONEBIT_MSAK<<Pin);
			}
			else if(Mode ==I_PULL_UP){
				Mode>>=1;
				GPIOPortArray[Port]->BSRR |= (ONEBIT_MSAK<<Pin);
			}
			/* Set the Mode & CNF  of the Given PinY */
			if(Pin < PIN8)
			{
				/* Clear Mode & CNF Bits of the portX pinY */
				GPIOPortArray[Port]->CRL &= ~(MODECNFBIT_MASK << (MODECNFSHIFTPIN* Pin));
				GPIOPortArray[Port]->CRL |= (Mode << (MODECNFSHIFTPIN* Pin));
			}
			else
			{
				/* Clear Mode & CNF Bits of the portX pinY */
				Pin-=8;
				GPIOPortArray[Port]->CRH &= ~(MODECNFBIT_MASK << (MODECNFSHIFTPIN* Pin));
				GPIOPortArray[Port]->CRH |= (Mode << (MODECNFSHIFTPIN* Pin));
			}
			
		}	
		else LocalErrorState=NOK; // Wrong option	
	
	return LocalErrorState;
}


uint8_t GPIO_u8setpinValue(Port_t Port, PinNum_t Pin, PinVal_t PinVal)
{
	uint8_t LocalErrorState=OK;
	if( Port <= PORTD && Pin <= PIN15)
	{
		if(PinVal == PIN_HIGH){
			/* O/P  is HIGH */
			GPIOPortArray[Port]->BSRR |= (ONEBIT_MSAK<<Pin);
		}
		else {
			/* O/P  is LOW */
			GPIOPortArray[Port]->BRR |= (ONEBIT_MSAK<<Pin);
		}
	}	
	else LocalErrorState=NOK; // Wrong option
	
	return LocalErrorState;
}

uint8_t GPIO_u8TogglepinValue(Port_t Port, PinNum_t Pin)
{
	uint8_t LocalErrorState=OK;
	if( Port <= PORTD && Pin <= PIN15)
	{
		/*** Toggle the ODR for the Given PinY ***/
		GPIOPortArray[Port]->ODR ^=  ONEBIT_MSAK << Pin;
	}
	else LocalErrorState=NOK; // Wrong option
	
	return LocalErrorState;
}

uint8_t GPIO_u8ReadpinValue(Port_t Port, PinNum_t Pin, PinVal_t * PinValPtr)
{
	uint8_t LocalErrorState=OK;
	if( Port <= PORTD && Pin <= PIN15)
	{
		/*** Read the IDR for the Given PinY ***/
		*PinValPtr = (GPIOPortArray[Port]->IDR >> Pin) & ONEBIT_MSAK;
	}
	else LocalErrorState=NOK; // Wrong option
	
	return LocalErrorState;
}
