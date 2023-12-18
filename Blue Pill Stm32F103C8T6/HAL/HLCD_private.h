/* ************************************************ */
/* Author      : Abd-alrahman Amin                  */
/* SWC         : LCD                                */
/* Layer       : HAL                                */
/* Version     : 1.1                                */
/* Date        : August 7, 2023                     */
/* Last Edit   : August 8, 2023	                    */
/* ************************************************ */


#ifndef _HLCD_PRIVATE_H_
#define _HLCD_PRIVATE_H_


/* include config */


// /* Macros needed */
// #define HLCD_DATA_PORT_INIT()						MDIO_stderrSetPortDirection(HLCD_DATA_PORT,0xFF)
// #define HLCD_CTRL_INIT(X) 							MDIO_stderrSetPinDirection(HLCD_CTRL_PORT, X ,MDIO_OUTPUT)
// #define HLCD_DATA_INIT(X) 							MDIO_stderrSetPinDirection(HLCD_DATA_PORT, X ,MDIO_OUTPUT)
// #define HLCD_SEND_DATA_PORT(X)						MDIO_stderrSetPortValue(HLCD_DATA_PORT , X)

/* commands */
//#define LCD_START_LINE_1					0x80
//#define LCD_START_LINE_2					0xC0
//#define LCD_CLEAR_DISPLAY 					0x01
//#define LCD_CURSOR_ON 						0x0E
//#define LCD_CURSOR_OFF			 			0x0C
//#define LCD_SHIFT_RIGHT 					0x18
//#define LCD_SHIFT_LEFT 						0x1C
//#define LCD_MOVE_LEFT 						0x10
//#define LCD_MOVE_RIGHT 						0x14
//#define ENABLE_4BIT_MODE 					0x20
//#define LCD_FUNCTION_SET					0x28
//#define LCD_ENTRY_MODE_SET 					0x06
//#define LCD_DISPLAY_OFF 					0x08
//#define LCD_INIT 							0x30

#define HLCD_RS(X) 									GPIO_u8setpinValue(HLCD_CTRL_PORT, HLCD_RS_PIN, X)
#define HLCD_EN(X) 									GPIO_u8setpinValue(HLCD_CTRL_PORT, HLCD_EN_PIN, X)


#define HLCD_D4(X) 									GPIO_u8setpinValue(HLCD_DATA_PORT, HLCD_D4_PIN, X)
#define HLCD_D5(X) 									GPIO_u8setpinValue(HLCD_DATA_PORT, HLCD_D5_PIN, X)
#define HLCD_D6(X) 									GPIO_u8setpinValue(HLCD_DATA_PORT, HLCD_D6_PIN, X)
#define HLCD_D7(X) 									GPIO_u8setpinValue(HLCD_DATA_PORT, HLCD_D7_PIN, X)


#endif
