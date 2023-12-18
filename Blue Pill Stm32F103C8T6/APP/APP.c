#include "LBIT_math.h"
#include "LSTD_types.h"
#include "ERRORTYPE.h"
#include "BITMATH.h"

#include "MGPIO_Interface.h"
#include "MRCC_Interface.h"
#include "MEXTI_Interface.h"
#include "MNVIC_Interface.h"
#include "MSPI_interface.h"
#include "MSYSTICK_Interface.h"

#include "HLCD_interface.h"
#include "HLED_Interface.h"

#include "APP.h"

char G_pcharSPIReceivedData[10]={0};
char L_pcharSPISendData[10]={0};

volatile char G_charFlagAlarm = 0 ;
volatile char G_charFlagSPI = 0 ;


STD_error_t 	APP_stderrClockPins_init	(void)
{
	STD_error_t L_stderrState = E_OK;

	RCC_APB2EnableClk(IOPA);
	RCC_APB2EnableClk(IOPB);
	RCC_APB2EnableClk(AFIO);
	RCC_APB2EnableClk(SPI1);

	GPIO_u8PinInit(PORTB, PIN4, GPO_PUSH_PULL_02_MHZ); // Buzzer

	GPIO_u8setpinValue(PORTB, PIN4, PIN_HIGH);

	/* Led init */
	HLED_Init(&LEDRed);

	/* Exti signal */
	L_stderrState = GPIO_u8PinInit(PORTA, PIN0, I_FLOATING);



	L_stderrState = GPIO_u8PinInit(PORTA, PIN5, I_PULL_UP); // SCK
	L_stderrState = GPIO_u8PinInit(PORTA, PIN7, I_FLOATING); // MOSI
	L_stderrState = GPIO_u8PinInit(PORTA, PIN4, I_FLOATING); // NSS
	L_stderrState = GPIO_u8PinInit(PORTA, PIN6, AFO_PUSH_PULL_10_MHZ); // MISO

	HLCD_voidInit();

	return L_stderrState;
}

STD_error_t 	APP_stderrPeripheral_init	(void)
{

	STD_error_t L_stderrState = E_OK;

	/* configure SPI struct  Slave */
	MSPI_Config_t L_SPI1Config =
	{
			.SPI_Num = MSPI_NUM1,
			.Mode = MSPI_SLAVE ,
			.ClockPolPha = MSPI_POLPHA_NONINVERTING_LEADING,
			.DataSize = MSPI_DFF_1BYTE,
			.NSS_mode = MSPI_NSS_HW_MANAGE,
			.Prescaler = MSPI_PERIPH_CLK_BY128 ,
			.DataOrder = MSPI_MSB_FIRST,
			.CommunicationMode = MSPI_COMMUNI_MODE_FULL_DUPLEX,
			//			.SSOE_Type = MSPI_SSOUT_EN,
			.InterruptEnable={
					.ERR  = MSPI_INT_DISABLED,
					.RXNE = MSPI_INT_ENABLED,
					.TXE  = MSPI_INT_DISABLED,
			},
			.Status = MSPI_ENABLE
	};

	L_stderrState = MSPI_stderrInit(&L_SPI1Config);
	L_stderrState = NVIC_u8EnableINT(SPI1_IRQ);
	L_stderrState = SPI_stderrTransceiveBuffer_IT(MSPI_NUM1, G_pcharSPIReceivedData, L_pcharSPISendData, 10, APP_voidReceivedBuffer);


	EXTI_voidSetCallBackFn(EXTI0_LINE, &APP_voidFireAlarm);
	//	GPIO_u8MappAFIToEXTI(EXTI0_LINE, PORTA);
	//		NVIC_u8SetIRQPriority(EXTI0_IRQ,IRQ_Priority5);
	//		NVIC_u8EnableINT(EXTI0_IRQ);
	//	NVIC_u8SetPendingFlag(EXTI0_IRQ);


	NVIC_u8EnableINT(EXTI0_IRQ);
	EXTI_u8ConfigLine(EXTI0_LINE, RISING_EDGE_TRIGGERING);
	EXTI_u8IntEnable(EXTI0_LINE);

	return L_stderrState;
}

STD_error_t 	APP_stderrDisplayAlarm		(void)
{
	STD_error_t L_stderrState = E_OK;

	G_pcharSPIReceivedData[4] = '\0';

	HLCD_voidClear();
	HLCD_voidSetCur(1, 0);
	HLCD_voidSendString("NAME ");
	HLCD_voidSendString(G_pcharSPIReceivedData);
	HLCD_voidSendString(", NUM");
	HLCD_voidSendChar(G_pcharSPIReceivedData[9]+'0');

	HLCD_voidSetCur(0, 1);

	HLCD_voidSendNum(G_pcharSPIReceivedData[6]); // H
	HLCD_voidSendChar(':');
	HLCD_voidSendNum(G_pcharSPIReceivedData[5]); // M

	switch (G_pcharSPIReceivedData[7])
	{
	case 0: HLCD_voidSendString(" AM");break;
	case 1: HLCD_voidSendString(" PM");break;
	case 2: HLCD_voidSendString(" NM");break;
	}

	HLCD_voidSendString(" Alarm");

	for(u8 L_u8I;L_u8I< 10; L_u8I++)
	{
		HLED_TurnOn(&LEDRed);
		L_stderrState = GPIO_u8setpinValue(PORTB, PIN4, PIN_HIGH);
		STK_voidDelayms(2000); // 2s
		HLCD_voidClear();
		HLED_TurnOff(&LEDRed);
		L_stderrState = GPIO_u8setpinValue(PORTB, PIN4, PIN_LOW);
		STK_voidDelayms(1000); // 1s


		HLCD_voidSetCur(1, 0);
		HLCD_voidSendString("NAME ");
		HLCD_voidSendString(G_pcharSPIReceivedData);
		HLCD_voidSendString(", NUM");
		HLCD_voidSendChar(G_pcharSPIReceivedData[9]+'0');

		HLCD_voidSetCur(0, 1);

		HLCD_voidSendNum(G_pcharSPIReceivedData[6]); // H
		HLCD_voidSendChar(':');
		HLCD_voidSendNum(G_pcharSPIReceivedData[5]); // M

		switch (G_pcharSPIReceivedData[7])
		{
		case 0: HLCD_voidSendString(" AM");break;
		case 1: HLCD_voidSendString(" PM");break;
		case 2: HLCD_voidSendString(" NM");break;
		}

		HLCD_voidSendString(" Alarm");
		//		HLCD_voidClear();

	}

	HLCD_voidClear();
	G_charFlagSPI = 0;

	return L_stderrState;
}

STD_error_t 	APP_stderrDisplayTime		(void)
{
	STD_error_t L_stderrState = E_OK;

	HLCD_voidClear();

	HLCD_voidSetCur(0, 0);
	HLCD_voidSendNum(G_pcharSPIReceivedData[2]); // H
	HLCD_voidSendChar(':');
	HLCD_voidSendNum(G_pcharSPIReceivedData[1]); // M
	HLCD_voidSendChar(':');
	HLCD_voidSendNum(G_pcharSPIReceivedData[0]); // S

	switch (G_pcharSPIReceivedData[8])
	{
	case 0: HLCD_voidSendString(" AM");break;
	case 1: HLCD_voidSendString(" PM");break;
	case 2: HLCD_voidSendString(" NM");break;
	}

	HLCD_voidSetCur(1, 0);

	HLCD_voidSendNum(G_pcharSPIReceivedData[4]); // D
	HLCD_voidSendChar('/');
	HLCD_voidSendNum(G_pcharSPIReceivedData[5]); // M
	HLCD_voidSendChar('/');
	HLCD_voidSendNum(G_pcharSPIReceivedData[6]); // Y

	switch (G_pcharSPIReceivedData[3])
	{
	case 1: HLCD_voidSendString(" SUN");	break;
	case 2: HLCD_voidSendString(" MON");break;
	case 3: HLCD_voidSendString(" TUE");break;
	case 4: HLCD_voidSendString(" WED");break;
	case 5: HLCD_voidSendString(" THU");break;
	case 6: HLCD_voidSendString(" FRI");break;
	case 7: HLCD_voidSendString(" SAT");break;
	}

	//	HLCD_voidClear();
	G_charFlagSPI = 0;

	///	STK_voidDelayms(10000); // 1s

	for(u8 L_u8I=0; (L_u8I < 10) && (G_charFlagSPI == 0) ; L_u8I++)
	{
		STK_voidDelayms(1000); // 1s
		G_pcharSPIReceivedData[0] ++ ;

		if(G_pcharSPIReceivedData[0] == 60){
			G_pcharSPIReceivedData[0] = 0;
			G_pcharSPIReceivedData[1]++;
			HLCD_voidSetCur(0, 3);
			HLCD_voidSendNum(G_pcharSPIReceivedData[1]); // M
			HLCD_voidSetCur(0, 5);
			HLCD_voidSendString(":00");
		}
		else{
			HLCD_voidSetCur(0, 6);
			HLCD_voidSendNum(G_pcharSPIReceivedData[0]);
		}
	}

	HLCD_voidClear();

	return L_stderrState;

}


void 			APP_voidFireAlarm			(void)/* Exti */
{
	G_charFlagAlarm = 1;

}
void			APP_voidReceivedBuffer		(void)/* SPI*/
{
	if(1 == G_charFlagAlarm)
	{
		G_charFlagAlarm = 0;
		GPIO_u8setpinValue(PORTB, PIN4, PIN_HIGH);
		HLED_TurnOn(&LEDRed);
		/* Display Alarm info */
		G_charFlagSPI = 2 ; //

	}
	else
	{
		/* Display Time info */
		G_charFlagSPI = 1 ;
	}
}
