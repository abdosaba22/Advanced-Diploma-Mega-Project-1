/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	APP	                            */
/* Version      : 	1.0                             */
/* Date         : 	December 10, 2023	            */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */

#ifndef _APP_H_
#define _APP_H_

//#include "LSTD_types.h"
#include "HRTC_Interface.h"
typedef enum
{
	NO_OPTION = '0',
	READ_TIME_OPTION  ,
	SET_TIME_OPTION ,
	SET_ALARM_OPTION ,
	EXIT_OPTION ,
	WRONG_OPTION,
}STD_Option_t;

typedef struct
{
	u8 Alarm_Number;
	u8 Alarm_Name[5];
	HRTC_Config_t Alarm_Time;
}APP_Alarm_t;


/******** Function prototypes ******/
STD_error_t 	APP_stderrClockPins_init	(void);
STD_error_t 	APP_stderrPeripheral_init	(void);
STD_error_t 	APP_stderrReadIDPassword	(void);
STD_error_t 	APP_stderrCheckIDPassword	(void);
STD_Option_t 	APP_stdopDisplayOptions		(void);
STD_error_t 	APP_stderrReadTimeOption	(void);
STD_error_t 	APP_stderrSetTimeOption		(void);
STD_error_t 	APP_stderrSetAlarmOption	(void);
void 			APP_voidCheckAlarm			(void);
u8 				APP_u8ConvertToNum			(char* ARG_pchVar);
u8				APP_u8ReadStart				(void);

#endif
