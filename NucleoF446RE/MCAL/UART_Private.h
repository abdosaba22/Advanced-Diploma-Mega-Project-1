/* ************************************************ */
/* Author       : 	Abdalrahman Amin                */
/* SWC          : 	USART 			                */
/* MCu         	:	Stm32F446RE						*/
/* Layer        : 	MCAL                            */
/* Version      : 	1.0                             */
/* Date         : 	September 10, 2023              */
/* Last Edit    : 	N/A 			                */
/* ************************************************ */

#ifndef _MUSART_PRIVATE_H_
#define _MUSART_PRIVATE_H_

/*
 * USART flags
 */
#define MUSART_FLAG_TXE 					(1 << SR_TXE)
#define MUSART_FLAG_RXNE 					(1 << SR_RXNE)
#define MUSART_FLAG_TC 						(1 << SR_TC)


#define MUSART_NUM             				6U


#define MUSART_BRR_DIVFRA_BIT 				0U
#define MUSART_BRR_MANFRA_BIT 				4U

#define MFLAG_SET           1u
#define MFLAG_RESET         0u



typedef enum {
    CR1_SBK = 0,
    CR1_RWU,
    CR1_RE,
    CR1_TE,
    CR1_IDLEIE,
    CR1_RXNEIE,
    CR1_TCIE,
    CR1_TXEIE,
    CR1_PEIE,
    CR1_PS,
    CR1_PCE,
    CR1_WAKE,
    CR1_M,
    CR1_UE,
    CR1_OVER8 = 15
}MUSART_CR1Bits_t ;

typedef enum {
    CR2_ADD = 0,
    CR2_LBDL = 5,
    CR2_LBDIE,
    CR2_LBCL = 8,
    CR2_CPHA,
    CR2_CPOL,
    CR2_CLKEN,
    CR2_STOP = 12,
    CR2_LINEN = 14
}MUSART_CR2Bits_t;

typedef enum {
    CR3_EIE = 0,
    CR3_IREN,
    CR3_IRLP,
    CR3_HDSEL,
    CR3_NACK,
    CR3_SCEN,
    CR3_DMAR,
    CR3_DMAT,
    CR3_RTSE,
    CR3_CTSE,
    CR3_CTSIE,
    CR3_ONEBIT
}MUSART_CR3Bits_t;

typedef enum {
    SR_PE = 0,
    SR_FE,
    SR_NE,
    SR_ORE,
    SR_IDLE,
    SR_RXNE,
    SR_TC,
    SR_TXE,
    SR_LBD,
    SR_CTS
}MUSART_SRBits_t;

/********************* UART Peripheral Base Addresses *****************/

#define MUSART2_BASE_ADDRESS       		0x40004400UL
#define MUSART3_BASE_ADDRESS       		0x40004800UL
#define MUSART4_BASE_ADDRESS        	0x40004C00UL
#define MUSART5_BASE_ADDRESS        	0x40005000UL

#define MUSART1_BASE_ADDRESS        		0x40011000UL
#define MUSART6_BASE_ADDRESS        		0x40014000UL

/***************** USART Register Definition Structure *************/
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}MUSART_RegDef_t	;

/******************  USART Peripheral Defination   **************/
#define USART1              ((MUSART_RegDef_t*)MUSART1_BASE_ADDRESS)
#define USART2              ((MUSART_RegDef_t*)MUSART2_BASE_ADDRESS)
#define USART3              ((MUSART_RegDef_t*)MUSART3_BASE_ADDRESS)
#define USART4              ((MUSART_RegDef_t*)MUSART4_BASE_ADDRESS)
#define USART5              ((MUSART_RegDef_t*)MUSART5_BASE_ADDRESS)
#define USART6              ((MUSART_RegDef_t*)MUSART6_BASE_ADDRESS)


#endif
