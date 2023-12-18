/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 SysTick							*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 September 22, 2023					*/
/* **************************************************** */

#ifndef _MSYSTICK_PRIVATE_H_
#define _MSYSTICK_PRIVATE_H_


/******************* SYSTICK Peripheral Base Addresses ********************/ 

#define MSYSTICK_BASE_ADDRESS		0xE000E010U
/**********************************************************************/


/***************** SYSTICK Register Definition Structure ***************/

typedef struct 
{
  volatile u32	 CSR;       /*!< SYSTICK Control and Status Register,                        */
  volatile u32	 RVR;       /*!< SYSTICK Reload Value Register,                              */
  volatile u32	 CVR;       /*!< SYSTICK Current Value Register,                             */
  volatile u32	 CALIB;     /*!< SYSTICK Calibration Value Register,                         */	
} MSYSTICK_REGDEF_t;
/************************************************************************/


/******************* SYSTICK Peripheral Definition **************/

#define SYSTICK 			 ((MSYSTICK_REGDEF_t*) MSYSTICK_BASE_ADDRESS)
/*****************************************************************/


/*********** private defines ***********/


/* in Config file*/
#define AHB_CLK				16UL /* 16Mh */

#define TMS_TUS 			1000U       /* to convert to uSec */
#define MAX_TICKS			0xFFFFFFU

/*SysTick Control Register Bits*/
#define MSTK_BIT_ENABLE     		0
#define MSTK_BIT_TICKINT    		1
#define MSTK_BIT_CLKSOURCE  		2
#define MSTK_BIT_COUNTFLAG  		16



#endif