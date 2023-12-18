/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 I2C								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 29, 2023					*/
/* Last Edit   	:	 December 3,2023					*/
/* **************************************************** */

#ifndef M_I2C_INTERFACE_H_
#define M_I2C_INTERFACE_H_


/*********************/

#define MI2C_WRITE 0
#define MI2C_READ  1

/*Status Flags*/
#define MI2C_START_CONDITION_SENT   		0
#define MI2C_SLAVE_ADDR_SENT        		1
#define MI2C_BYTE_TRANSFER_FINISHED       	2
#define MI2C_STOP_CONDITION_SENT    		4
#define MI2C_DATA_BUFFER_NOT_EMPTY  		6
#define MI2C_DATA_BUFFER_EMPTY      		7
#define MI2C_ACK_FAIL               		10
#define MI2C_BUSY                   		12


typedef enum
{
	MI2C1,
	MI2C2,
	MI2C3
}MI2C_Number_t;

typedef enum
{
	SM_MOOD,             /*Standard mood 100Kbps*/
	FM_MOOD              /*Fast mood 400Kbps*/
}MI2C_Mode_t;


typedef enum
{
	I2C_POLLING,         /*wait for transmit and receive the data*/
	I2C_DMA,             /*Using DMA for transmit and receive the data*/
	I2C_INTERRUPT        /*using Interrupt for transmit and receive the data*/
}MI2C_TransferMethod_t;

typedef struct
{
	u16 OwnAddress;    /*Master/Slave Own Address*/
	MI2C_Mode_t  Speed_Mood;     /*set speed mood*/
	MI2C_Number_t Num;       /*Select I2C number to configure*/
	MI2C_TransferMethod_t  Transfer_Method;    /*Select method of transferring the data*/
}MI2C_Config_t;

typedef enum
{
	MI2C_NULL_PTR_ERR,
	MI2C_NOERR,
	MI2C_START_ERR,
	MI2C_AddressErr,
	MI2C_TransmittERR,
	MI2C_RECEIVEERR,
	MI2C_TIMEOUTERROR,
}MI2C_Error_t;


/* Function Prototypes */
void MI2C_voidMasterInit(MI2C_Number_t ARG_I2CNum, u16 ARG_u16OwnAddress, MI2C_Mode_t ARG_modeSpeed);
MI2C_Error_t MI2C_errSendStartCondition(MI2C_Number_t ARG_I2CNum);
MI2C_Error_t MI2C_errSendSlaveAddress_RW(MI2C_Number_t ARG_I2CNum, u8 ARG_u8SlaveAddress, u8 ARG_u8ReadWrite);
void MI2C_voidSendStopCondition(MI2C_Number_t ARG_I2CNum);
MI2C_Error_t MI2C_errMasterSendData(MI2C_Number_t ARG_I2CNum, u8 ARG_u8Data);
MI2C_Error_t MI2C_errMasterReadDataByte(u8 *ARG_pu8Data, MI2C_Number_t ARG_I2CNum);
//MI2C_Error_t MI2C_errMasterReadDataByteARR(MI2C_Number_t ARG_I2CNum, u8 *ARG_pu8Data, u8 ARG_u8ArrSize);
MI2C_Error_t MI2C_errFlagPolling(MI2C_Number_t ARG_I2CNum, u8 ARG_u8Flag);
void CLR_SR(MI2C_Number_t ARG_I2CNum);
MI2C_Error_t MI2C_errMasterReadData2Byte( u8 *ARG_pu8Data, MI2C_Number_t ARG_I2CNum);

#endif
