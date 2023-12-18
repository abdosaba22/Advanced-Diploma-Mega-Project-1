/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 RTC DS1307							*/
/* Layer       	:	 HAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 30, 2023					*/
/* Last Edit   	:	 December 5, 2023					*/
/* **************************************************** */


#ifndef _HRTC_INTERFACE_H_
#define _HRTC_INTERFACE_H_

typedef enum
{
	DISPLAY_24,
	DISPLAY_12
}HRTC_Display_t;

typedef enum
{
	AM,
	PM,
	NO_AM_PM       /*if DISPLAY_24 method is chosen*/
}HRTC_MidDay_t;

typedef enum
{
	SUNDAY=1,
	MONDAY,
	TUESDAY,
	WEDENSDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
}HRTC_DOW_t;

typedef struct
{
	u8 Seconds;
	u8 Minuites;
	u8 Hours;
	u8 Date;
	u8 Month;
	u8 Year;
	HRTC_Display_t Display_Method;    /*12 Hour  or  24Hour*/
	HRTC_DOW_t Day_of_Week;
	HRTC_MidDay_t MidDay;   /*AM  or  PM*/
}HRTC_Config_t;

STD_error_t HRTC_stderrSetTime(HRTC_Config_t *ARG_pconTimeVal);

STD_error_t HRTC_stderrReadTime(HRTC_Config_t *ARG_pconTimeVal);


#endif
