
#include "LSTD_types.h"
#include "LBIT_math.h"
#include <stdint.h>
#include "APP.h"

extern char G_charFlagSPI;


int main(void)
{
	APP_stderrClockPins_init();
	APP_stderrPeripheral_init();

	for(;;)
	{
		switch(G_charFlagSPI)
		{
		case 1: APP_stderrDisplayTime(); break;
		case 2: APP_stderrDisplayAlarm(); break;
		default: break;
		}

	}
}
