/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	main                            */
/* Version      : 	1.0                             */
/* Date         : 	December 12, 2023	            */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */
#include <stdint.h>

#include "LBIT_math.h"
#include "LSTD_types.h"

#include "App.h"

int main(void)
{
	APP_stderrClockPins_init();
	APP_stderrPeripheral_init();

	u8 L_u8SystemState = E_NOK, L_u8Lock = 1 ;

	STD_Option_t L_stdopChosenOption;
    /* Loop forever */
	for(;;)
	{
		L_u8Lock = APP_u8ReadStart();
		while(L_u8Lock == E_OK)
		{
			L_u8SystemState = APP_stderrReadIDPassword();
			L_u8Lock = L_u8SystemState;
			while(L_u8SystemState == E_OK)
			{
				L_stdopChosenOption = APP_stdopDisplayOptions();
				switch(L_stdopChosenOption)
				{
				case READ_TIME_OPTION:  APP_stderrReadTimeOption(); break;
				case SET_TIME_OPTION :  APP_stderrSetTimeOption() ; break;
				case SET_ALARM_OPTION:  APP_stderrSetAlarmOption(); break;
				case EXIT_OPTION	 : 	L_u8SystemState = E_NOK; L_u8Lock =E_NOK; break;
				case WRONG_OPTION	 :  /* do nothing */ break;
				default: break;
				}
			}

		}

	}
}
