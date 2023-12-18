/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* SWC          : 	USART 			                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	MCAL                            */
/* Version      : 	1.0                             */
/* Date         : 	September 10, 2023              */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */

#ifndef _MUSART_INTERFACE_H_
#define _MUSART_INTERFACE_H_

/* Possible options for USART_Mode */
typedef enum
{
								/*    TE RE */
	MUSART_MODE_ONLY_RX = 1, 	/* 0b 0  1  */
	MUSART_MODE_ONLY_TX ,		/* 0b 1  0  */
	MUSART_MODE_TXRX 			/* 0b 1  1  */
}MUSART_Mode_t;

/* Possible options for USART_Baud */
typedef enum{
	MUSART_BAUD_1200 = 1200,
	MUSART_BAUD_2400 = 2400,
	MUSART_BAUD_9600 = 9600,
	MUSART_BAUD_19200 = 19200,
	MUSART_BAUD_38400 = 38400,
	MUSART_BAUD_57600 = 57600,
	MUSART_BAUD_115200 = 115200,
	MUSART_BAUD_230400 = 230400,
	MUSART_BAUD_460800 = 460800,
	MUSART_BAUD_921600 = 921600,
	MUSART_BAUD_2M = 2000000,
	MUSART_BAUD_3M = 3000000
}MUSART_BaudeRate_t;

/* Possible options for USART_ParityControl */
typedef enum {
								/*   PCE  PS    */
	MUSART_PARITY_DISABLE=0, 	/* 0b 0   0		*/
	MUSART_PARITY_EN_EVEN=2,	/* 0b 1   0		*/
	MUSART_PARITY_EN_ODD  		/* 0b 1   1		*/
}MUSART_Parity_t;

/* Possible options for USART_WordLength */
typedef enum{
	MUSART_WORD_WIDTH_8BITS=0,
	MUSART_WORD_WIDTH_9BITS
}MUSART_WordWidth_t;

/* Possible options for USART_NoOfStopBits */
typedef enum{
	MUSART_STOPBITS_1=0,
	MUSART_STOPBITS_0_5,
	MUSART_STOPBITS_2,
	MUSART_STOPBITS_1_5
}MUSART_StopBits_t;


/* Possible options for USART_HWFlowControl */
typedef enum{
	/*                                	  CTSE RTSE */
	MUSART_HW_FLOW_CTRL_NONE = 0,	/* 0 0b 0   0  	*/
	MUSART_HW_FLOW_CTRL_RTS, 		/* 1 0b 0   1  	*/
	MUSART_HW_FLOW_CTRL_CTS, 		/* 2 0b 1   0  	*/
	MUSART_HW_FLOW_CTRL_CTS_RTS  	/* 3 0b 1   1  	*/
}MUSART_HWFlowControl_t;


 /* Possible options for SynchMode */
typedef enum{
	ASYNCH =0,
    SYNCH
}MUSART_SynchMode_t;

 /* Possible options for USARTNumber */
typedef enum{
	MUSART_1=0,
	MUSART_2,
	MUSART_3,
	MUSART_4,
	MUSART_5,
	MUSART_6
}MUSART_Number_t;

 /* Possible options for USARTOversampling */
typedef enum
{
 	MUSART_OVERSAMPLING_16,
 	MUSART_OVERSAMPLING_8
}MUSART_Oversampling_t;

/* Config interrupt   */
typedef struct
{
	/* 0 or 1 */
    u8 PEIE:1; 	/* parity error */
    u8 TXEIE:1;	/* Transmit data register empty */
    u8 TCIE:1;     /* Transmission complete */
    u8 RXNEIE:1;   /* Read data register not empty */
    u8 IDLEIE:1;   /* IDLE line detected */
    u8 CTSIE:1;    /* CTS  interrupt */

}MUART_IT_ENABLE_t;

 /*
 * Configuration structure for USARTx peripheral
 */
typedef struct {
	MUSART_Number_t	 		USART_Num;
	MUSART_Mode_t 			USART_Mode;
	MUSART_BaudeRate_t 		USART_Baud;
	MUSART_StopBits_t 		USART_NoOfStopBits;	// can be removed
	MUSART_WordWidth_t 		USART_WordLength;	// can be removed
	MUSART_Parity_t 		USART_ParityControl; // can be removed
	MUSART_HWFlowControl_t 	USART_HWFlowControl; // can be removed
	MUSART_SynchMode_t 		USART_SynchMode; // can be removed

	/* in synchronous mode need to config CPOL & CPHA  */

	MUSART_Oversampling_t 	USART_Oversampling;
	MUART_IT_ENABLE_t  	 	USART_InterruptEnable; // struct
}MUSART_Config_t;


/* ********************************************* */
STD_error_t		MUSART_stderrInit (MUSART_Config_t *ARG_pUSARTHandle);

STD_error_t 	MUSART_stderrSendChar(MUSART_Number_t ARG_numUSARTNum , char ARG_charString );
STD_error_t 	MUSART_stderrSendString	(MUSART_Number_t ARG_numUSARTNum , const char *ARG_ccharpString );

char 			MUSART_charReceiveCharNonBlocking(MUSART_Number_t ARG_numUSARTNum );
char 			MUSART_charReceiveCharBlocking(MUSART_Number_t ARG_numUSARTNum );
STD_error_t 	MUSART_stderrReceiveStringUntil(MUSART_Number_t ARG_numUSARTNum , char *ARG_charpReceived, char  ARG_charTerminator);

u8 				MUSART_u8GetFlagStatus(MUSART_Number_t ARG_numUSARTNum, u8 ARG_u8Flag);

STD_error_t 	MUART_stderrSetCallback(MUSART_Number_t ARG_numUSARTx, u8 ARG_u8InterruptSource , void(*ARG_pvoidfUserFunction)(void));


/* using ISR */
//STD_error_t 	MUSART_stderrSendData_IT	(USART_Config_t *ARG_pUSARTHandle, uint8_t *ARG_pu8TxBuffer , uint32_t ARG_u32Length);
//STD_error_t 	MUSART_stderrReceiveData_IT (USART_Config_t *ARG_pUSARTHandle, uint8_t *ARG_pu8pRxBuffer, uint32_t ARG_u32Length);


#endif
