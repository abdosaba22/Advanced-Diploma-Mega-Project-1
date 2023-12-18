/* ************************************************ */
/* Author      : 	Abdalrahman Amin                */
/* SWC         : 	Reset & Clock Control	        */
/* MCu         : 	Stm32F446RE		                */
/* Layer       : 	MCAL                            */
/* Version     : 	1.0                             */
/* Date        : 	September 12, 2023              */
/* Last Edit   : 	N/A			                    */
/* ************************************************ */


#ifndef _MRCC_INTERFACE_H_
#define _MRCC_INTERFACE_H_



/************************ Defines ********************************/

#define HSI				0u
#define HSE				1u
#define PLL				2u

/* CLK Type options   */
typedef enum 
{
    MRCC_CLKTYPE_HSI ,
	MRCC_CLKTYPE_HSE ,
    MRCC_CLKTYPE_PLL 
} MRCC_CLKType_t;

/********************************************************************/
#define AHB1_BUS		0u
#define AHB2_BUS		1u
#define APB1_BUS		2u
#define APB2_BUS		3u
/********************************************************************/
#define HSE_CRYSTAL		0u
#define HSE_EXTERNAL	1u

/* HSE options */
typedef enum 
{
	MRCC_HSE_CRYSTAL , 
	MRCC_HSE_EXTERNAL /* By pass */
} MRCC_HSEType_t;

/********************************************************************/
#define HSI_PLL			0u
#define HSE_PLL			1u

/* PLL Source Mux options */
typedef enum 
{
	MRCC_PLLSRC_HSI ,
	MRCC_PLLSRC_HSE
} MRCC_PLLSRC_t;


/* PLL input frequency division factor (PLLM) enumeration , 2 ≤ PLLM ≤ 63  */
typedef enum {
    MRCC_PLLM_DIV2 = 2,
    MRCC_PLLM_DIV3 ,
    MRCC_PLLM_DIV4 ,
    MRCC_PLLM_DIV5 ,
    MRCC_PLLM_DIV6 ,
    MRCC_PLLM_DIV7 ,
    MRCC_PLLM_DIV8 ,
    MRCC_PLLM_DIV9 ,
    MRCC_PLLM_DIV10 ,
    MRCC_PLLM_DIV11 ,
    MRCC_PLLM_DIV12 ,
    MRCC_PLLM_DIV13 ,
    MRCC_PLLM_DIV14 ,
    MRCC_PLLM_DIV15 ,
    MRCC_PLLM_DIV16 ,
    MRCC_PLLM_DIV17 ,
    MRCC_PLLM_DIV18 ,
    MRCC_PLLM_DIV19 ,
    MRCC_PLLM_DIV20 ,
    MRCC_PLLM_DIV21 ,
    MRCC_PLLM_DIV22 ,
    MRCC_PLLM_DIV23 ,
    MRCC_PLLM_DIV24 ,
    MRCC_PLLM_DIV25 ,
    MRCC_PLLM_DIV26 ,
    MRCC_PLLM_DIV27 ,
    MRCC_PLLM_DIV28 ,
    MRCC_PLLM_DIV29 ,
    MRCC_PLLM_DIV30
	/*  to  63*/
} MRCC_PLLM_t;

/* PLL multiplication factor (PLLN) enumeration , 192 ≤ PLLN ≤ 432 */
typedef enum {
	MRCC_PLLN_MUL192 = 192,
	MRCC_PLLN_MUL193,
	MRCC_PLLN_MUL194,
	MRCC_PLLN_MUL195,
	MRCC_PLLN_MUL196,
	MRCC_PLLN_MUL197,
	MRCC_PLLN_MUL198,
	MRCC_PLLN_MUL199,
	MRCC_PLLN_MUL200,
	MRCC_PLLN_MUL201,
	MRCC_PLLN_MUL202,
	MRCC_PLLN_MUL203,
	MRCC_PLLN_MUL204,
	MRCC_PLLN_MUL205,
	MRCC_PLLN_MUL206,
	MRCC_PLLN_MUL207,
	MRCC_PLLN_MUL208,
	MRCC_PLLN_MUL209,
	MRCC_PLLN_MUL210,
	MRCC_PLLN_MUL211,
	MRCC_PLLN_MUL212,
	MRCC_PLLN_MUL213,
	MRCC_PLLN_MUL214,
	MRCC_PLLN_MUL215,
	MRCC_PLLN_MUL216,
	MRCC_PLLN_MUL217,
	MRCC_PLLN_MUL218,
	MRCC_PLLN_MUL219,
	MRCC_PLLN_MUL220,
	MRCC_PLLN_MUL221,
	MRCC_PLLN_MUL222,
	MRCC_PLLN_MUL223,
	MRCC_PLLN_MUL224,
	MRCC_PLLN_MUL225,
	MRCC_PLLN_MUL226,
	MRCC_PLLN_MUL227,
	MRCC_PLLN_MUL228,
	MRCC_PLLN_MUL229,
	MRCC_PLLN_MUL230,
	MRCC_PLLN_MUL231,
	MRCC_PLLN_MUL232,
	MRCC_PLLN_MUL233,
	MRCC_PLLN_MUL234,
	MRCC_PLLN_MUL235,
	MRCC_PLLN_MUL236,
	MRCC_PLLN_MUL237,
	MRCC_PLLN_MUL238,
	MRCC_PLLN_MUL239,
	MRCC_PLLN_MUL240,
	MRCC_PLLN_MUL241,
	MRCC_PLLN_MUL242,
	MRCC_PLLN_MUL243,
	MRCC_PLLN_MUL244,
	MRCC_PLLN_MUL245,
	MRCC_PLLN_MUL246,
	MRCC_PLLN_MUL247,
	MRCC_PLLN_MUL248,
	MRCC_PLLN_MUL249,
	MRCC_PLLN_MUL250,
	MRCC_PLLN_MUL251,
	MRCC_PLLN_MUL252,
	MRCC_PLLN_MUL253,
	MRCC_PLLN_MUL254,
	MRCC_PLLN_MUL255,
	MRCC_PLLN_MUL256,
	MRCC_PLLN_MUL257,
	MRCC_PLLN_MUL258,
	MRCC_PLLN_MUL259,
	MRCC_PLLN_MUL260,
	MRCC_PLLN_MUL261
	/*  to  432*/
} MRCC_PLLN_t;

/* PLL main division factor (PLLP) enumeration */
typedef enum {
    MRCC_PLLP_DIV2 = 0,
    MRCC_PLLP_DIV4 ,
    MRCC_PLLP_DIV6 ,
    MRCC_PLLP_DIV8
} MRCC_PLLP_t;

/* MCO1 clock source selection (MCO1) enumeration */
typedef enum {
	MCO1_HSI,
	MCO1_LSE,
	MCO1_HSE,
	MCO1_PLL
}MRCC_MCO1SRC_t;

/* MCO1 Prescaler (MCO1PRE) enumeration */
typedef enum {
	/* from 0 to 3 NO Div */
	MCO1_NODIV=0,
	MCO1_DIV_BY2=4,
	MCO1_DIV_BY3,
	MCO1_DIV_BY4,
	MCO1_DIV_BY5
}MRCC_MCO1PRES_t;


/*************** MRCC Struct configuration ************/
typedef struct 
{
	MRCC_CLKType_t CLK_Type;
	MRCC_HSEType_t HSE_Type;
	MRCC_PLLSRC_t  PLL_SRC;
	MRCC_PLLM_t    PLLM_Value;
	MRCC_PLLN_t    PLLN_Value;
	MRCC_PLLP_t    PLLP_Value;
	
	/**  add HPRE and PPRE1 & PPRE2 Later **/
	
	
} MRCC_Config_t;


/**********************************************************
*	we have 4 Reg each 32-bit if we choose APB2_USART1_EN which = 100
*	0b01100100 in binary if we read only 5-LSB [4:0] it will indicate 
*	the bit num in REGX cause 32 is 2^5 then n = 5 bits 
*	to read the Reg num we need to read bits[6:5] 
*   then  APB2_USART1_EN Bit is 0b00100 ->4 & Reg is num 3 0b011
*	we have AHB1, AHB2, APB1 and APB2 
*			  0  ,  1  ,  2  ,  3 
******************************************************/
typedef enum 
{
    /* AHB1 Peripherals */
	AHB1_GPIOA_EN = 0,
	AHB1_GPIOB_EN ,
	AHB1_GPIOC_EN ,
	AHB1_GPIOD_EN ,
	AHB1_GPIOE_EN ,
	AHB1_GPIOH_EN=7 ,
	AHB1_CRC_EN=12,
	AHB1_DMA1_EN=21,
	AHB1_DMA2_EN,
	/* AHB2 Peripherals */
	AHB2_OTGFS_EN=39, 
	/* APB1 Peripherals */
	APB1_TIM2_EN =64,
	APB1_TIM3_EN,
	APB1_TIM4_EN,
	APB1_TIM5_EN,
	APB1_TIM6_EN,
	APB1_TIM7_EN,
	APB1_TIM12_EN,
	APB1_TIM13_EN,
	APB1_TIM14_EN,
	APB1_WWDG_EN =75,
	APB1_SPI2_EN =78,
	APB1_SPI3_EN,
	APB1_SPDIFRXEN_EN,
	APB1_USART2_EN,
	APB1_USART3_EN,
	APB1_UART4_EN,
	APB1_UART5_EN,
	APB1_I2C1_EN,
	APB1_I2C2_EN,
	APB1_I2C3_EN,
	APB1_FMP12C1_EN,
	APB1_CAN1_EN,
	APB1_CAN2_EN,
	APB1_CEC_EN,
	APB1_PWR_EN,
	APB1_DAC_EN,
	/* APB1 Peripherals */
	APB2_TIM1_EN = 96,
    APB2_USART1_EN = 100,
    APB2_USART6_EN,
    APB2_ADC1_EN = 104,
    APB2_SDIO_EN=107,
    APB2_SPI1_EN,
    APB2_SPI4_EN,
	APB2_SYSCFG_EN ,
    APB2_TIM9_EN = 112,
    APB2_TIM10_EN,
    APB2_TIM11_EN
	
}MRCCPeripheral_t;

/************************ Func Prototypes ****************************/

void MRCC_voidInit (void);

STD_error_t MRCC_stderrCLKConfig( MRCC_Config_t* ARG_pconfCLKConfig);

void MRCC_voidEnableCSS(void);
void MRCC_voidDisableCSS(void);

STD_error_t MRCC_stderrEnablePeripheralClock (MRCCPeripheral_t ARG_perPeripheral);

STD_error_t MRCC_stderrDisablePeripheralClock (MRCCPeripheral_t ARG_perPeripheral);

STD_error_t MRCC_stderrMCO1Config (MRCC_MCO1SRC_t ARG_mco1srcMCO1Source, MRCC_MCO1PRES_t ARG_mco1preMCO1Prescaler );


#endif
