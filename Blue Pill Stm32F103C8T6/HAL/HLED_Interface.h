#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include <MGPIO_Interface.h>
#include <stdint.h>

#define LED_SourceConnnec		 0 // to turn on need high pin
#define LED_SinkConnec  		 1 // to turn on need LOW pin



typedef struct
{
	Port_t  	LedPort;
	PinNum_t 	LedPin;
	PinMode_t 	LedMode;
	uint8_t 	conn_type; /* connection type */
}HLED_t;

void HLED_Init(const HLED_t * LED_Config);

void HLED_TurnOn(const HLED_t * LED_Config);

void HLED_TurnOff(const HLED_t * LED_Config);

void HLED_Toggle(const HLED_t * LED_Config);

extern HLED_t LEDRed ;

//extern HLED_t LEDGreen ;


#endif
