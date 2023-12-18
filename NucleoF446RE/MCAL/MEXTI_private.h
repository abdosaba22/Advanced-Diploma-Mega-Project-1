/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 EXT Interrupt						*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

#ifndef _MEXTI_PRIVATE_H_
#define _MEXTI_PRIVATE_H_


/********************* MEXTI Peripheral Base Addresse *****************/
#define MEXTI_BASE_ADDRESS				0x40013C00UL

/********************* MSYSCFG Peripheral Base Addresse *****************/
#define MSYSCFG_BASE_ADDRESS			0x40013800UL

/********************************************************************/


/************************* MEXTI Register Definition Structure ***********************/

typedef struct
{
	volatile u32 IMR;               /*Interrupt mask register*/
	volatile u32 EMR;               /*Event mask register*/
	volatile u32 RTSR;              /*Rising trigger selection register*/
	volatile u32 FTSR;              /*Falling trigger selection register*/
	volatile u32 SWIER;             /*Software interrupt event register*/
	volatile u32 PR;                /*Pending register*/
}MEXTI_REGDEF_t;


/************** SYSCFG Register Definition Structure ****************/
typedef struct
{
	volatile u32 MEMRMP;			/*SYSCFG memory remap register*/
	volatile u32 PMC;				/*SYSCFG peripheral mode configuration register*/
	volatile u32 EXTICR[4];			/*SYSCFG external interrupt configuration registers*/
	u32 Reserved[2];
	volatile u32 CMPCR;				/*Compensation cell control register*/
	u32 Reserved2[2];
	volatile u32 CFGR;				/*SYSCFG configuration register*/
}MSYSCFG_REGDEF_t;

/*************************************************************/


/************************ Peripheral Definitions **********************/

/*********************** MEXTI Peripheral Definitions **************************/
#define EXTI					((MEXTI_REGDEF_t*)MEXTI_BASE_ADDRESS)

/*********************** MSYSCFG Peripheral Definitions **************************/
#define SYSCFG					((MSYSCFG_REGDEF_t*)MSYSCFG_BASE_ADDRESS)

/*************************************************************************/

/************************* private Defines  *******************/

#define MEXTI_NUM					23U

#define MEXTI_PR_PR0_Pos  			 0U
#define MEXTI_PR_PR1_Pos  			 1U
#define MEXTI_PR_PR2_Pos  			 2U
#define MEXTI_PR_PR3_Pos  			 3U
#define MEXTI_PR_PR4_Pos  			 4U
#define MEXTI_PR_PR5_Pos  			 5U
#define MEXTI_PR_PR6_Pos  			 6U
#define MEXTI_PR_PR7_Pos  			 7U
#define MEXTI_PR_PR8_Pos  			 8U
#define MEXTI_PR_PR9_Pos  			 9U
#define MEXTI_PR_PR10_Pos 			10U
#define MEXTI_PR_PR11_Pos 			11U
#define MEXTI_PR_PR12_Pos 			12U
#define MEXTI_PR_PR13_Pos 			13U
#define MEXTI_PR_PR14_Pos 			14U
#define MEXTI_PR_PR15_Pos 			15U
#define MEXTI_PR_PR16_Pos 			16U
#define MEXTI_PR_PR17_Pos 			17U
#define MEXTI_PR_PR18_Pos 			18U
#define MEXTI_PR_PR19_Pos 			19U

#define MEXTIX_FLAG(REG,LINE)  ( (REG >> LINE) & 1 )



#define MSYSCFG_EXTI_SHIFT				2U		
#define MSYSCFG_Bit_MASK				0x03U
#define EXTI_PORT_MASK					0b1111U



#endif
