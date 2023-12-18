/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 RCC									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 1, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */


// #include "stm32f103xx.h"
#include <MRCC_Interface.h>
#include <MRCC_Private.h>
#include "LSTD_types.h"
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include <stdint.h>



uint8_t RCC_SetClksts( EN_CLKType_t ClkType , EN_CLKStatus_t ClkStatus ){
	uint8_t Startup_counter =0; // for time out
	switch(ClkType ){
	case HSE_CRYSTAL:
		if(ClkStatus == STATUS_ON){
			SETBIT(RCC->CR,HSEON); // set bit 16 HSE on
			//RCC->RCC_CR=0x00010000;
			do{
				Startup_counter++;
			}while( (READBIT(RCC->CR, HSERDY)==0 ) && (Startup_counter != STARTUP_TIMEOUT) );
			// HSERDY == 0 && Time out then return error
			 if(READBIT(RCC->CR, HSERDY)==0)  return ERROR_TIMEOUT;
			//else  HSERDY == 1
			/*
			 *  HSI turn off
			 */
		}
		else if(ClkStatus == STATUS_OFF){
			CLRBIT(RCC->CR,HSEON);
			while(READBIT(RCC->CR, HSERDY)!=0); // needs 6 cycles to fall down after HSEON reset.
		}
		break;

	case HSE_RC:
		if(ClkStatus == STATUS_ON){
			SETBIT(RCC->CR,HSEON); // set bit 16 HSE on
			do{
				Startup_counter++;
			}while( (READBIT(RCC->CR, HSERDY)==0 ) && (Startup_counter != STARTUP_TIMEOUT) );
			// HSERDY == 0 then return
			 if(READBIT(RCC->CR, HSERDY)==0)  return ERROR_TIMEOUT;
			//else  HSERDY == 1
			/*
			 *  HSI turn off
			 */
			SETBIT(RCC->CR,HSEBYB); // set bit 18 HSE by pass
		}
		else if(ClkStatus == STATUS_OFF){
			CLRBIT(RCC->CR,HSEON);
			while(READBIT(RCC->CR, HSERDY)!=0); // needs 6 cycles to fall down after HSEON reset.
		}
		break;

	case HSI:
		if(ClkStatus == STATUS_ON){
			SETBIT(RCC->CR,HSION); // set bit 16 HSI on
			do{
				Startup_counter++;
			}while( (READBIT(RCC->CR, HSIRDY)==0 ) && (Startup_counter != STARTUP_TIMEOUT) );
			// HSIRDY=0 return Time out
			if(READBIT(RCC->CR, HSIRDY)==0) return ERROR_TIMEOUT;
			// else complete
			RCC->CR &= ~(RCC_CLEAR_TRIM_VAL<<HSITRIM0); // clear trim
			SETBIT(RCC->CR,HSITRIM4); // for make TRRIM value = 16
		}

		else if(ClkStatus == STATUS_OFF){
			CLRBIT(RCC->CR,HSION);
			while(READBIT(RCC->CR, HSIRDY)!=0); // needs 6 cycles to fall down after HSION reset.
		}
		break;

	case PLL:
		if(ClkStatus == STATUS_ON){
			SETBIT(RCC->CR,PLLON); // set bit 24 PLL on
			do{
				Startup_counter++;
			}while( (READBIT(RCC->CR, PLLRDY)==0 ) && (Startup_counter != STARTUP_TIMEOUT) );
			// PLL == 0 then return
			if(READBIT(RCC->CR, PLLRDY)==0)  return ERROR_TIMEOUT;
			//else  PLLRDY == 1
			/*
			 *  HSI turn off
			 */
		}
		else if(ClkStatus == STATUS_OFF){
			CLRBIT(RCC->CR,PLLON);
			while(READBIT(RCC->CR, PLLRDY)!=0); // needs 6 cycles to fall down after HSEON reset.
		}
		break;

	default:
		break;
	}
	return OK;
}

void RCC_SetSysClk( EN_CLKType_t ClkType){
	switch(ClkType){
	case HSI:
		CLRBIT(RCC->CFGR,SW0);
		CLRBIT(RCC->CFGR,SW1);
		break;
	case HSE_CRYSTAL:
	case HSE_RC:
		SETBIT(RCC->CFGR,SW0);
		CLRBIT(RCC->CFGR,SW1);
		break;
	case PLL:
		SETBIT(RCC->CFGR,SW0);
		SETBIT(RCC->CFGR,SW1);
		break;
	default :
		break;
	}

}

void RCC_HSEConfig( EN_HSEConfig_t HSE_Config ){
	//  HSI ON & HSE OFF
	switch(HSE_Config){
	case HSE_NOTDIV:
		CLRBIT(RCC->CFGR,PLLXTPRE); // PLLXTPRE
		break;
	case HSE_DIV2:
		SETBIT(RCC->CFGR,PLLXTPRE); // PLLXTPRE use HSE /2 for PLL
		break;
	default :
		break;
	}

}

/*****************************

    NOTE before Configuration of PLL it must be OFF
	configure PLL set the MUL & the Clk source

 ******************************/
void RCC_PLLConfig( EN_PLLMul_t PLL_MulVal, EN_PLLSourceMux_t PLL_ClkSource){
	//RCC_SetClksts(PLL,STATUS_OFF); // PLL OFF before configuration to PLL
	switch(PLL_ClkSource){
	case PLL_HSE_DIVBY1:
		// HSE ON
		RCC_HSEConfig(HSE_NOTDIV);
		SETBIT(RCC->CR,PLLSRC); // PLLSRC choose HSE half
		break;
	case PLL_HSE_DIVBY2:
		// HSE ON
		RCC_HSEConfig(HSE_DIV2);
		SETBIT(RCC->CR,PLLSRC); // PLLSRC choose HSE half
		break;
	case PLL_HSI_DIVBY2:
		// HSI ON
		CLRBIT(RCC->CR,PLLSRC); // PLLSRC choose HSI half
		break;
	default :
		break;
	}
	// set MUL value first clear then Modify
	RCC->CFGR &= ~(RCC_PLL_MUL_RESET<<PLLMUL0); // Clear PUL val
	RCC->CFGR |= (PLL_MulVal << PLLMUL0); // set PUL MUL value

	//RCC->RCC_CFGR =((RCC->RCC_CFGR)& 0xFFC3FFFF) | (PLL_MulVal << PLLMUL0);
	//RCC_SetClksts(PLL,STATUS_ON);
	// RCC_SetSysClk(PLL); switch to pll
}

void RCC_AHBEnableClk( EN_AHB_Peripheral_t AHB_Peripheral){
	/*
	 	 	if we need to set the prescaler
	 	 	this prescaler to the AHB
		  	AHB prescaler HPRE[3:0]: AHB prescaler IN RCC_CFGR
			0xxx: SYSCLK not divided
			1000: SYSCLK divided by 2
			1001: SYSCLK divided by 4
			1010: SYSCLK divided by 8
			1011: SYSCLK divided by 16
			1100: SYSCLK divided by 64
			1101: SYSCLK divided by 128
			1110: SYSCLK divided by 256
			1111: SYSCLK divided by 512
	 */
	SETBIT(RCC->AHBENR,AHB_Peripheral); // enable the Clk for peripheral

}

void RCC_AHBDisableClk( EN_AHB_Peripheral_t AHB_Peripheral){
	CLRBIT(RCC->AHBENR,AHB_Peripheral); // Disable the Clk for peripheral

}

void RCC_APB2EnableClk( EN_APB2_Peripheral_t APB2_Peripheral){
	/*
	 	 	if we need to set the prescaler
	 	 	this prescaler to the APB2
		  	APB2 prescaler PPRE2[2:0]: APB2 prescaler in RCC_CFGR
			0xx: HCLK not divided
			100: HCLK divided by 2
			101: HCLK divided by 4
			110: HCLK divided by 8
			111: HCLK divided by 16
	 */
	SETBIT(RCC->APB2ENR,APB2_Peripheral); // enable the Clk for peripheral

}

void RCC_APB2DisableClk( EN_APB2_Peripheral_t APB2_Peripheral ){
	CLRBIT(RCC->APB2ENR,APB2_Peripheral); // Disable the Clk for peripheral
}

void RCC_APB1EnableClk( EN_APB1_Peripheral_t APB1_Peripheral){
	/*
	 	 	if we need to set the prescaler
	 	 	this prescaler to the APB1
		  	APB1 prescaler PPRE1[2:0]: APB1 prescaler in RCC_CFGR
			0xx: HCLK not divided
			100: HCLK divided by 2
			101: HCLK divided by 4
			110: HCLK divided by 8
			111: HCLK divided by 16
	 */
	SETBIT(RCC->APB1ENR,APB1_Peripheral); // enable the Clk for peripheral
}

void RCC_APB1DisableClk( EN_APB1_Peripheral_t APB1_Peripheral){
	CLRBIT(RCC->APB1ENR,APB1_Peripheral); // Disable the Clk for peripheral
}

