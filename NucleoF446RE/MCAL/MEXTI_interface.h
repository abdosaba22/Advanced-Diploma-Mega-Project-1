/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 EXT Interrupt						*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 19, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

#ifndef _MEXTI_INTERFACE_H_
#define _MEXTI_INTERFACE_H_

typedef enum
{
	MEXTI_LIN0,
	MEXTI_LIN1,
	MEXTI_LIN2,
	MEXTI_LIN3,
	MEXTI_LIN4,
	MEXTI_LIN5,
	MEXTI_LIN6,
	MEXTI_LIN7,
	MEXTI_LIN8,
	MEXTI_LIN9,
	MEXTI_LIN10,
	MEXTI_LIN11,
	MEXTI_LIN12,
	MEXTI_LIN13,
	MEXTI_LIN14,
	MEXTI_LIN15,
	MEXTI_LIN16,
	MEXTI_LIN17,
	MEXTI_LIN18,
	MEXTI_LIN19,
	MEXTI_LIN20,
	MEXTI_LIN21,
	MEXTI_LIN22
}MEXTI_NUM_t;

typedef enum
{
	MEXTI_RAISING_TRIGGER,
	MEXTI_FALLING_TRIGGER,
	MEXTI_RIS_FALL_TRIGGER
}MEXTI_TRIGGER_t;

typedef enum
{
	MEXTI_DISABLE,
	MEXTI_ENABLE
}MEXTI_MODE_t;


typedef struct
{
	MEXTI_NUM_t 		Exti_Num;
	MEXTI_TRIGGER_t 	Trigger;
	MEXTI_MODE_t 		Mode;
	void(*CallBackFunc)(void); //ptr to func
}MEXTI_PinConfig_t;


STD_error_t MEXTI_stderrConfig 				(const MEXTI_PinConfig_t* ARG_pconfigPinConfig);
STD_error_t MEXTI_stderrSetTrigger			(u8  ARG_u8MEXTILineNum ,u8 ARG_u8TriggerMode );
STD_error_t MEXTI_stderrClearPendingFlag	(u8  ARG_u8MEXTILineNum);
STD_error_t MEXTI_stderrGetPendingFlag		(u8* ARG_PenValue, u8 ARG_u8MEXTILineNum);
STD_error_t MEXTI_stderrIntEnable			(u8  ARG_u8MEXTILineNum);
STD_error_t MEXTI_stderrIntDisable			(u8  ARG_u8MEXTILineNum);
STD_error_t MEXTI_stderrSWTrigger			(u8  ARG_u8MEXTILineNum);
STD_error_t MSYSCFG_stderrSelEXTI_Line		(u8 ARG_u8MEXTILineNum, u8 ARG_u8Port);

#endif
