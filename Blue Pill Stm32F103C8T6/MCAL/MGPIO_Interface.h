/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 GPIO									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 10, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <stdint.h>

typedef enum
{
	PORTA=0,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTF,
	PORTG
}Port_t;

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
}PinNum_t;



typedef enum
{	
    I_ANALOG = 0b0000, 				  	/* 0  --         */
	GPO_PUSH_PULL_10_MHZ ,      		/* 1  -- 0b00001 */
    GPO_PUSH_PULL_02_MHZ ,			    /* 2  -- 0b00010 */
    GPO_PUSH_PULL_50_MHZ ,			    /* 3  -- 0b00011 */
    I_FLOATING , 					  	/* 4  -- 0b00100 */
    GPO_OPEN_DRIAN_10_MHZ , 		    /* 5  -- 0b00101 */
    GPO_OPEN_DRIAN_02_MHZ , 		    /* 6  -- 0b00110 */
    GPO_OPEN_DRIAN_50_MHZ , 		    /* 7  -- 0b00111 */
    AFO_PUSH_PULL_10_MHZ ,    			/* 9  -- 0b01001 */
    AFO_PUSH_PULL_02_MHZ ,    			/* 10 -- 0b01010 */
    AFO_PUSH_PULL_50_MHZ ,    			/* 11 -- 0b01011 */
    AFO_OPEN_DRIAN_10_MHZ=0b01101, 	   	/* 13 -- 0b01101 */
    AFO_OPEN_DRIAN_02_MHZ , 			/* 14 -- 0b01110 */
    AFO_OPEN_DRIAN_50_MHZ , 			/* 15 -- 0b01111 */
    I_PULL_DOWN , 					  	/* 16 -- 0b10000 */
    I_PULL_UP 						  	/* 17 -- 0b10001 */
} PinMode_t;

/*
typedef enum{
	IP_MODE=0,
	OP_10_MHZ,    // 1
	OP_02_MHZ,    // 2
	OP_50_MHZ     // 3
}PinMode_t;

typedef enum{
	I_ANALOG   =0b00,
	I_FLOATING ,  //1
	I_PULL_DOWN =0b100, //4
	I_PULL_UP  , //5		
}PinInCNF_t;

typedef enum{
	GPO_PUSH_PULL   =0b00,
	GPO_OPEN_DRIAN  ,
	AFO_PUSH_PULL   ,
	AFO_OPEN_DRIAN  	
}PinOpCNF_t;
*/

typedef enum{
	PIN_LOW=0,
	PIN_HIGH
}PinVal_t;

/*
typedef struct{
	Port_t Port;
	PinNUM_t_t Pin;
	PinMode_t Mode;
	//AltFunc_t AltFunc;	there is reg to set AlFun for the peripheral 
}PinConfig_t; 
*/

uint8_t GPIO_u8PinInit(Port_t Port, PinNum_t Pin, PinMode_t Mode);

uint8_t GPIO_u8setpinValue(Port_t Port, PinNum_t Pin, PinVal_t PinVal);

uint8_t GPIO_u8TogglepinValue(Port_t Port, PinNum_t Pin);

uint8_t GPIO_u8ReadpinValue(Port_t Port, PinNum_t Pin, PinVal_t* PinVal);


#endif
