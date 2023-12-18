/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 GPIO								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 15, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */

#ifndef _MGPIO_INTERFACE_H_
#define _MGPIO_INTERFACE_H_

/**** used to indicate port ****/
typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	// PORTE,
	// PORTF,
	// PORTG,
	// PORTH
}MGPIO_PORT_t;

/****** PIN options (enum) ******/
typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,	
}MGPIO_PINNUM_t;

/***** Pin mode options *****/
typedef enum
{
	INPUT=0,
	OUTPUT,
	ALTERNATE_FUNCTION,
	ANALOG
}MGPIO_MODE_t;

/**** Pin speed options ***/
typedef enum
{
	LOW=0,
	MEDIUM,
	FAST,
	HIGH /* in this case may Overshot happen */
}MGPIO_OPSPEED_t;

/**** O/P Pin type also in AF may used ***/
typedef enum
{
	PUSH_PULL=0,
	OPEN_DRAIN
}MGPIO_OPTYPE_t;

/**** PIN pull optins  ****/
typedef enum 
{
	NOPULL=0,
	PULLUP,
	PULLDOWN
}MGPIO_PULLUD_t;

typedef enum
{
	PIN_LOW=0,
	PIN_HIGH
}MGPIO_PINVAL_t;

/**** Alternate func options to choose the correct AFx go to DataSheet ****/
typedef enum
{
	AF0=0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}MGPIO_ALTFUNC_t;

typedef struct
{
	MGPIO_PORT_t 		Port;
	MGPIO_PINNUM_t 		Pin;
	MGPIO_MODE_t 		Mode; 
	MGPIO_OPSPEED_t 	Speed; 		//in case OP
	MGPIO_OPTYPE_t 		OutputType;	//in case OP
	MGPIO_PULLUD_t	 	PullType;
	MGPIO_ALTFUNC_t 	AltFunc;
	
	/* may add Lock value to lock configuration of pin */
	
}MGPIO_CONFIG_t;


STD_error_t MGPIO_stderrPinConfig		(const MGPIO_CONFIG_t * ARG_configPinConfig);

STD_error_t MGPIO_stderrSetPinValue		(MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum, MGPIO_PINVAL_t ARG_PinVal);

STD_error_t MGPIO_stderrTogglePinValue	(MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum);

STD_error_t MGPIO_stderrReadPinValue	(u8* ARG_pu8PinVal, MGPIO_PORT_t ARG_portPort, MGPIO_PINNUM_t ARG_numPinNum);


#endif
