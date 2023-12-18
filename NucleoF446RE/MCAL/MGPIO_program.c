/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 GPIO								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 15, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MGPIO_interface.h"
#include "MGPIO_private.h"

/* Static Array of 4 Pointers --> The GPIO Ports to avoid using "Switch(){ case: }" */
static MGPIO_REGDEf_t *G_pregdefPortArray[MGPIO_PERIPHERAL_NUM] = 
{
	GPIOA, GPIOB,
	GPIOC, GPIOD
};

/**** This function initializes the GPIO pin according to the parameter ****/	
STD_error_t MGPIO_stderrPinConfig	(const MGPIO_CONFIG_t * ARG_configPinConfig)
{
	STD_error_t L_stderrState= E_OK;
	/* Check NULL pointer */
	if(NULL_POINTER != ARG_configPinConfig)
	{
		/* check Port & pin parameter */
		if(ARG_configPinConfig->Port <= PORTD && ARG_configPinConfig->Pin <= PIN15 )
		{
			/* Set Mode value in MODE Reg, Mask then OR */
			G_pregdefPortArray[ARG_configPinConfig->Port]->MODER &= ~( MGPIO_MODEBIT_MASK << (ARG_configPinConfig->Pin * MGPIO_MODE_NBITS) ); /* each pin has 2 bits so Mul pin * 2 to get bit */
			G_pregdefPortArray[ARG_configPinConfig->Port]->MODER |= ( ARG_configPinConfig->Mode << (ARG_configPinConfig->Pin * MGPIO_MODE_NBITS) ); 
			
			/* Set PullType value in PUPD Reg, Mask then OR */
			G_pregdefPortArray[ARG_configPinConfig->Port]->PUPDR &= ~( MGPIO_PUPDBIT_MASK << (ARG_configPinConfig->Pin * MGPIO_PUPD_NBITS) ); /* each pin has 2 bits so Mul pin * 2 to get bit */
			G_pregdefPortArray[ARG_configPinConfig->Port]->PUPDR |= ( ARG_configPinConfig->PullType << (ARG_configPinConfig->Pin * MGPIO_PUPD_NBITS) );
			
			/* special configuration in case of O/P or AF Mode */
			if( OUTPUT==ARG_configPinConfig->Mode || ALTERNATE_FUNCTION==ARG_configPinConfig->Mode)
			{   /* Configure  OSPEEDR & OTYPER for the Given Pin */
				
				/* Set Speed value in OSPEED Reg, Mask then OR */
				G_pregdefPortArray[ARG_configPinConfig->Port]->OSPEEDR &= ~( MGPIO_SPEEDBIT_MASK << (ARG_configPinConfig->Pin * MGPIO_SPEED_NBIS) ); /* each pin has 2 bits so Mul pin * 2 to get bit */
				G_pregdefPortArray[ARG_configPinConfig->Port]->OSPEEDR |= ( ARG_configPinConfig->Speed << (ARG_configPinConfig->Pin * MGPIO_SPEED_NBIS) );
				
				/* Set OutputType value in OTYPE Reg, Mask then OR */
				G_pregdefPortArray[ARG_configPinConfig->Port]->OTYPER &= ~( MGPIO_SPEEDBIT_MASK << ARG_configPinConfig->Pin ); 
				G_pregdefPortArray[ARG_configPinConfig->Port]->OTYPER |= ( ARG_configPinConfig->OutputType << ARG_configPinConfig->Pin ); 
				
				/* in case of AF need to assign Value of ARF */
				if( ALTERNATE_FUNCTION==ARG_configPinConfig->Mode )
				{	
					/* Bit[3] indicate the Reg*/
					u8 L_u8RegARF = ARG_configPinConfig->Pin >> MGPIO_ARFLH_PIN_SHIFITR ; /* ARF[x] REG can access for only 8 pins so pin>>3 */
					u8 L_u8BitARF = (ARG_configPinConfig->Pin & MGPIO_ARFLH_PIN_MASK) * MGPIO_ALTFUNC_NBITS ; /* each pin has 4 bits in ARF so Mul by 4*/
					
					/* Set AltFunc value in ARF[x] Reg, Mask then OR */
					G_pregdefPortArray[ARG_configPinConfig->Port]->ARF[L_u8RegARF] &= ~( MGPIO_ALTFUNCBIT_MASK << L_u8BitARF ); 
					G_pregdefPortArray[ARG_configPinConfig->Port]->ARF[L_u8RegARF] |= ( ARG_configPinConfig->AltFunc << L_u8BitARF ); 
				
				}
				else{ /* Do nothing, MISRA Rule */ }
		
			}
			else{ /* Do nothing, MISRA Rule */ }
			
		}
		else
		{
			L_stderrState= E_NOK; /* Error value*/
		}
	}
	else 
	{
		L_stderrState= E_NULL_POINTER;
	}
	
	return L_stderrState;
}

/**** This function outputs a certain value on an output pin ****/
STD_error_t MGPIO_stderrSetPinValue		(MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum, MGPIO_PINVAL_t ARG_PinVal)
{
	STD_error_t L_stderrState=E_OK;

	if( ARG_portPort <= PORTD && ARG_numPinNum <= PIN15)
	{
		/*  
		 *	toggle pin value to calc offset 16 or not 
		 *	case pin value is High 1 then tog will be 0 Mul by 16 = 0 then offset is 0 so bits range 0->15
		 *	case pin value is Low 0 then tog will be 1 Mul by 16 = 16 then offset is 16 so bits range 0->15
		 */
		/* also we can use vol u16 BSRR[2] in Reg Def */ 
		u8 L_u8BitOffset = (ARG_PinVal^1)* MGPIO_BSRR_OFFSET ; /* the bits[31:16] for Reset */
		/*** Toggle the ODR Value thrugh BSRR for the Given PinY ***/
		G_pregdefPortArray[ARG_portPort]->BSRR =  (MGPIO_ODRBIT_MASK<< (ARG_numPinNum+L_u8BitOffset) );
	}	
	else
	{
		L_stderrState= E_NOK; /* Error value*/
	}
	

	return L_stderrState;
	
}

/**** Theis function Toggles the value on an output pin ****/
STD_error_t MGPIO_stderrTogglePinValue	(MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum)
{
	STD_error_t L_stderrState=E_OK;

	if( ARG_portPort <= PORTD && ARG_numPinNum <= PIN15)
	{
		/*** Toggle the ODR Value for the Given PinY ***/
		G_pregdefPortArray[ARG_portPort]->ODR ^=  (MGPIO_ODRBIT_MASK<< ARG_numPinNum);
	}	
	else
	{
		L_stderrState= E_NOK; /* Error value*/
	}
	

	return L_stderrState;
	
}

/**** This function Reads a certain value on an input pin ****/
STD_error_t MGPIO_stderrReadPinValue	(u8* ARG_pu8PinVal, MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum)
{
	STD_error_t L_stderrState=E_OK;
	/* Make sure that the pointer Was Allocated */
	if(ARG_pu8PinVal != NULL_POINTER)
	{
		if( ARG_portPort <= PORTD && ARG_numPinNum <= PIN15)
		{
			/*** Read the IDR Value for the Given PinY ***/
			*ARG_pu8PinVal = (G_pregdefPortArray[ARG_portPort]->IDR >> ARG_numPinNum) & MGPIO_IDRBIT_MASK;
		}	
		else
		{
			L_stderrState= E_NOK; /* Error value*/
		}
		
	}
	else 
	{
		L_stderrState= E_NULL_POINTER;
	}
	
	return L_stderrState;
}
