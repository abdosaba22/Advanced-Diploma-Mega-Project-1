/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 SysTICK								*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 6, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef STK_PRIVATE_H_
#define STK_PRIVATE_H_

#define SYSTICK_BASE_ADDRESS		0xE000E010U

/*************** SYSTICK Register Definition Structure **********/
typedef struct {
	volatile uint32_t CSR;       /*!< SYSTICK Control and Status Register,                                   */
	volatile uint32_t RVR;       /*!< SYSTICK Reload Value Register,                               */
	volatile uint32_t CVR;       /*!< SYSTICK Current Value Register,                             */
	volatile uint32_t CALIB;     /*!< SYSTICK Calibration Value Register,                                 */	
} SYSTICK_RegDef_t;

/******************* SYSTICK Peripheral Definition **************/

#define SYSTICK 						((SYSTICK_RegDef_t*) SYSTICK_BASE_ADDRESS)


#define T_OV 	  			0xFFFFFFU   /* 8388608 usec   AHB/8 --> 8/8 = 1Mhz then Tclock=1us .. 2^24 *1  */   
#define T_MSTuS 			1000U       /* to convert to uSec */
#define TO_TICK				1U			/* every pulse take 0.5u then To get Nof pulses T_desiredinUs/0.5 then we will Multiply by 2*/	
#define MAX_TICKS			0xFFFFFFU

//#define F_SYSTICK			1000000U	
//#define T_TICK 			(1.0/F_SYSTICK)F
//#define T_OV				(MAX_TICKS*T_TICK)U 
//#define TO_TICK			(1/T_TICK)U	


#endif