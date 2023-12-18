/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 RCC									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 1, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef RCC_Interface_H_
#define RCC_Interface_H_


//#include "RCC_Private.h"
#include <stdint.h>

/************************

  Clock status options--> ON ,OFF

 ************************/
typedef enum {
	STATUS_OFF,STATUS_ON
} EN_CLKStatus_t;


/************************

  CLOCK type options--> HSE Crystal , HSE RC , HSI or PLL

 ************************/
typedef enum {
	HSE_CRYSTAL,HSE_RC,HSI,PLL
} EN_CLKType_t;


/************************

  HSE configuration--> HSE/2 , HSE/1

 ************************/
typedef enum {
	HSE_NOTDIV,HSE_DIV2
} EN_HSEConfig_t;

/************************

  PLL Multiplication options--> (*2 , *3 , *4 .... TO *16 )

 ************************/
typedef enum {
	PLL_MULBY2=2, PLL_MULBY3, PLL_MULBY4, PLL_MULBY5, PLL_MULBY6,
	PLL_MULBY7, PLL_MULBY8, PLL_MULBY9, PLL_MULBY10, PLL_MULBY11,
	PLL_MULBY12,PLL_MULBY13,PLL_MULBY14,PLL_MULBY15, PLL_MULBY16
} EN_PLLMul_t;


/************************

  PLL options--> HSE/2 , HSE , HSI/2

 ************************/
typedef enum {
	PLL_HSE_DIVBY1,PLL_HSE_DIVBY2,PLL_HSI_DIVBY2
} EN_PLLSourceMux_t;

typedef enum{
	E_TOK,ERROR_TIMEOUT
} EN_CLK_Return_t;

/************************

  AHB peripherals options-->

 ************************/
typedef enum {
	DMA1,DMA2,SRAM,FLITF=4,CRC=6,FSMC=8,SDIO=10
} EN_AHB_Peripheral_t;

/************************

  APB1 peripherals options-->

 ************************/
typedef enum {
	TIM2_EN
} EN_APB1_Peripheral_t;

/************************

  APB2 peripherals options-->

 ************************/
typedef enum {
	AFIO,IOPA=2,IOPB,IOPC,IOPD,IOPE,IOPF,IOPG,ADC1,ADC2,TIM1,SPI1,TIM8,USART1,ADC3,TIM9=19,TIM10,TIM11
} EN_APB2_Peripheral_t;

/**** bits ****/
typedef enum {
	HSION,HSIRDY,HSITRIM0=3,HSITRIM1,HSITRIM2,HSITRIM3,HSITRIM4,HSICAL0=8,HSEON=16,HSERDY,HSEBYB,CSSON,PLLON=24,PLLRDY
} EN_RCC_CRBITS_t;
/****  bits *****/
typedef enum {
	SW0,SW1,SWS0,SWS1,HPRE0,PPRE10=8,PPRE20=11,ADCPRE0=14,PLLSRC=16,PLLXTPRE,PLLMUL0,USBPRE=22,MCO0=24
} EN_RCC_CFGRBITS_t;



/* Functions prototype */
uint8_t RCC_SetClksts( EN_CLKType_t , EN_CLKStatus_t );
void RCC_SetSysClk( EN_CLKType_t );
void RCC_HSEConfig( EN_HSEConfig_t );
void RCC_PLLConfig( EN_PLLMul_t , EN_PLLSourceMux_t);
void RCC_AHBEnableClk( EN_AHB_Peripheral_t );
void RCC_AHBDisableClk( EN_AHB_Peripheral_t );
void RCC_APB2EnableClk( EN_APB2_Peripheral_t );
void RCC_APB2DisableClk( EN_APB2_Peripheral_t );
void RCC_APB1EnableClk( EN_APB1_Peripheral_t );
void RCC_APB1DisableClk( EN_APB1_Peripheral_t );


#endif
