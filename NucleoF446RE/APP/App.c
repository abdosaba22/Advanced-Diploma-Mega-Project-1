/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	APP	                            */
/* Version      : 	1.0                             */
/* Date         : 	December 10, 2023	            */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */

#include <stdint.h>

#include "LBIT_math.h"
#include "LSTD_types.h"
#include "MEXTI_interface.h"
#include "MGPIO_interface.h"
#include "MNVIC_interface.h"
#include "MI2C_Interface.h"
#include "MRCC_interface.h"
#include "MSYSTICK_interface.h"
#include "MSPI_interface.h"
#include "UART_Interface.h"

#include "HRTC_Interface.h"
#include "HBUTTON_Interface.h"
#include "App.h"
/**
 * 7- create function to read time to be set to RTC
 * 8- create function to transmit time to Blue Pill
 * 9- create function to set Alarm (Number , Name )
 * 10 create function to check is Alarm == Time current
 * 11
 *
 * **/

char G_ID[5] = {0};
char G_Password[5] ={0};
HRTC_Config_t G_conRTC = {0};
APP_Alarm_t G_conRTCAlarm[5]={{0}};

STD_error_t APP_stderrClockPins_init(void)
{
	STD_error_t L_stderrState = E_OK;

	/* Init RCC HSE 8 MHZ */
	MRCC_voidInit();

	L_stderrState = MRCC_stderrEnablePeripheralClock(APB2_SPI1_EN);

	L_stderrState = MRCC_stderrEnablePeripheralClock(AHB1_GPIOA_EN);
	L_stderrState = MRCC_stderrEnablePeripheralClock(AHB1_GPIOB_EN);
	L_stderrState = MRCC_stderrEnablePeripheralClock(AHB1_GPIOC_EN);
	L_stderrState = MRCC_stderrEnablePeripheralClock(APB2_SYSCFG_EN);
	L_stderrState = MRCC_stderrEnablePeripheralClock(APB1_USART2_EN);


//    MRCC_stderrEnablePeripheralClock(APB1_I2C1_EN);

	/* configure PinA1 as: Output Pushpull, PULLDOWN Lowspeed */
	MGPIO_CONFIG_t FireEXTI_Pin={
			.Port=PORTA,
			.Pin=PIN1,
			.Mode=OUTPUT,
			.Speed=LOW,
			.OutputType=PUSH_PULL,
			.PullType=PULLDOWN
	};
	L_stderrState = MGPIO_stderrPinConfig(&FireEXTI_Pin);

	/* configure USART pins */
	MGPIO_CONFIG_t USART2_RxPin ={
			.Port = PORTA,
			.Pin = PIN3,
			.Mode = ALTERNATE_FUNCTION,
			.AltFunc = AF7,
			.PullType = NOPULL
	};

	MGPIO_CONFIG_t USART2_TxPin ={
			.Port = PORTA,
			.Pin = PIN2,
			.Mode = ALTERNATE_FUNCTION,
			.AltFunc = AF7,
			.PullType = NOPULL
	};

	L_stderrState = MGPIO_stderrPinConfig(&USART2_RxPin);
	L_stderrState = MGPIO_stderrPinConfig(&USART2_TxPin);


	/* GPIO for I2C */
	MGPIO_CONFIG_t I2C_SDAPin ={
			.Port = PORTB,
			.Pin = PIN9,
			.Mode = ALTERNATE_FUNCTION,
			.AltFunc = AF4,
			.OutputType = OPEN_DRAIN,
			.PullType = PULLUP,
			.Speed = LOW,
	};
	MGPIO_CONFIG_t I2C_SCLPin ={
			.Port = PORTB,
			.Pin = PIN8,
			.Mode = ALTERNATE_FUNCTION,
			.AltFunc = AF4,
			.OutputType = OPEN_DRAIN,
			.PullType = PULLUP,
			.Speed = LOW,
	};
	/** Configure I2C pins **/
	L_stderrState = MGPIO_stderrPinConfig(&I2C_SCLPin);
	L_stderrState = MGPIO_stderrPinConfig(&I2C_SDAPin);

	/* Config pins of SPI */
		MGPIO_CONFIG_t L_SPIMOSI={
				.Port=PORTA,
				.Pin=PIN7,
				.Mode=ALTERNATE_FUNCTION,
				.Speed=LOW,
				.AltFunc=AF5,
				.OutputType=PUSH_PULL,
		};
		MGPIO_CONFIG_t L_SPIMISO={
				.Port=PORTA,
				.Pin=PIN6,
				.Mode=ALTERNATE_FUNCTION,
				.Speed=LOW,
	//			.PullType = NOPULL,
				.AltFunc=AF5,
				.OutputType=PUSH_PULL,
		};
		MGPIO_CONFIG_t L_SPISCK={
				.Port=PORTA,
				.Pin=PIN5,
				.Mode=ALTERNATE_FUNCTION,
				.Speed=LOW,
				.AltFunc=AF5,
				.OutputType=PUSH_PULL,
				.PullType=NOPULL,
		};
		MGPIO_CONFIG_t L_NSS_Select={
				.Port=PORTA,
				.Pin=PIN0,
				.Mode=OUTPUT,
				.Speed=LOW,
				.OutputType=PUSH_PULL,
		};



//		MSTK_stderrInit(MSTK_CLOCKSRC_AHB_8);
		/* SPI Pin init */
		MGPIO_stderrPinConfig(&L_NSS_Select);
		MGPIO_stderrPinConfig(&L_SPIMISO);
		MGPIO_stderrPinConfig(&L_SPIMOSI);
		MGPIO_stderrPinConfig(&L_SPISCK);

		MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH); // NSS



//	/* Config pins of SPI */
//	MGPIO_CONFIG_t L_SPIMOSI={
//			.Port=PORTA,
//			.Pin=PIN7,
//			.Mode=ALTERNATE_FUNCTION,
//			.Speed=LOW,
//			.AltFunc=AF5,
//			.OutputType=PUSH_PULL,
//	};
//	MGPIO_CONFIG_t L_SPIMISO={
//			.Port=PORTA,
//			.Pin=PIN6,
//			.Mode=ALTERNATE_FUNCTION,
//			.Speed=LOW,
//			//			.PullType = NOPULL,
//			.AltFunc=AF5,
//			.OutputType=PUSH_PULL,
//	};
//	MGPIO_CONFIG_t L_SPISCK={
//			.Port=PORTA,
//			.Pin=PIN5,
//			.Mode=ALTERNATE_FUNCTION,
//			.Speed=LOW,
//			.AltFunc=AF5,
//			.OutputType=PUSH_PULL,
//			.PullType=NOPULL,
//	};
//	MGPIO_CONFIG_t L_NSS_Select={
//			.Port=PORTA,
//			.Pin=PIN0,
//			.Mode=OUTPUT,
//			.Speed=LOW,
//			.OutputType=PUSH_PULL,
//			.PullType = PULLUP,
//	};
//	/* SPI Pin init */
//	L_stderrState = MGPIO_stderrPinConfig(&L_NSS_Select);
//	L_stderrState = MGPIO_stderrPinConfig(&L_SPIMISO);
//	L_stderrState = MGPIO_stderrPinConfig(&L_SPIMOSI);
//	L_stderrState = MGPIO_stderrPinConfig(&L_SPISCK);
//	L_stderrState = MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH); // NSS

	HButton_voidInit(PORTC,PIN13,PULLUP);

	return L_stderrState;
}

STD_error_t APP_stderrPeripheral_init(void)
{
	STD_error_t L_stderrState = E_OK ;

	/* Systick init*/
	L_stderrState = MSTK_stderrInit(MSTK_CLOCKSRC_AHB_8);

	/* initialize USART peripheral */
	MUSART_Config_t USART2_Recive ={
			.USART_Num = MUSART_2,
			.USART_Baud = MUSART_BAUD_115200,
			.USART_HWFlowControl = MUSART_HW_FLOW_CTRL_NONE,
			.USART_Mode = MUSART_MODE_TXRX,
			.USART_NoOfStopBits = MUSART_STOPBITS_1,
			.USART_Oversampling = MUSART_OVERSAMPLING_16,
			.USART_SynchMode = ASYNCH,
			.USART_ParityControl = MUSART_PARITY_DISABLE,
			.USART_WordLength = MUSART_WORD_WIDTH_8BITS,
			.USART_InterruptEnable={0,0,0,0,0,0}
	};

	L_stderrState = MUSART_stderrInit( &USART2_Recive);
	//	MSTK_voidBusyDelay(1000); // 1ms
	/* I2C */
	L_stderrState = MRCC_stderrEnablePeripheralClock(APB1_I2C1_EN);
	MI2C_voidMasterInit(MI2C1, 10, SM_MOOD);

	/* configure SPI struct  Master */
	MSPI_Config_t L_SPI1Config =
	{
			.SPI_Num = MSPI_NUM1,
			.Mode = MSPI_MASTER,
			.ClockPolPha = MSPI_POLPHA_NONINVERTING_LEADING,
			.DataSize = MSPI_DFF_1BYTE,
			.NSS_mode = MSPI_NSS_SW_MANAGE, /* SW so need to write */
			.Prescaler = MSPI_PERIPH_CLK_BY128 ,
			.DataOrder = MSPI_MSB_FIRST,
			.CommunicationMode = MSPI_COMMUNI_MODE_FULL_DUPLEX,
			//			.SSOE_Type = MSPI_SSOUT_EN,
			.InterruptEnable={
					.ERR  = MSPI_INT_DISABLED,
					.RXNE = MSPI_INT_DISABLED,
					.TXE  = MSPI_INT_DISABLED,
			},
			.Status = MSPI_DISABLE
	};


	MSPI_stderrInit(&L_SPI1Config);
	MSPI_stderrEnable(MSPI_NUM1);

	/* 1000000 == 1s  in periodic we reduce it by 1 */
	MSTK_stderrStart_IT(999999, 1,&APP_voidCheckAlarm);

	return L_stderrState;
}

STD_error_t APP_stderrReadIDPassword(void)
{
	STD_error_t L_stderrState = E_OK;
	STD_error_t L_stderrCheck ;
	u8 L_u8NumberofTries = 0 ;

	do
	{
		L_stderrState =	MUSART_stderrSendString(MUSART_2,"Please, Enter Your ID .. \r\n");
		L_stderrState = MUSART_stderrReceiveStringUntil(MUSART_2,G_ID,'*');
		L_stderrState =	MUSART_stderrSendString(MUSART_2,"Then, Enter Your Password .. \r\n");
		L_stderrState = MUSART_stderrReceiveStringUntil(MUSART_2,G_Password,'*');

		L_stderrCheck = APP_stderrCheckIDPassword();
		if(L_stderrCheck == E_OK)
		{
			L_stderrState = E_OK;
			break ;
		}
		else
		{
			L_stderrState =	MUSART_stderrSendString(MUSART_2,"Wrong, Try again .. \r\n");
//			MSTK_voidBusyDelay(1000000); /* 1s */
			L_u8NumberofTries ++;
		}
	}while(L_u8NumberofTries < 4);

	if(L_u8NumberofTries == 4 )
	{
		/* Wrong finish your */
		L_stderrState = E_NOK;
		MUSART_stderrSendString(MUSART_2,"You have finished your Number of tries .. \r\n");
	}
	else
	{
		MUSART_stderrSendString(MUSART_2,"Correct .. \r\n");
	}
	return L_stderrState;
}

STD_error_t APP_stderrCheckIDPassword(void)
{
	STD_error_t L_stderrState = E_OK;
	u8 L_u8Iterator;
	for(L_u8Iterator=0;L_u8Iterator<4;L_u8Iterator++)
	{
		/* check ID & Password */
		if(G_ID[L_u8Iterator] != G_Password[ 3-L_u8Iterator ] )
		{
			L_stderrState = E_NOK;
			break;
		}
		else
		{
			/* Do nothing */
		}
	}
	return L_stderrState;
}

STD_Option_t APP_stdopDisplayOptions(void)
{
	STD_Option_t L_stdopVar= NO_OPTION;

	MUSART_stderrSendString(MUSART_2,"You have 4 options .. \r\n\n");
	MUSART_stderrSendString(MUSART_2,"1- Read Time & Date ..\r\n");
	MUSART_stderrSendString(MUSART_2,"2- Set Time & Date ..\r\n");
	MUSART_stderrSendString(MUSART_2,"3- Set Alarm ..\r\n");
	MUSART_stderrSendString(MUSART_2,"4- Exit ..\r\n");
	MUSART_stderrSendString(MUSART_2,"Your option is:");
	L_stdopVar = MUSART_charReceiveCharBlocking(MUSART_2);

	/* Check range of option entered ? */
	if(L_stdopVar > EXIT_OPTION && L_stdopVar < READ_TIME_OPTION)
	{
		/* Wrong option */
		L_stdopVar = WRONG_OPTION;
		MUSART_stderrSendString(MUSART_2,"\nWrong option, Try again .. \r\n\n");
	}
	else
	{
		MUSART_stderrSendString(MUSART_2,"\nOK.. \r\n\n");
	}

	return L_stdopVar;

}

STD_error_t APP_stderrReadTimeOption(void)
{
	STD_error_t L_stderrState = E_OK;
	u8 L_u8Timearr[10]={0};
	u8 L_u8Temparr[10]={0};
	/* stop STK */
	MSTK_voidStop();

	/*read from RTC */
	HRTC_stderrReadTime(&G_conRTC);

	L_u8Timearr[0] = G_conRTC.Seconds;
	L_u8Timearr[1] = G_conRTC.Minuites;
	L_u8Timearr[2] = G_conRTC.Hours;
	L_u8Timearr[3] = G_conRTC.Day_of_Week;
	L_u8Timearr[4] = G_conRTC.Date;
	L_u8Timearr[5] = G_conRTC.Month;
	L_u8Timearr[6] = G_conRTC.Year;
	L_u8Timearr[7] = G_conRTC.Display_Method;
	L_u8Timearr[8] = G_conRTC.MidDay;
	L_u8Timearr[9] = READ_TIME_OPTION;

	/* 1st need to check SPI NUM */
	u16 L_u16Counter = 0;
	for (L_u16Counter = 0; L_u16Counter < 10; L_u16Counter++)
	{
		MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_LOW);
		MSPI_stderrTransceiveData(MSPI_NUM1, &L_u8Temparr[L_u16Counter], L_u8Timearr[L_u16Counter]);
		MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH);
		MSTK_voidBusyDelay(120);
	}

	/*send via spi */
//	MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_LOW);
//	L_stderrState = MSPI_stderrTransceiveBuffer(MSPI_NUM1, L_u8Temparr, L_u8Timearr, 10);
//	MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH);
	/* done */
	L_stderrState = MUSART_stderrSendString(MUSART_2,"\nTime Displayed On LCD .. \r\n\n");


	/* 1000000 == 1s  in periodic we reduce it by 1 */
	MSTK_stderrStart_IT(999999, 1,&APP_voidCheckAlarm);


	return L_stderrState;
}

STD_error_t APP_stderrSetTimeOption(void)
{
	STD_error_t L_stderrState = E_OK;
	char L_u8Timearr[26]={0};
	/* stop STK */
	MSTK_voidStop();
	/*read from User 										for ex	12 00:00:00 AM* */
	L_stderrState = MUSART_stderrSendString(MUSART_2,"\nEnter Time in Format->\r\nDisplay_method H:M:S AM,PM or No .. \r\n");
	L_stderrState = MUSART_stderrReceiveStringUntil(MUSART_2,L_u8Timearr,'*');
	/*												sun = 1 to 7	00/00/00*				 */
	L_stderrState = MUSART_stderrSendString(MUSART_2,"\nThen Enter Date in format->\r\nDay Date/Month/Year .. \r\n");
	L_stderrState = MUSART_stderrReceiveStringUntil(MUSART_2,&L_u8Timearr[15],'*');



	switch(APP_u8ConvertToNum(&L_u8Timearr[0]))
	{
	case 12: G_conRTC.Display_Method	 =	DISPLAY_12; break;
	case 24: G_conRTC.Display_Method	 =	DISPLAY_24; break;
	}
//	G_conRTC.Display_Method	 =	APP_u8ConvertToNum(&L_u8Timearr[0]);
	G_conRTC.Seconds =	APP_u8ConvertToNum(&L_u8Timearr[9]);
	G_conRTC.Minuites=	APP_u8ConvertToNum(&L_u8Timearr[6]);
	G_conRTC.Hours	 =	APP_u8ConvertToNum(&L_u8Timearr[3]);
	switch(L_u8Timearr[12])
	{
	case 'A':	G_conRTC.MidDay = AM;		break;
	case 'P':	G_conRTC.MidDay = PM; 		break;
	case 'N':	G_conRTC.MidDay = NO_AM_PM; break;
	default	:								break;
	}
	G_conRTC.Day_of_Week = L_u8Timearr[15] - '0' ;

	G_conRTC.Date	=	APP_u8ConvertToNum(&L_u8Timearr[17]);
	G_conRTC.Month	=	APP_u8ConvertToNum(&L_u8Timearr[20]);
	G_conRTC.Year	=	APP_u8ConvertToNum(&L_u8Timearr[23]);

	L_stderrState = HRTC_stderrSetTime(&G_conRTC);
	L_stderrState = MUSART_stderrSendString(MUSART_2,"\nTime Set .. \r\n");

	/* 1000000 == 1s  in periodic we reduce it by 1 */
	MSTK_stderrStart_IT(999999, 1,&APP_voidCheckAlarm);

	/* done */
	return L_stderrState;
}

STD_error_t APP_stderrSetAlarmOption(void)
{
	STD_error_t L_stderrState = E_OK;
	u8 L_u8Number=0;
	/* Get Number of Alarm from User */
	L_stderrState = MUSART_stderrSendString(MUSART_2,"\nAdd or edit Alarm..\nEnter Number of Alarm from 0 to 4 .. \r\n");
	L_u8Number = MUSART_charReceiveCharBlocking(MUSART_2) - '0';
	if(L_u8Number < 5  )
	{
		G_conRTCAlarm[L_u8Number].Alarm_Number = L_u8Number;
		L_stderrState = MUSART_stderrSendString(MUSART_2,"Enter Name for Alarm of 4 char .. \r\n");
		MUSART_stderrReceiveStringUntil(MUSART_2,G_conRTCAlarm[L_u8Number].Alarm_Name,'*');

		char L_u8Timearr[26]={0};
		/*read from User 										for ex	12 00:00 AM* */
		L_stderrState = MUSART_stderrSendString(MUSART_2,"\nEnter Time in Format->\r\nDisplay_method H:M AM,PM or No .. \r\n");
		L_stderrState = MUSART_stderrReceiveStringUntil(MUSART_2,L_u8Timearr,'*');
		/*												sun = 1 to 7*				 */
		L_stderrState = MUSART_stderrSendString(MUSART_2,"\nThen Enter Day from 1 To 7 : \r\n");
		G_conRTCAlarm[L_u8Number].Alarm_Time.Day_of_Week = MUSART_charReceiveCharBlocking(MUSART_2) - '0';

		G_conRTCAlarm[L_u8Number].Alarm_Time.Display_Method	=	APP_u8ConvertToNum(&L_u8Timearr[0]);
//		G_conRTCAlarm[L_u8Number].Alarm_Time.Seconds 		=	APP_u8ConvertToNum(&L_u8Timearr[9]);
		G_conRTCAlarm[L_u8Number].Alarm_Time.Minuites		=	APP_u8ConvertToNum(&L_u8Timearr[6]);
		G_conRTCAlarm[L_u8Number].Alarm_Time.Hours	 		=	APP_u8ConvertToNum(&L_u8Timearr[3]);

		switch(L_u8Timearr[9])
		{
		case 'A':	G_conRTCAlarm[L_u8Number].Alarm_Time.MidDay = AM;		break;
		case 'P':	G_conRTCAlarm[L_u8Number].Alarm_Time.MidDay = PM; 		break;
		case 'N':	G_conRTCAlarm[L_u8Number].Alarm_Time.MidDay = NO_AM_PM; break;
		default	:								break;
		}

	}
	else
	{
		/* Wrong number */
		L_stderrState = MUSART_stderrSendString(MUSART_2,"\nWrong Number .. \r\n");
		L_stderrState = E_NOK;
	}

	return L_stderrState;
}

void APP_voidCheckAlarm(void)
{

	HRTC_stderrReadTime(&G_conRTC);

	for(u8 L_u8i = 0;L_u8i<5;L_u8i++)
	{
		/* check Day */
		if(G_conRTCAlarm[L_u8i].Alarm_Time.Day_of_Week == G_conRTC.Day_of_Week)
		{
			/* check hour */
			if(G_conRTCAlarm[L_u8i].Alarm_Time.Hours == G_conRTC.Hours)
			{
				/* check AM or PM or NO */
				if(G_conRTCAlarm[L_u8i].Alarm_Time.MidDay == G_conRTC.MidDay)
				{
					if(G_conRTCAlarm[L_u8i].Alarm_Time.Minuites == G_conRTC.Minuites)
					{
						/* fire alarm send signal */
						MGPIO_stderrSetPinValue(PORTA, PIN1, PIN_HIGH);
						/* array to send elements over SPI */
						u8 L_u8Timearr[10]={0};

//						MSTK_voidBusyDelay(50); /* 50 us */
						L_u8Timearr[0] = G_conRTCAlarm[L_u8i].Alarm_Time.Minuites;
						L_u8Timearr[1] = G_conRTCAlarm[L_u8i].Alarm_Time.Hours;
						L_u8Timearr[2] = G_conRTCAlarm[L_u8i].Alarm_Time.MidDay;
						L_u8Timearr[3] = G_conRTCAlarm[L_u8i].Alarm_Time.Day_of_Week;
						L_u8Timearr[4] = G_conRTCAlarm[L_u8i].Alarm_Number;

						MGPIO_stderrSetPinValue(PORTA, PIN1, PIN_LOW);

						/* send info of alarm over SPI */
//						MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_LOW); // NSS

						u16 L_u16Counter = 0;
						for (L_u16Counter = 0; L_u16Counter < 5; L_u16Counter++)
						{
							MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_LOW);
							MSPI_stderrTransceiveData(MSPI_NUM1, &L_u8Timearr[5+L_u16Counter] , G_conRTCAlarm[L_u8i].Alarm_Name[L_u16Counter]);
							MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH);
							MSTK_voidBusyDelay(120);
						}
//						u16 L_u16Counter = 0;
						for (L_u16Counter = 0; L_u16Counter < 5; L_u16Counter++)
						{
							MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_LOW);
							MSPI_stderrTransceiveData(MSPI_NUM1, &L_u8Timearr[5+L_u16Counter] , L_u8Timearr[L_u16Counter]);
							MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH);
							MSTK_voidBusyDelay(120);
						}


//						MSPI_stderrTransceiveBuffer(MSPI_NUM1,&L_u8Timearr[5] , G_conRTCAlarm[L_u8i].Alarm_Name ,5);
//						MSPI_stderrTransceiveBuffer(MSPI_NUM1,&L_u8Timearr[5] , &L_u8Timearr[0] ,5);

//						MGPIO_stderrSetPinValue(PORTA, PIN0, PIN_HIGH); // NSS
					}
					else
					{
						/* do nothing */
						continue ;
					}
				}
				else
				{
					/* do nothing */
					continue ;
				}
			}
			else
			{
				/* do nothing */
				continue ;
			}
		}
		else
		{
			/* do nothing */
			continue ;
		}
	}

//	return L_stderrState;
}

u8 APP_u8ConvertToNum(char* ARG_pchVar)
{
	u8 L_u8ReturnNum = 0;

	L_u8ReturnNum = (ARG_pchVar[0]-'0') * 10;
	L_u8ReturnNum += (ARG_pchVar[1]-'0');

	return L_u8ReturnNum;
}

u8 APP_u8ReadStart(void)
{
	return HButton_u8Read(PORTC,PIN13);
}
