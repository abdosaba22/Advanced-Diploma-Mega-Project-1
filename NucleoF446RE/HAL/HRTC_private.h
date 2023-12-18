/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 RTC DS1307							*/
/* Layer       	:	 HAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 30, 2023					*/
/* Last Edit   	:	 December 5, 2023					*/
/* **************************************************** */


#ifndef _HRTC_PRIVATE_H_
#define _HRTC_PRIVATE_H_


/* Private Function used in driver scope */
u8 ConvetTo_BCD			(u8 ARG_u8DecimalVal);
u8 ConvertTo_Decimal	(u8 ARG_u8BCDVal);

/* Some private defines */
#define HRTC_ADDRESS          			0x68u
#define HRTC_REGISTER_ADDRESS 			0x00u

#define BIT_12_24_DISPLAY       			6u
#define AM_PM_BIT               			5u

#define SECOND                  			0u
#define MINUIT                  			1u
#define HOUR                    			2u
#define DAY                     			3u
#define DATE                    			4u
#define MONTH                   			5u
#define YEAR                    			6u
#define CH_BIT                  			7u
#define HRTC_BUFFER_SIZE      				7u
#define HOUR_MASK               			0b00011111
#define SECOND_MASK             			0b01111111


#endif
