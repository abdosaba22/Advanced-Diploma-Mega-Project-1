/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 I2C								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 29, 2023					*/
/* Last Edit   	:	 December 3,2023					*/
/* **************************************************** */


/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"
/* SWC Includes */
#include "MI2C_Interface.h"
#include "MI2C_private.h"




static MI2C_REGDEF_t * I2C_ARR[3] = {I2C1,I2C2,I2C3};


// STD_error_t MI2C_stderrMasterInit(MI2C_Config_t *ARG_stConfig)
void MI2C_voidMasterInit(MI2C_Number_t ARG_I2CNum, u16 ARG_u16OwnAddress, MI2C_Mode_t ARG_modeSpeed)
{
    // STD_error_t L_stderrError = E_OK;
  
	//I2C_ARR[ARG_I2CNum]->I2C_CR1 |= 1<<15;
	u16 L_u16CCR_Val = 0,L_u16TRISE_Val=0;
	I2C_ARR[ARG_I2CNum]->OAR1 = OAR1_MASK;   /*Clear Address bits*/
	I2C_ARR[ARG_I2CNum]->OAR1 |= ((ARG_u16OwnAddress)<<MI2C_OAR1_ADD1) | 1<<14; ; /*Set the Address*/
	I2C_ARR[ARG_I2CNum]->CR2  = CR2_MASK;   /*Clear control register 2*/
	I2C_ARR[ARG_I2CNum]->CR2  |=  APB1_FREQUENCY;  /*Setting the APB1 Bus frequency*/
	
	I2C_ARR[ARG_I2CNum]->CCR  =  CCR_MASK;   /*Clear Clock control Register*/
	I2C_ARR[ARG_I2CNum]->CCR  |= (ARG_modeSpeed)<<MI2C_CCR_FS; /*Select SM or FM Mood*/
	I2C_ARR[ARG_I2CNum]->TRISE = TRISE_MASK;   /*Clear TRISE register*/
	/*Configure CCR Value and TRISE Value*/
	switch (ARG_modeSpeed)
	{
	case SM_MOOD :
	   L_u16CCR_Val = (u16)APB1_FREQUENCY * SM_CCR_MUL; // 40
	   L_u16TRISE_Val = (u16)APB1_FREQUENCY + TRISE_KEY; // 9
	   I2C_ARR[ARG_I2CNum]->CCR |= L_u16CCR_Val;
	   I2C_ARR[ARG_I2CNum]->TRISE |= L_u16TRISE_Val;
	   break;
	case FM_MOOD :
	   L_u16CCR_Val = (u16)APB1_FREQUENCY * FM_CCR_MUL / FM_CCR_DIV;
	   L_u16TRISE_Val = ((u16)APB1_FREQUENCY * FM_TRISE_MUL / FM_TRISE_DIV) + TRISE_KEY;
	   I2C_ARR[ARG_I2CNum]->CCR |= L_u16CCR_Val;
	   I2C_ARR[ARG_I2CNum]->TRISE |= L_u16TRISE_Val;
	   break;
	}
	I2C_ARR[ARG_I2CNum]->CR1  =  CR1_MASK; /*Clear Control register 1*/
	I2C_ARR[ARG_I2CNum]->CR1  |= 1<<MI2C_CR1_ACK;   /*Enable Acknowledge Bit*/

	/*Enable I2C peripheral*/
	I2C_ARR[ARG_I2CNum]->CR1 |= MI2C_ENABLE;
	I2C_ARR[ARG_I2CNum]->CR1  |= 1<<MI2C_CR1_ACK;   /*Enable Acknowledge Bit*/
  
}

MI2C_Error_t MI2C_errSendStartCondition(MI2C_Number_t ARG_I2CNum)
{
	I2C_ARR[ARG_I2CNum]->CR1 = 0x401;

	MI2C_Error_t L_errStatus = MI2C_NOERR;  /*Define Error Status*/
	//u16 L_u16SR1Val = 0; /*Define variable to carry SR1 value register*/
	/*Set START BIT*/
	I2C_ARR[ARG_I2CNum]->CR1 |= 1<<MI2C_CR1_START;
	
	/*Wait till SB Bit is Set*/
	L_errStatus = MI2C_errFlagPolling(ARG_I2CNum , MI2C_START_CONDITION_SENT);

	return L_errStatus;
}

MI2C_Error_t MI2C_errSendSlaveAddress_RW(MI2C_Number_t ARG_I2CNum, u8 ARG_u8SlaveAddress, u8 ARG_u8ReadWrite)
{
	u8 L_u8Address = (ARG_u8SlaveAddress<< MI2C_OAR1_ADD1) | ARG_u8ReadWrite; /* assign address with R_W Access */
	u16 L_u16SR_Val = 0; /*Define variable to carry SR1,SR2 value registers*/
	MI2C_Error_t L_errStatus = MI2C_NOERR; /*Define Error Status*/

	/*Clearing SB Event by Reading SR1 register*/
//	L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR1;
    /*Sending Address With Writing Bit*/
	I2C_ARR[ARG_I2CNum]->DR = L_u8Address;

	/*Wait until ADDR Bit is set*/
	while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR1, MI2C_SR1_ADDR) );
//	L_errStatus = MI2C_errFlagPolling(ARG_I2CNum , MI2C_SR1_ADDR);

	/*Clearing Event By Reading SR1, SR2 Registers*/
	L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR1;
	L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR2;

	return L_errStatus;
}

void MI2C_voidSendStopCondition(MI2C_Number_t ARG_I2CNum)
{
	/*CLR POS bit*/
	I2C_ARR[ARG_I2CNum]->CR1 &= ~(1<<MI2C_CR1_POS);
	/*Set Stop Bit*/
    I2C_ARR[ARG_I2CNum]->CR1 |= 1<<STOP_BIT;
}

MI2C_Error_t MI2C_errMasterSendData(MI2C_Number_t ARG_I2CNum, u8 ARG_u8Data)
{
	MI2C_Error_t L_errStatus = MI2C_NOERR; /*Define Error Status*/
	I2C_ARR[ARG_I2CNum]->DR = ARG_u8Data;  /*Writing data into DR register*/

	/*wait until the TXE bit is set*/
	while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR1, MI2C_DATA_BUFFER_EMPTY) );
//	L_errStatus = MI2C_errFlagPolling(ARG_I2CNum , MI2C_DATA_BUFFER_EMPTY);
	
	return L_errStatus;

}

MI2C_Error_t MI2C_errMasterReadDataByte(u8 *ARG_pu8Data, MI2C_Number_t ARG_I2CNum)
{
	MI2C_Error_t L_errStatus = MI2C_NOERR; /*Define Error Status*/

	if(ARG_pu8Data != NULL_POINTER)
	{
        /*Waiting until the RXNe bit is Raised*/
		while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR1, MI2C_DATA_BUFFER_NOT_EMPTY) );
		/*Reading Data Register*/
		*ARG_pu8Data = I2C_ARR[ARG_I2CNum]->DR;
	}
	else
	{
		L_errStatus = MI2C_NULL_PTR_ERR;
	}

	return L_errStatus;
}


MI2C_Error_t MI2C_errFlagPolling(MI2C_Number_t ARG_I2CNum, u8 ARG_u8Flag)
{
	MI2C_Error_t L_errStatus = MI2C_NOERR; /*Define Error Status */
//	u32 L_u16SR_Val =0 ,L_u16Counter =0;
	/* BUSY Flag in SR2 Reg */
	if(ARG_u8Flag == MI2C_BUSY)
	{
		/* we can use STK instead in timeout */	
		while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR2, MI2C_SR2_BUSY) );//&& L_u16Counter != TIME_OUT)
//			L_u16Counter++;
	}
	else
	{
		while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR1, ARG_u8Flag) );//&& L_u16Counter != TIME_OUT)
//			L_u16Counter++;
	}

//	else
//	{
//		/*Clearing Event By Reading SR1, SR2 Registers*/
//		L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR1;
//		L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR2;
//	}
	
	return L_errStatus;
}
void CLR_SR(MI2C_Number_t ARG_I2CNum)
{
	u16 L_u16SR_Val = 0;
	/*Clearing Event By Reading SR1, SR2 Registers*/
	L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR1;
	L_u16SR_Val = I2C_ARR[ARG_I2CNum]->SR2;
}

MI2C_Error_t MI2C_errMasterReadData2Byte( u8 *ARG_pu8Data, MI2C_Number_t ARG_I2CNum)
{
	MI2C_Error_t L_errStatus = MI2C_NOERR; /*Define Error Status*/

	/*Clear Acknowledge bit*/
	I2C_ARR[ARG_I2CNum]->CR1 &= ~(1<<MI2C_CR1_ACK);
	/*Set POS bit*/
	I2C_ARR[ARG_I2CNum]->CR1 |= 1<<MI2C_CR1_POS;
//	CLR_SR(ARG_I2CNum);
	/*Wait Until BTF bit is set*/
	while(!GET_BIT(I2C_ARR[ARG_I2CNum]->SR1, MI2C_BYTE_TRANSFER_FINISHED) );
//    		L_errStatus = MI2C_errFlagPolling(ARG_I2CNum , MI2C_BYTE_TRANSFER_FINISHED);
	/*Send Stop Condition*/
	I2C_ARR[ARG_I2CNum]->CR1 |= 1<<MI2C_CR1_STOP;
	/*Reading Data Register*/
	ARG_pu8Data[0] = I2C_ARR[ARG_I2CNum]->DR;
	ARG_pu8Data[1] = I2C_ARR[ARG_I2CNum]->DR;

	/*Set POS bit*/
	I2C_ARR[ARG_I2CNum]->CR1 &= ~(1<<MI2C_CR1_POS);

	return L_errStatus;
}
