#include "LBIT_math.h"
#include "LSTD_types.h"

#include "MGPIO_interface.h"
#include "HBUTTON_Private.h"
#include "HBUTTON_Interface.h"

void HButton_voidInit(MGPIO_PORT_t ARG_BUTPort,MGPIO_PINNUM_t ARG_BUTPin,MGPIO_PULLUD_t ARG_BUTPUPD)
{
    MGPIO_CONFIG_t L_conButtonPin;

    /* GPIO Ports Clock Enable */
	/* .....  */
    /*Configure GPIO pin */
    L_conButtonPin.Port= ARG_BUTPort;
    L_conButtonPin.Pin = ARG_BUTPin;
    L_conButtonPin.Mode = INPUT;
    L_conButtonPin.PullType = ARG_BUTPUPD;
    
    MGPIO_stderrPinConfig(&L_conButtonPin);
}

uint8_t HButton_u8Read(MGPIO_PORT_t ARG_BUTPort,MGPIO_PINNUM_t ARG_BUTPin)
{
	uint8_t L_u8buttonval;
	MGPIO_stderrReadPinValue(&L_u8buttonval, ARG_BUTPort, ARG_BUTPin);
    return L_u8buttonval;
}
