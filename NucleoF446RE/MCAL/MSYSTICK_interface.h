/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 SysTick							*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 September 22, 2023					*/
/* **************************************************** */

#ifndef _MSYSTICK_INTERFACE_H_
#define _MSYSTICK_INTERFACE_H_


STD_error_t MSTK_stderrInit(u8 ARG_u8ClockSrc);

STD_error_t MSTK_stderrStart_IT	(u32 ARG_u32Ticks, u8 ARG_u8Periodic, void (*ARG_pvoidfuncUserFunction)(void) );

u32 MSTK_u32Millis(void);

void MSTK_voidBusyDelay(u32 ARG_u32Ticks);

void MSTK_voidStop(void);

u32 MSTK_u32GetElapsedTime(void);

u32 MSTK_u32GetRemainingTime(void);

#define MSTK_CLOCKSRC_AHB_8			  	0U
#define MSTK_CLOCKSRC_AHB  			  	1U

#define MSTK_SINGLE_INTERVAL			0U
#define MSTK_PERIOD_INTERVAL			1U


#endif