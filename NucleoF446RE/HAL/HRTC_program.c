/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 RTC DS1307							*/
/* Layer       	:	 HAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 30, 2023					*/
/* Last Edit   	:	 December 5, 2023					*/
/* **************************************************** */


/* Library Includes */
#include "LSTD_types.h"
#include "LBIT_math.h"

/* SWC Includes */
#include "MI2C_Interface.h"
#include "HRTC_Interface.h"
#include "HRTC_private.h"



STD_error_t HRTC_stderrSetTime(HRTC_Config_t *ARG_pconTimeVal)
{
    /* return variable */
	STD_error_t L_stderrStatus = E_OK;
	/* array of 7 elements to store time */
    u8 L_u8TimeArr[HRTC_BUFFER_SIZE] = {0};
    
	if(ARG_pconTimeVal != NULL_POINTER)
    {
    	
		/*Prepare data to send to DS1037 convert To BCD Form */
    	u8 L_u8Seconds = (ConvetTo_BCD(ARG_pconTimeVal->Seconds)) | 0<<CH_BIT;
    	u8 L_u8Minuites = ConvetTo_BCD(ARG_pconTimeVal->Minuites);
    	u8 L_u8DayOfWeek = ARG_pconTimeVal->Day_of_Week;
    	u8 L_u8Date = ConvetTo_BCD(ARG_pconTimeVal->Date);
    	u8 L_u8Month = ConvetTo_BCD(ARG_pconTimeVal->Month);
    	u8 L_u8Year = ConvetTo_BCD(ARG_pconTimeVal->Year);
    	u8 L_u8Hours = ConvetTo_BCD(ARG_pconTimeVal->Hours);
    	
		/* convert to 24 display */
		switch(ARG_pconTimeVal->Display_Method)
    	{
    	case DISPLAY_24 : L_u8Hours |= DISPLAY_24 << BIT_12_24_DISPLAY;break;
    	case DISPLAY_12 : L_u8Hours |= (DISPLAY_12 << BIT_12_24_DISPLAY | (ARG_pconTimeVal->MidDay)<<AM_PM_BIT);break;
    	}
    	
		/*Assign the data in array to send*/
    	L_u8TimeArr[SECOND] = L_u8Seconds ;
    	L_u8TimeArr[MINUIT] = L_u8Minuites;
    	L_u8TimeArr[HOUR] = L_u8Hours;
    	L_u8TimeArr[DAY] = L_u8DayOfWeek;
    	L_u8TimeArr[DATE] = L_u8Date;
    	L_u8TimeArr[MONTH] = L_u8Month;
    	L_u8TimeArr[YEAR] = L_u8Year;
    	
		/* Send Data To RTC module Using I2C */
		/*Send start condition*/
    	MI2C_errSendStartCondition(MI2C1);
        /*Send DS1037 Address with write*/
    	MI2C_errSendSlaveAddress_RW(MI2C1, HRTC_ADDRESS, MI2C_WRITE);
    	/*intialise DS1307 Pointer*/
    	MI2C_errMasterSendData(MI2C1, HRTC_REGISTER_ADDRESS);
    	/*Send Data*/
        for(u8 Counter = SECOND ; Counter <= YEAR ; Counter++)
        {
       	 MI2C_errMasterSendData(MI2C1, L_u8TimeArr[Counter]);
        }
        /*Send Stop condition*/
        MI2C_voidSendStopCondition(MI2C1);

    }
    else
    {
    	L_stderrStatus = E_NULL_POINTER;
    }
    return L_stderrStatus;

}

STD_error_t HRTC_stderrReadTime(HRTC_Config_t *ARG_pconTimeVal)
{
	/* return variable */
    STD_error_t L_stderrStatus = E_OK;
	
    if(ARG_pconTimeVal != NULL_POINTER)
    {
    	/* Array to store Time from RTC */
		u8 L_u8TimeArr[HRTC_BUFFER_SIZE] = {0};
		
   	    /* Receive Data over I2C protocol */
		/* Send start condition */
   	    MI2C_errSendStartCondition(MI2C1);
        /* Send DS1037 Address with write */
    	MI2C_errSendSlaveAddress_RW(MI2C1, HRTC_ADDRESS, MI2C_WRITE);
    	/* intialise DS1307 Pointer to point 0x00 */
    	MI2C_errMasterSendData(MI2C1, HRTC_REGISTER_ADDRESS);
  	    /* receive Data from RTC */
		/* Send Repeated start condition */
  	    MI2C_errSendStartCondition(MI2C1);
    	/* Send DS1037 Address with Read */
    	MI2C_errSendSlaveAddress_RW(MI2C1, HRTC_ADDRESS, MI2C_READ);

    	/* Read data from DS1037 0 to 4  */
    	for(u8 i = 0; i<HRTC_BUFFER_SIZE - 2 ; i++)
    	{
    		MI2C_errMasterReadDataByte( &L_u8TimeArr[i],MI2C1);
    	}
		/* read 2 byte arr[5] & arr[6] */
    	/* Receive Data N=2 + Stop condition */
    	MI2C_errMasterReadData2Byte(&L_u8TimeArr[5],MI2C1);
    	

		/* Store Hour */
		if((L_u8TimeArr[HOUR]>>BIT_12_24_DISPLAY) == DISPLAY_24)
    	{
    		ARG_pconTimeVal->Display_Method = DISPLAY_24;
    		ARG_pconTimeVal->MidDay = NO_AM_PM;
    		ARG_pconTimeVal->Hours = ConvertTo_Decimal(L_u8TimeArr[HOUR]);
    	}
    	else
    	{
    		ARG_pconTimeVal->Display_Method = DISPLAY_12;
			/* read AM_PM Bit */
			ARG_pconTimeVal->MidDay = 1 & (L_u8TimeArr[HOUR]>>AM_PM_BIT);
			/*Clear 12-24 Bit and AM_PM Bit*/
            L_u8TimeArr[HOUR] &= HOUR_MASK; 
            ARG_pconTimeVal->Hours = ConvertTo_Decimal(L_u8TimeArr[HOUR]);
    	}
		

		/*Clear CH Bit*/
        L_u8TimeArr[SECOND] &= SECOND_MASK; 
		/* Convert to Decimal form */
        ARG_pconTimeVal->Seconds = ConvertTo_Decimal(L_u8TimeArr[SECOND]);
        ARG_pconTimeVal->Minuites = ConvertTo_Decimal(L_u8TimeArr[MINUIT]);
        ARG_pconTimeVal->Day_of_Week = L_u8TimeArr[DAY];
        ARG_pconTimeVal->Date = ConvertTo_Decimal(L_u8TimeArr[DATE]);
        ARG_pconTimeVal->Month = ConvertTo_Decimal(L_u8TimeArr[MONTH]);
        ARG_pconTimeVal->Year = ConvertTo_Decimal(L_u8TimeArr[YEAR]);
    }
    else
    {
   	 L_stderrStatus = E_NULL_POINTER;
    }
    return L_stderrStatus;
}

u8 ConvetTo_BCD(u8 ARG_u8DecimalVal)
{
	u8 L_u8RightDigit = ARG_u8DecimalVal % 10 ; /*Getting Right Digit*/
	u8 L_u8LeftDigit  = ARG_u8DecimalVal /10 ;  /*Getting left Digit*/
	u8 L_u8BCDVal=0;
    L_u8BCDVal = L_u8RightDigit | (L_u8LeftDigit << 4) ; /*Converting to BCD*/

    return L_u8BCDVal;
}
u8 ConvertTo_Decimal(u8 ARG_u8BCDVal)
{
	u8 L_u8RightDigit = ARG_u8BCDVal & 0b00001111 ; /*Getting Right Digit*/
	u8 L_u8LeftDigit  = (ARG_u8BCDVal >> 4) & 0b00001111 ;  /*Getting left Digit*/
	u8 L_u8DecimalVal=0;
	L_u8DecimalVal = L_u8LeftDigit * 10 + L_u8RightDigit; /*Converting to Decimal*/
	return L_u8DecimalVal;
}

