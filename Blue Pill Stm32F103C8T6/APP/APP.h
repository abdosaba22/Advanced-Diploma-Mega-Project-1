/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	APP	                            */
/* Version      : 	1.0                             */
/* Date         : 	December 14, 2023	            */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */

#ifndef _APP_H_
#define _APP_H_


/******** Function prototypes ******/
STD_error_t 	APP_stderrClockPins_init	(void);
STD_error_t 	APP_stderrPeripheral_init	(void);

STD_error_t 	APP_stderrDisplayAlarm		(void);
STD_error_t 	APP_stderrDisplayTime		(void);



void 			APP_voidFireAlarm			(void);/* Exti */
void			APP_voidReceivedBuffer		(void);/* SPI*/

#endif

