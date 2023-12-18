/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 SPI									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f446RE       						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 September 30, 2023						*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef _MSPI_INTERFACE_H_
#define _MSPI_INTERFACE_H_


typedef enum
{
    MSPI_NUM1 ,
    MSPI_NUM2 ,
    MSPI_NUM3 ,
    // MSPI_NUM4 ,
} MSPI_Num_t;

typedef enum
{
    MSPI_SLAVE = 0,
    MSPI_MASTER

} MSPI_Mode_t;

typedef enum
{
    MSPI_DFF_1BYTE = 0,
    MSPI_DFF_2BYTE,
} MSPI_DATA_SIZE_t;

typedef enum
{
    MSPI_POLPHA_NONINVERTING_LEADING	,	
    MSPI_POLPHA_NONINVERTING_TAILLING,	
	MSPI_POLPHA_INVERTING_LEADING	,	
    MSPI_POLPHA_INVERTING_TAILLING	,	
} MSPI_CPOLPHA_t;

typedef enum
{
    MSPI_NSS_HW_MANAGE,
    MSPI_NSS_SW_MANAGE,
} MSPI_SLAVE_MANAGEMENT_t;

typedef enum
{
    MSPI_PERIPH_CLK_BY2   ,
    MSPI_PERIPH_CLK_BY4   ,
    MSPI_PERIPH_CLK_BY8   ,
    MSPI_PERIPH_CLK_BY16  ,
    MSPI_PERIPH_CLK_BY32  ,
    MSPI_PERIPH_CLK_BY64  ,
    MSPI_PERIPH_CLK_BY128 ,
    MSPI_PERIPH_CLK_BY256 ,
} MSPI_PRESCALER_t;

typedef enum
{
    MSPI_MSB_FIRST = 0,
    MSPI_LSB_FIRST,
} MSPI_DIRECTION_t;

typedef enum
{
    MSPI_COMMUNI_MODE_FULL_DUPLEX          	 		, 	/* BIDIMODE = 0, RXONLY = 0 , */
    MSPI_COMMUNI_MODE_DATA_TRANSMIT_ONLY   	 		, 	/* BIDIMODE = 0, RXONLY = 0 , */
    MSPI_COMMUNI_MODE_DATA_RECEIVE_ONLY    	 		, 	/* BIDIMODE = 0, RXONLY = 1 , */ 
	MSPI_COMMUNI_MODE_BIDIRECTIONAL_RECEIVE_ONLY 	, 	/* BIDIMODE = 1 , BIDIOE = 0 , 2 in this case MOSI in MAster connected to MISO 		*/
	MSPI_COMMUNI_MODE_BIDIRECTIONAL_TRANSMIT_ONLY 	,   /* BIDIMODE = 1 , BIDIOE = 1 , 3 in this case MOSI in MAster connected to MISO		*/

} MSPI_COMMUNICATION_Mode_t;

typedef enum
{
    MSPI_SSI_SELECTED = 0,
    MSPI_SSI_NOT_SELECTED,
	
} MSPI_SW_SLAVE_STATUS_t;

typedef enum
{
    MSPI_INT_DISABLED = 0,
    MSPI_INT_ENABLED,
	
} MSPI_INT_STATUS_t;

/* in Master mode */
typedef enum
{
    MSPI_SSOUT_DIS = 0, /* used in MultiMaster mode */
    MSPI_SSOUT_EN,

} MSPI_SSO_TYPE_t;

typedef enum
{
    MSPI_FLAG_RESET = 0,
    MSPI_FLAG_SET = 1,

} MSPI_FLAG_STATUS_t;


typedef enum
{
	MSPI_RXNE_FLAG ,		/* RECEIVE BUFFER NE FLAG , 	    */
    MSPI_TXE_FLAG ,         /* TRANSMIT BUFFER FLAG ,     		*/
    MSPI_RES,
	MSPI_UDR_FLAG,          /* UNDERRUN FLAG,               	*/
    MSPI_CRCERR_FLAG ,      /* CRC ERROR FLAG ,             	*/
    MSPI_MODEF_FLAG ,       /* MODE FAULTFLAG ,            		*/
    MSPI_OVR_FLAG ,         /* OVERRUN FLAG ,               	*/
    MSPI_BSY_FLAG ,         /* BUSY FLAG ,                 		*/
    MSPI_FRE_FLAG ,	        /* FRAME ERROR FLAG ,			 	*/

} MSPI_FLAG_t; 


typedef struct 
{
	u8 ERR  : 1 ;
	u8 RXNE : 1 ;
	u8 TXE 	: 1 ;

} MSPI_INT_ENABLE_t;

typedef enum
{
	MSPI_DISABLE,
	MSPI_ENABLE,

} MSPI_Status_t;

 
typedef struct 
{
	MSPI_Num_t 					SPI_Num; // SPI1 or SPI2
	MSPI_Mode_t 				Mode; // Master or slave
	MSPI_DATA_SIZE_t 			DataSize; // 8-bit or 16 bit 
	MSPI_CPOLPHA_t				ClockPolPha; // 
	MSPI_SLAVE_MANAGEMENT_t  	NSS_mode; // SW or HW --> SSM = 0 or 1 
	MSPI_PRESCALER_t 			Prescaler; // 2:256
	MSPI_DIRECTION_t 		 	DataOrder; // LSB or MSB
	MSPI_COMMUNICATION_Mode_t 	CommunicationMode; // full duplex ,, only trans only receive
	MSPI_SSO_TYPE_t 			SSOE_Type;
	MSPI_INT_ENABLE_t 			InterruptEnable;
	MSPI_Status_t				Status;  // Enabled or Disabled
	
}MSPI_Config_t;




STD_error_t MSPI_stderrInit						(const MSPI_Config_t* ARG_pconfigSPIConfig );

STD_error_t MSPI_stderrEnable					( u8 ARG_u8SPINum );
STD_error_t MSPI_stderrDisable					( u8 ARG_u8SPINum );

MSPI_FLAG_STATUS_t 	MSPI_flagstatusReadFlag		(u8 ARG_u8SPINum, MSPI_FLAG_t ARG_Flag);
void 	MSPI_voidWaitUntilFlagSet				(u8 ARG_u8SPINum, MSPI_FLAG_t ARG_Flag);
void 	MSPI_voidNSSControlSW					(u8 ARG_u8SPINum, MSPI_SW_SLAVE_STATUS_t ARG_SSIState);

STD_error_t 	MSPI_stderrTransceiveData		(u8 ARG_u8SPINum, u8 *ARG_pu16ReceivedData, u8 ARG_u16DataToSend);
STD_error_t 	MSPI_stderrTransceiveBuffer		(u8 ARG_u8SPINum, u8 *ARG_pu8ReceivedData, u8 *ARG_pu8BufferToSend, u16 ARG_u16BufferSize);

STD_error_t 	SPI_stderrTransceiveData_IT		(u8 ARG_u8SPINum, char *ARG_pcharReceivedData, char ARG_charDataToSend, void(*ARG_pvoidfUserFunction)(void));
STD_error_t 	SPI_stderrTransceiveBuffer_IT	(u8 ARG_u8SPINum, char *ARG_pcharReceivedBuffer, char *ARG_pcharBufferToSend, u16 ARG_u16BufferSize, void (*ARG_pvoidfUserFunction)(void));







#endif
