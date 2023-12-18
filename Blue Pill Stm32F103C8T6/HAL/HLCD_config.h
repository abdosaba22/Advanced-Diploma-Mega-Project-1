/* ************************************************ */
/* Author      : Abd-alrahman Amin                  */
/* SWC         : LCD                                */
/* Layer       : HAL                                */
/* Version     : 1.1                                */
/* Date        : August 7, 2023                     */
/* Last Edit   : August 8, 2023	                    */
/* ************************************************ */


#ifndef _HLCD_CONFIG_H_
#define _HLCD_CONFIG_H_

#define HLCD_DATA_PORT 					PORTB /*Data port from D0:D7 */
#define HLCD_CTRL_PORT 					PORTA /*Control port for RS,EN and RW */


#define HLCD_D4_PIN 					PIN15
#define HLCD_D5_PIN 					PIN14
#define HLCD_D6_PIN 					PIN13
#define HLCD_D7_PIN 					PIN12

#define HLCD_RS_PIN 					PIN11
#define HLCD_EN_PIN 					PIN8


#endif
