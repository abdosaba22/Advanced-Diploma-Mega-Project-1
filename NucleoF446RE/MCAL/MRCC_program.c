/* ************************************************ */
/* Author      : 	Abdalrahman Amin                */
/* SWC         : 	Reset & Clock Control	        */
/* MCu         : 	Stm32F446RE		                */
/* Layer       : 	MCAL                            */
/* Version     : 	1.0                             */
/* Date        : 	September 12, 2023              */
/* Last Edit   : 	N/A			                    */
/* ************************************************ */

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MRCC_interface.h"
#include "MRCC_private.h"
#include "MRCC_config.h"

/********* used for Prebuild  *******/
void MRCC_voidInit (void)
{
	
	#if CLK_SOURCE == HSI
		/* Enable HSI CLOCK */
		SET_BIT(MRCC->CFGR,12);
		SET_BIT(MRCC->CR,RCC_CR_HSION);
		/* polling */
		while(GET_BIT(MRCC->CR,RCC_CR_HSIRDY)==0);

	#elif CLK_SOURCE == HSE

		#if HSE_SOURCE == HSE_CRYSTAL
			CLEAR_BIT(MRCC->CR,RCC_CR_HSEBYP); /* by pass */
		#elif HSE_SOURCE == HSE_EXTERNAL
			SET_BIT(MRCC->CR,RCC_CR_HSEBYP); /* by pass */
		#endif
		/* Enable HSE CLOCK */
		SET_BIT(MRCC->CR,RCC_CR_HSEON);
		/* polling */
		while(GET_BIT(MRCC->CR,RCC_CR_HSERDY)==0);
		
	#elif CLK_SOURCE == PLL
		
		#if  PLL_SOURCE == HSI_PLL
			/* Enable HSI CLOCK */
			SET_BIT(MRCC->CR,RCC_CR_HSION);
			/* polling */
			while(GET_BIT(MRCC->CR,RCC_CR_HSIRDY)==0);
			/* Choose HSI_PLL From PLLCFGR */
			CLEAR_BIT(MRCC->PLLCFGR,RCC_PLLCFGR_PLLSRC);
		
		#elif  PLL_SOURCE == HSE_PLL
			/* check for HSE EXT or Cry*/
			/* Enable HSI CLOCK */
			SET_BIT(MRCC->CR,RCC_CR_HSEON);
			/* polling */
			while(GET_BIT(MRCC->CR,RCC_CR_HSERDY)==0);
			/* Choose HSE_PLL From PLLCFGR */
			SET_BIT(MRCC->PLLCFGR,RCC_PLLCFGR_PLLSRC);
		
		#endif	
		/* configure PLLM , PLLN and PLLP */
		/* Clear PLLM PLLN PLLP  */
		MRCC->PLLCFGR &= ~( RCC_PLLCFGR_PLLP_MASK | RCC_PLLCFGR_PLLN_MASK | RCC_PLLCFGR_PLLM_MASK ) ;
		/* Set Modify the RCC_PLLCFGR with value of parameters */
		MRCC->PLLCFGR |= (PLL_P << RCC_PLLCFGR_PLLP_0) | (PLL_N << RCC_PLLCFGR_PLLN_0) | (PLL_M << RCC_PLLCFGR_PLLM_0) );
		/* Enable PLL CLOCK */
		SET_BIT(MRCC->CR,RCC_CR_PLLON);
		/* polling */
		while(GET_BIT(MRCC->CR,RCC_CR_PLLRDY)==0);
	#else 
		/* warning */
	
	#endif
	
	/* Choose The HCLK From SW */
	MRCC->CFGR &= ~(RCC_CFGR_SW_MASK);   /* ~(3<<0) */
	MRCC->CFGR |= (CLK_SOURCE << RCC_CFGR_SW_0);   /* (CLK_SOURCE<<0) */
	
}

/********* used for Postbuild  *******/
STD_error_t MRCC_stderrCLKConfig( MRCC_Config_t* ARG_pconfCLKConfig)
{
	STD_error_t L_stderrState= E_OK;
	
	/* check passed pointer not NULL */
	if(ARG_pconfCLKConfig != NULL_POINTER )
	{
		switch (ARG_pconfCLKConfig->CLK_Type)
		{
		case MRCC_CLKTYPE_HSI:
			/* Enable HSI */
			SET_BIT(MRCC->CR, RCC_CR_HSION);
			while( GET_BIT(MRCC->CR, RCC_CR_HSIRDY)== 0 );
		
		break;	
			
		case MRCC_CLKTYPE_HSE:
			
			/* 1st Config choose by pass or not */
			MRCC->CR &= ~(1<< RCC_CR_HSEBYP);
			MRCC->CR |= ( ARG_pconfCLKConfig->HSE_Type << RCC_CR_HSEBYP);
			/* Enable HSE */
			SET_BIT(MRCC->CR, RCC_CR_HSEON);
			while(GET_BIT(MRCC->CR, RCC_CR_HSERDY)  == 0 );				
			
		break;
			
		case MRCC_CLKTYPE_PLL:
			
			/* 1st Config PLL Src */
			if(ARG_pconfCLKConfig->PLL_SRC == MRCC_PLLSRC_HSI)
			{
				SET_BIT(MRCC->CR, RCC_CR_HSION);
				while( GET_BIT(MRCC->CR, RCC_CR_HSIRDY)== 0 );
				/* Choose HSI_PLL From PLLCFGR */
				CLEAR_BIT(MRCC->PLLCFGR,RCC_PLLCFGR_PLLSRC);
			}
			else
			{
				/* 1st Config choose by pass or not */
				MRCC->CR &= ~(1<< RCC_CR_HSEBYP);
				MRCC->CR |= ( ARG_pconfCLKConfig->HSE_Type << RCC_CR_HSEBYP);
				/* Enable HSE */
				SET_BIT(MRCC->CR, RCC_CR_HSEON);
				while(GET_BIT(MRCC->CR, RCC_CR_HSERDY)  == 0 );
				/* Choose HSE_PLL From PLLCFGR */
				SET_BIT(MRCC->PLLCFGR,RCC_PLLCFGR_PLLSRC);
			}
			/* configure PLLM , PLLN and PLLP */
			/* Clear PLLM PLLN PLLP  */
			MRCC->PLLCFGR &= ~( RCC_PLLCFGR_PLLP_MASK | RCC_PLLCFGR_PLLN_MASK | RCC_PLLCFGR_PLLM_MASK ) ;
			/* Set Modify the RCC_PLLCFGR with value of parameters */
			MRCC->PLLCFGR |= ( (ARG_pconfCLKConfig->PLLP_Value << RCC_PLLCFGR_PLLP_0) | (ARG_pconfCLKConfig->PLLN_Value << RCC_PLLCFGR_PLLN_0) | (ARG_pconfCLKConfig->PLLM_Value << RCC_PLLCFGR_PLLM_0) );
			/* Enable PLL CLOCK */
			SET_BIT(MRCC->CR,RCC_CR_PLLON);
			/* polling */
			while(GET_BIT(MRCC->CR,RCC_CR_PLLRDY)==0);
			
		break;
			
		default: L_stderrState= E_NOK; break; 
		
		}
		/* Choose The HCLK From SW */
		MRCC->CFGR &= ~(RCC_CFGR_SW_MASK);   /* ~(3<<0) */
		MRCC->CFGR |= (ARG_pconfCLKConfig->CLK_Type << RCC_CFGR_SW_0);   /* (CLK_SOURCE<<0) */
		
	}
	else
	{
		L_stderrState= E_NULL_POINTER;
	}
	return L_stderrState;
	
}


void MRCC_voidEnableCSS(void)
{
	SET_BIT( MRCC->CR, RCC_CR_CSSON );
	
}

void MRCC_voidDisableCSS(void)
{
	CLEAR_BIT( MRCC->CR, RCC_CR_CSSON );
	
}

/**********************************************************
*	we have 4 Reg each 32-bit if we choose APB2_USART1_EN which = 100
*	0b01100100 in binary if we read only 5-LSB [4:0] it will indicate 
*	the bit num in REGX cause 32 is 2^5 then n = 5 bits 
*	to read the Reg num we need to read bits[6:5] 
*   then  APB2_USART1_EN Bit is 0b00100 ->4 & Reg is num 3 0b011
*	we have AHB1, AHB2, APB1 and APB2 
*			  0  ,  1  ,  2  ,  3 
******************************************************/
STD_error_t MRCC_stderrEnablePeripheralClock (MRCCPeripheral_t ARG_perPeripheral)
{
	STD_error_t L_stderrState= E_OK;
	
	if(ARG_perPeripheral < RCC_PERIPHERAL_MAX)
	{	
		u8 L_u8PeripheralBit = (ARG_perPeripheral & RCC_PERIPHERAL_BIT_MASK) ; // read [4:0] 
		u8 L_u8PeripheralReg = ( (ARG_perPeripheral >> 5) & RCC_PERIPHERAL_REG_MASK ); // read [6:5]
		if(L_u8PeripheralReg < APB1_BUS )
		{
			SET_BIT( MRCC->AHBENR[L_u8PeripheralReg] ,L_u8PeripheralBit );
		}
		else
		{
			SET_BIT( MRCC->APBENR[L_u8PeripheralReg-2] ,L_u8PeripheralBit );
		}
	}
	else 
	{
		L_stderrState = E_NOK;
	}

	return L_stderrState;
}

STD_error_t MRCC_stderrDisablePeripheralClock (MRCCPeripheral_t ARG_perPeripheral)
{
	STD_error_t L_stderrState= E_OK;
	
	if(ARG_perPeripheral < RCC_PERIPHERAL_MAX)
	{	
		u8 L_u8PeripheralBit = (ARG_perPeripheral & RCC_PERIPHERAL_BIT_MASK) ; // read [4:0] 
		u8 L_u8PeripheralReg = ( (ARG_perPeripheral >> 5) & RCC_PERIPHERAL_REG_MASK ); // read [6:5]
		if(L_u8PeripheralReg < APB1_BUS )
		{
			CLEAR_BIT( MRCC->AHBENR[L_u8PeripheralReg] ,L_u8PeripheralBit );
		}
		else
		{
			CLEAR_BIT( MRCC->APBENR[L_u8PeripheralReg] ,L_u8PeripheralBit );
		}
	}
	else 
	{
		L_stderrState = E_NOK;
	}
	
	return L_stderrState;
}

STD_error_t MRCC_stderrMCO1Config (MRCC_MCO1SRC_t ARG_mco1srcMCO1Source, MRCC_MCO1PRES_t ARG_mco1preMCO1Prescaler )
{
	/*
	 *	It is highly recommended to configure these bits only after reset 
	 *	before enabling the external oscillators and PLL.
	 */
	 
	/*
	 *  MCO1 pin has to be configured in alternate function mode
	 */
	STD_error_t L_stderrState= E_OK;

	if(ARG_mco1srcMCO1Source <=MCO1_PLL   && ARG_mco1preMCO1Prescaler <= MCO1_DIV_BY5)
	{
		/* Mask MCO1 bits */
		MRCC->CFGR &= ~( RCC_CFGR_MCO1PRE_MASK | RCC_CFGR_MCO1_MASK );
		MRCC->CFGR |=  (ARG_mco1srcMCO1Source<<RCC_CFGR_MCO1_0 ) | ( ARG_mco1preMCO1Prescaler <<RCC_CFGR_MCO1PRE_0 );

	}
	else
	{
		L_stderrState = E_NOK;
	}

	return L_stderrState;

}
