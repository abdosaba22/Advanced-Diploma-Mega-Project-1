/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 SPI									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 October 3, 2023						*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MSPI_interface.h"
#include "MSPI_private.h"
#include "MSPI_config.h"

/* array of 3 pointers to struct Reg def */
static MSPI_RegDef_t *MSPI_pArr[SPI_MAX_NUM] = {SPI_1, SPI_2};

static volatile void(* pvoidfCallbackFunc[SPI_MAX_NUM][4])(void)={NULL_POINTER};

static char *MSPI_DataToBeReceived[SPI_MAX_NUM] 	= {NULL_POINTER}; /* ptr to var received data */
static char *MSPI_DataToBeSend[SPI_MAX_NUM]		 	= {NULL_POINTER}; /* ptr to var Send data */
static char *MSPI_CopyBassedAdd[SPI_MAX_NUM] 		= {NULL_POINTER}; 	/* copy ptr to var received data */
static u16 	MSPI_u8BufferLength[SPI_MAX_NUM] 		= {0}; 		/* buffer Length */

static u8 	MSPI_u8IRQReceiveMode[SPI_MAX_NUM] 	= {0};  		/* Tranceive Data or buffer  */



/*
	*SSM = 1 --> slave set SSI = 0,1 to select itself NSS of master not needed 
	*SSM = 0 --> SSI have no effect
	
	*SSM = 0 in Master and Slaves
	SSM = 0 --> SSOE = 1  so can't be used in Multi Master 
			--> SSOE = 0  so can used in Multi Master 
			
*/


STD_error_t MSPI_stderrInit						(const MSPI_Config_t* ARG_pconfigSPIConfig )
{
	STD_error_t L_stderrState = E_OK ;
	if( ARG_pconfigSPIConfig != NULL_POINTER )
	{
		/* check parameters of Struct */
		if( ARG_pconfigSPIConfig -> SPI_Num <= MSPI_NUM2 )
		{
			u32 L_u32TempReg=0;
			/* disable SPI before configuration */
			MSPI_pArr[ ARG_pconfigSPIConfig -> SPI_Num ] -> CR1 &= ~(1<<SPE_BIT);
			
			/* Assign values CLK Polarity , CLK Phase, MAster bit, Frequency prescaler, Data Size and Data order into Temp REG */
			L_u32TempReg = ( (ARG_pconfigSPIConfig -> ClockPolPha) << CPHA_BIT ) | ( (ARG_pconfigSPIConfig -> Mode) << MSTR_BIT ) | ( (ARG_pconfigSPIConfig -> DataOrder) << LSB_BIT ) | ( (ARG_pconfigSPIConfig -> DataSize) << DFF_BIT ) | ( (ARG_pconfigSPIConfig -> NSS_mode) << SSM_BIT ) ;
			/* Check communication mode */
			/* Full duplex and Transmit only not configure anything by default are 0 */	
			/*   */
			if ( MSPI_COMMUNI_MODE_DATA_RECEIVE_ONLY == ARG_pconfigSPIConfig->CommunicationMode )
			{
				SET_BIT(L_u32TempReg, RX_ONLY_BIT); // Set RXONLY  bit
			}
			else if( MSPI_COMMUNI_MODE_BIDIRECTIONAL_RECEIVE_ONLY == ARG_pconfigSPIConfig->CommunicationMode  || MSPI_COMMUNI_MODE_BIDIRECTIONAL_TRANSMIT_ONLY == ARG_pconfigSPIConfig->CommunicationMode )
			{
				L_u32TempReg |= ( ( ARG_pconfigSPIConfig -> CommunicationMode ) << BIDI_MODE_BIT);  /* Assign value which is 2 or 3 0b10 or 0b11 */
			}
			else
			{
				/* MISRA Rule */
			}
			
			/* Assign the CR1 value */
			MSPI_pArr[ ARG_pconfigSPIConfig -> SPI_Num ] -> CR1 = L_u32TempReg ;
			
			L_u32TempReg = 0 ;
			
			/* check master bit to configure SSOE bit in CR2*/
			if( MSPI_MASTER == ARG_pconfigSPIConfig -> Mode )
			{
				/* ASsign SSOE BIt */
				L_u32TempReg = ( (ARG_pconfigSPIConfig -> SSOE_Type) << SSOE_BIT );
			}
			else
			{
				/* MISRA Rule */
			}
			/* Enables interrupts */
//			u8 temp = ((ARG_pconfigSPIConfig-> InterruptEnable.TXE) << 7 ) | ( (ARG_pconfigSPIConfig-> InterruptEnable.RXNE) << 6)  | ( (ARG_pconfigSPIConfig-> InterruptEnable.ERR) << 5);
			L_u32TempReg |= ((ARG_pconfigSPIConfig-> InterruptEnable.TXE) << 7 ) | ( (ARG_pconfigSPIConfig-> InterruptEnable.RXNE) << 6)  | ( (ARG_pconfigSPIConfig-> InterruptEnable.ERR) << 5) ;
			
			/* Assign the CR2 value */
			MSPI_pArr[ ARG_pconfigSPIConfig -> SPI_Num ] -> CR2 = L_u32TempReg ;
			
			/* SET the Start Mode of SPI Peripheral */
			MSPI_pArr[ ARG_pconfigSPIConfig -> SPI_Num ]-> CR1 |= ( ARG_pconfigSPIConfig->Status << SPE_BIT);
			
			
		}
		else
		{
			L_stderrState = E_NOK ;
		}	
	}
	else
	{
		/* NULL pointer error */
		L_stderrState = E_NULL_POINTER ;
	}
	return L_stderrState;
}

STD_error_t MSPI_stderrEnable					( u8 ARG_u8SPINum )
{
	STD_error_t L_stderrState = E_OK ;
	if( ARG_u8SPINum <= MSPI_NUM2 )
	{
		/* Set Enable Bit*/
		MSPI_pArr[ ARG_u8SPINum ]-> CR1 |= ( 1 << SPE_BIT );
	}
	else
	{
		L_stderrState = E_NOK ;
	}
	return L_stderrState;
}

STD_error_t MSPI_stderrDisable					( u8 ARG_u8SPINum )
{
	STD_error_t L_stderrState = E_OK ;
	if( ARG_u8SPINum <= MSPI_NUM2 )
	{
		/* Clear Enable Bit*/
		MSPI_pArr[ ARG_u8SPINum ]-> CR1 &= ~( 1 << SPE_BIT );
	}
	else
	{
		L_stderrState = E_NOK ;
	}
	return L_stderrState;	
}

MSPI_FLAG_STATUS_t 	MSPI_flagstatusReadFlag		(u8 ARG_u8SPINum, MSPI_FLAG_t ARG_Flag)
{
	/* Read Flag Bit in SR and Return it */
	return ( (MSPI_pArr[ARG_u8SPINum]->SR >> ARG_Flag) & 0x01);
}

void 	MSPI_voidWaitUntilFlagSet				(u8 ARG_u8SPINum, MSPI_FLAG_t ARG_Flag)
{
	MSPI_FLAG_STATUS_t L_u8FlagState = MSPI_FLAG_RESET;
    while (MSPI_FLAG_SET != L_u8FlagState)
    {
    	L_u8FlagState=MSPI_flagstatusReadFlag(ARG_u8SPINum, ARG_Flag);
    }
	
}

/* in case SSM = 1, in Slave select SSI */
void 	MSPI_voidNSSControlSW					(u8 ARG_u8SPINum, MSPI_SW_SLAVE_STATUS_t ARG_SSIState)
{
	if (1 == ARG_SSIState )
	{
		// SSI bits
		SET_BIT(MSPI_pArr[ARG_u8SPINum]->CR1, SSI_BIT);
	}
	else
	{
		// Clear SSI bit
		CLEAR_BIT(MSPI_pArr[ARG_u8SPINum]->CR1, SSI_BIT);
	}
	
}

STD_error_t 	MSPI_stderrTransceiveData		(u8 ARG_u8SPINum, u8 *ARG_pu16ReceivedData, u8 ARG_u16DataToSend)
{
	STD_error_t L_stderrState = E_OK ;
    
	if(NULL_POINTER == ARG_pu16ReceivedData )
	{
		L_stderrState = E_NULL_POINTER;
	}
	else
	{
		if( ARG_u8SPINum <= MSPI_NUM2 )
		{
			/* Sending Data is Required */
			/* Wait Until The Transmit Buffer is Empty */
//			MSPI_voidWaitUntilFlagSet(ARG_u8SPINum, MSPI_TXE_FLAG);
		

			while( 1 == MSPI_flagstatusReadFlag(ARG_u8SPINum, BSY_BIT) );

			/* Receiving Data is Required */  
			/* Wait Until The Receive Buffer is Not Empty */
			MSPI_voidWaitUntilFlagSet(ARG_u8SPINum, MSPI_RXNE_FLAG);
		
			/* Read Received Data */
			*ARG_pu16ReceivedData = MSPI_pArr[ARG_u8SPINum]->DR;
		}
		else
		{
			L_stderrState = E_NOK ;
		}

    }
	
//	MSPI_pArr[ARG_u8SPINum]->DR = ARG_u16DataToSend;
//		while(GET_BIT(MSPI_pArr[ARG_u8SPINum]->SR,7)==1	);
//		return(MSPI_pArr[ARG_u8SPINum]->DR);

    return L_stderrState;
}

STD_error_t 	MSPI_stderrTransceiveBuffer		(u8 ARG_u8SPINum, u8 *ARG_pu8ReceivedData, u8 *ARG_pu8BufferToSend, u16 ARG_u16BufferSize)
{
	STD_error_t L_stderrState = E_OK ;

    if( NULL_POINTER == ARG_pu8BufferToSend || NULL_POINTER == ARG_pu8ReceivedData )
	{
		L_stderrState = E_NULL_POINTER;
	}
    else
    {
        /* 1st need to check SPI NUM */
		u16 L_u16Counter = 0;
        for (L_u16Counter = 0; L_u16Counter < ARG_u16BufferSize; L_u16Counter++)
        {
            MSPI_stderrTransceiveData(ARG_u8SPINum, &ARG_pu8ReceivedData[L_u16Counter], ARG_pu8BufferToSend[L_u16Counter]);
        }
    }
	
    return L_stderrState;
}

STD_error_t 	SPI_stderrTransceiveData_IT		(u8 ARG_u8SPINum, char *ARG_pcharReceivedData, char ARG_charDataToSend, void(*ARG_pvoidfUserFunction)(void))
{
	/* */
	STD_error_t L_stderrState = E_OK ;
	/* Check NULL pointer */
	if( NULL_POINTER !=ARG_pvoidfUserFunction && NULL_POINTER !=ARG_pcharReceivedData )
	{	
		if( ARG_u8SPINum <= MSPI_NUM2 )
		{
			/* Save address of data to be received */
			MSPI_DataToBeReceived[ARG_u8SPINum] = ARG_pcharReceivedData;
			MSPI_CopyBassedAdd[ARG_u8SPINum]  = ARG_pcharReceivedData;
			/* Save Type of Transceive Data or Buffer 0 to data 1 to Buffer */
			MSPI_u8IRQReceiveMode[ARG_u8SPINum] = 0;
			
			/* Assign callback func for Receive */
			pvoidfCallbackFunc[ARG_u8SPINum][MSPI_RXNE_FLAG] = ARG_pvoidfUserFunction;
			
			/* Wait Until The Transmit Buffer is Empty */
			MSPI_voidWaitUntilFlagSet(ARG_u8SPINum, MSPI_TXE_FLAG);

			/* Send Data */
			MSPI_pArr[ARG_u8SPINum]->DR = ARG_charDataToSend;
		
			/* RXNE must be enabled */
			MSPI_pArr[ARG_u8SPINum]->CR2 |= (1 << RXNEIE_BIT);;
			
		}
		else
		{
			L_stderrState = E_NOK ;
		}
	}
	else
	{
		L_stderrState = E_NULL_POINTER;
	}

	return L_stderrState;	
	
}
STD_error_t 	SPI_stderrTransceiveBuffer_IT	(u8 ARG_u8SPINum, char *ARG_pcharReceivedBuffer, char *ARG_pcharBufferToSend, u16 ARG_u16BufferSize, void (*ARG_pvoidfUserFunction)(void))
{
	/* */
	STD_error_t L_stderrState = E_OK ;
	/* Check NULL pointer */
	if( NULL_POINTER !=ARG_pvoidfUserFunction && NULL_POINTER !=ARG_pcharReceivedBuffer )
	{
		if( ARG_u8SPINum <= MSPI_NUM2 )
		{
			/* Save address of data to be received */
			MSPI_DataToBeReceived[ARG_u8SPINum] = ARG_pcharReceivedBuffer;
			MSPI_CopyBassedAdd[ARG_u8SPINum]  = ARG_pcharReceivedBuffer;
			/* Save Type of Transceive Data or Buffer 0 to data 1 to Buffer */
			MSPI_u8IRQReceiveMode[ARG_u8SPINum] = 1;

			/* assign the size of Buffer */
			MSPI_u8BufferLength[ARG_u8SPINum] = ARG_u16BufferSize;
			/* assign base address of send data */
			MSPI_DataToBeSend[ARG_u8SPINum] = ARG_pcharBufferToSend;

			/* Assign callback func for Receive */
			pvoidfCallbackFunc[ARG_u8SPINum][MSPI_RXNE_FLAG] = ARG_pvoidfUserFunction;

			/* Wait Until The Transmit Buffer is Empty */
			MSPI_voidWaitUntilFlagSet(ARG_u8SPINum, MSPI_TXE_FLAG);

			/* Send Data */
			MSPI_pArr[ARG_u8SPINum]->DR = *MSPI_DataToBeSend[ARG_u8SPINum]++;

			/* RXNE must be enabled */
			MSPI_pArr[ARG_u8SPINum]->CR2 |= (1 << RXNEIE_BIT);;

		}
		else
		{
			L_stderrState = E_NOK ;
		}
	}
	else
	{
		L_stderrState = E_NULL_POINTER;
	}

	return L_stderrState;
}


/* SPI1 Interrupt Handler */
void SPI1_IRQHandler(void)
{
    /* callback func */
	*MSPI_DataToBeReceived[MSPI_NUM1] = SPI_1 -> DR & 0xFF;
	/* Data not Buffer */
	if( 0 == MSPI_u8IRQReceiveMode[MSPI_NUM1]  )
	{
		pvoidfCallbackFunc[MSPI_NUM1][0]();
	}
	else
	{	
		static volatile u16 L_u16BufferCounter = 0;
		L_u16BufferCounter ++; /* increment counter */
		
		/* in case of buffer */
		if( L_u16BufferCounter == MSPI_u8BufferLength[MSPI_NUM1] )
		{
			L_u16BufferCounter=0;
			/* callback func */
			pvoidfCallbackFunc[MSPI_NUM1][0]();
			/* ReAssign Base Address */
			MSPI_DataToBeReceived[MSPI_NUM1] =MSPI_CopyBassedAdd[MSPI_NUM1] ; 
		}
		else
		{
			MSPI_DataToBeReceived[MSPI_NUM1]++; /* move address to next */
			/* Send Data */
			MSPI_pArr[MSPI_NUM1]->DR = *MSPI_DataToBeSend[MSPI_NUM1]++;

		}
		
	}
	
}
