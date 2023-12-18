/* ************************************************ */
/* Author      : Abd-alrahman Amin                  */
/* SWC         : LCD                                */
/* Layer       : HAL                                */
/* Version     : 1.1                                */
/* Date        : August 7, 2023                     */
/* Last Edit   : August 8, 2023	                    */
/* ************************************************ */

/* Library Includes */
#include <stdint.h>
#include "BITMATH.h"
#include "ERRORTYPE.h"
#include "LBIT_math.h"
#include "LSTD_types.h"

#include <MGPIO_Interface.h>
#include <MSYSTICK_Interface.h>

#include "HLCD_config.h"
#include "HLCD_private.h"
#include "HLCD_interface.h"

/*****************************************************************************/
static HLCD_Config LCD_arr[6]= {
	{HLCD_DATA_PORT,HLCD_D4_PIN},{HLCD_DATA_PORT,HLCD_D5_PIN},{HLCD_DATA_PORT,HLCD_D6_PIN},{HLCD_DATA_PORT,HLCD_D7_PIN},{HLCD_CTRL_PORT,HLCD_RS_PIN},{HLCD_CTRL_PORT,HLCD_EN_PIN}
};


void HLCD_voidInit(void)
{
//	GPIO_PinConfig_t LCDPINS={
//			.Mode=OUTPUT,
//			.speed=LOW,
//			.OutputType=PUSH_PULL,
//			.PullType=NOPULL
//	};
//	// init direction pin
	for(uint8_t i=0; i< 6;i++)
	{
		GPIO_u8PinInit(LCD_arr[i].port,LCD_arr[i].pin,GPO_PUSH_PULL_02_MHZ);
//		LCDPINS.Port=LCD_arr[i].port;
//		LCDPINS.Pin =LCD_arr[i].pin;
//		GPIO_u8PinInit(&LCDPINS);
	}

	STK_voidDelayms(40) ;

	HLCD_voidSendCmd(HLCD_INIT);//send most first
	STK_voidDelayms(5);
	HLCD_voidSendCmd(HLCD_ENABLE_4BIT_MODE);//send most first
	STK_voidDelayus(100);
	HLCD_voidSendCmd(0x28);//send most first
	STK_voidDelayus(100);
	HLCD_voidSendCmd(0x0C);
	STK_voidDelayus(200);

	HLCD_voidSendCmd(0x06);
	HLCD_voidSendCmd(0x0F);
	HLCD_voidSendCmd(0x01);
	STK_voidDelayms(2);

}

void HLCD_voidSendCmd(uint8_t ARG_u8Cmd){
	
	HLCD_RS(PIN_LOW);
	HLCD_EN(PIN_LOW);
	
	/* 4 - bit mode */
	
	/* send 4-MS bits  */
	HLCD_D4( GET_BIT(ARG_u8Cmd,4)) ;  /*if bit is 0 or 1 increment it by 1 cause MDIO driver #MDIO_HIGH is 2 low is 1  */
	HLCD_D5( GET_BIT(ARG_u8Cmd,5)) ;	/* we can change the macro in MDIO_driver but we don't need to define macro with 0 */
	HLCD_D6( GET_BIT(ARG_u8Cmd,6)) ;
	HLCD_D7( GET_BIT(ARG_u8Cmd,7)) ;

	HLCD_EN(PIN_HIGH);
	STK_voidDelayus(10);
	HLCD_EN(PIN_LOW);
	STK_voidDelayus(100);

	/* send 4-LS bits  */
	HLCD_D4( GET_BIT(ARG_u8Cmd,0) );
	HLCD_D5( GET_BIT(ARG_u8Cmd,1) );
	HLCD_D6( GET_BIT(ARG_u8Cmd,2) );
	HLCD_D7( GET_BIT(ARG_u8Cmd,3) );

	HLCD_EN(PIN_HIGH);
	STK_voidDelayus(10);
	HLCD_EN(PIN_LOW);
	STK_voidDelayus(100);
}

void HLCD_voidSendChar(char ARG_charChar){
	HLCD_RS(PIN_HIGH);
	HLCD_EN(PIN_LOW);
	
	/* send 4-MS bits  */
	HLCD_D4( GET_BIT(ARG_charChar,4) );
	HLCD_D5( GET_BIT(ARG_charChar,5) );
	HLCD_D6( GET_BIT(ARG_charChar,6) );
	HLCD_D7( GET_BIT(ARG_charChar,7) );

	HLCD_EN(PIN_HIGH);
	STK_voidDelayus(10);
	HLCD_EN(PIN_LOW);
	STK_voidDelayus(100);

	/* send 4-LS bits  */
	HLCD_D4( GET_BIT(ARG_charChar,0) );
	HLCD_D5( GET_BIT(ARG_charChar,1) );
	HLCD_D6( GET_BIT(ARG_charChar,2) );
	HLCD_D7( GET_BIT(ARG_charChar,3) );

	HLCD_EN(PIN_HIGH);
	STK_voidDelayus(10);
	HLCD_EN(PIN_LOW);
	STK_voidDelayus(100);
}

void HLCD_voidSendNum(uint16_t ARG_u16Number){
	if (0 == ARG_u16Number ) 
	{
		HLCD_voidSendChar('0');
	}
	else{
		uint8_t L_u8arrNum[6]; 
		int8_t	L_s8Iterator=0;
		//save every digit of num in our array separately
		for(;ARG_u16Number!=0;L_s8Iterator++)
		{
			L_u8arrNum[L_s8Iterator]=(ARG_u16Number%10) +'0';
			ARG_u16Number/=10;
		}

		if(L_s8Iterator == 1) HLCD_voidSendChar('0');

		L_s8Iterator--;
		while(L_s8Iterator!=-1){
			HLCD_voidSendChar(L_u8arrNum[L_s8Iterator]);
			L_s8Iterator--;
		}	
	}
}

void HLCD_voidSendString(const char *ARG_charptrString){
	
	if(ARG_charptrString != NULL )
	{	
		uint8_t L_u8Iterator =0;
		do{
			HLCD_voidSendChar(ARG_charptrString[L_u8Iterator]);
			L_u8Iterator++;
		}while(ARG_charptrString[L_u8Iterator]!='\0');
		
		/* for(;ARG_charptrString[L_u8Iterator]!='\0';L_u8Iterator++){
			LCD_voidSendChar(ARG_charptrString[L_u8Iterator]);
		 }*/
	}
	else{
		/* return NULL_POINTER_ERROR */
	}
}

void HLCD_voidSetCur(uint8_t ARG_u8Row, uint8_t ARG_u8Col)
{
    uint8_t L_u8Temp=HLCD_START_LINE_1 | (ARG_u8Col ) | (ARG_u8Row<<6);

    HLCD_voidSendCmd(L_u8Temp);
    STK_voidDelayms(1);
}

void HLCD_voidClear(void)
{
	HLCD_voidSendCmd(HLCD_CLEAR_DISPLAY);
	STK_voidDelayms(1);
}
