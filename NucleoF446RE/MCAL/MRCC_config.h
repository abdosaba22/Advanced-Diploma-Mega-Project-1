/* ************************************************ */
/* Author      : 	Abdalrahman Amin                */
/* SWC         : 	Reset & Clock Control	        */
/* MCu         : 	Stm32F446RE		                */
/* Layer       : 	MCAL                            */
/* Version     : 	1.0                             */
/* Date        : 	September 12, 2023              */
/* Last Edit   : 	N/A			                    */
/* ************************************************ */

#ifndef _MTIM_CONFIG_H_
#define _MTIM_CONFIG_H_

/* 	
 *		1- HSI
 *		2- HSE
 *		3- PLL
 */
#define CLK_SOURCE   	HSE


/* 	
 *		1- HSE_CRYSTAL
 *		2- HSE_EXTERNAL
 */
#define HSE_SOURCE 		HSE_CRYSTAL


/* 	
 *		1- HSI_PLL
 *		2- HSE_PLLL
 */
#define PLL_SOURCE		HSI_PLL


/*
 *  2<= PLL_M >=63 
 */
#define PLL_M 	8u		


/*
 *  192<= PLL_N >=432   
 */
#define PLL_N 	336u		


/*
 *  2, 4, 6, 8   
 */
#define PLL_P 	8u		


#endif
