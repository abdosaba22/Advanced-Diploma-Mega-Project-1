/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 NVIC								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.0               					*/
/* Date        	:	 September 18, 2023					*/
/* Last Edit   	:	 N/A			   					*/
/* **************************************************** */


#ifndef _MNVIC_PRIVATE_H_
#define _MNVIC_PRIVATE_H_


/******************* MNVIC Peripheral Base Addresses ********************/

#define MNVIC_BASE_ADDRESS			0xE000E100UL
/**********************************************************************/

/************************* MNVIC Register Definition Structure ***********************/
typedef struct 
{
    volatile u32 	ISER[8];      /* Interrupt Set-enable Registers */
    u32 			reserved1[24];        // difference 96 / 4 
    volatile u32 	ICER[8];      /* Interrupt Clear-enable Registers */
    u32 			reserved2[24];        
    volatile u32 	ISPR[8];      /* Interrupt Set-pending Registers */
    u32 			reserved3[24];        
    volatile u32 	ICPR[8];      /* Interrupt Clear-pending Registers */
    u32 			reserved4[24];        
    volatile u32 	IABR[8];      /* Interrupt Active Bit Registers */
    u32 			reserved5[56]; 		/* 0x400 - 0x320 / 4 = 56 */
    volatile u32 	IPR[240];      /* Interrupt Priority Registers  */    
    u32 			reserved6[580];
    volatile u32 	STIR;              /* Software Trigger Interrupt Register */
}MNVIC_REGDEF_t;
/*************************************************************/

/************************ MNVIC Definition **********************/
#define NVIC				 	((MNVIC_REGDEF_t*) MNVIC_BASE_ADDRESS)

#define MSCB_AIRCR 				*((volatile u32*)0xE000ED0CU)
/*************************************************************/


/************** Defines Private magic num ***************/

#define MNVIC_IRQ_REGSHIFT				5U
#define MNVIC_IRQ_BITSMASK				0x1FU
#define MNVIC_IRQ_PIRSIZE				4U
#define MNVIC_BITMASK					1U
#define MNVIC_IRQ_PIR_SHIFTBITS			4U

#define MSCB_AIRCR_VECTKEY				0x05FA0000U

#define MSCB_PRIGROUP_BIT0				8U

#define MNVIC_PIR4BIT_MASK              0x0F
#define MNVIC_PIR3BIT_MASK              0x07
#define MNVIC_PIR2BIT_MASK              0x03
#define MNVIC_PIR1BIT_MASK				0x01

#endif
