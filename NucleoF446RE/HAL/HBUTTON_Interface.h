#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include "MGPIO_interface.h"
#include <stdint.h>

void HButton_voidInit(MGPIO_PORT_t BUT_Port,MGPIO_PINNUM_t BUT_Pin,MGPIO_PULLUD_t BUT_PUPD);

uint8_t HButton_u8Read(MGPIO_PORT_t BUT_Port,MGPIO_PINNUM_t BUT_Pin);

#endif
