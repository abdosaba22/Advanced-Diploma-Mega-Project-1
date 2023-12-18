/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 SPI									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f446RE       						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 September 30, 2023						*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef _MSPI_PRIVATE_H_
#define _MSPI_PRIVATE_H_

#define MSPI1_BASE_ADDRESS			0x40013000UL
#define MSPI2_BASE_ADDRESS			0x40003800UL
#define MSPI3_BASE_ADDRESS			0x40003C00UL
// #define MSPI4_BASE_ADDRESS			0x40013400UL



/*************** SPI Register Definition Structure **********/

typedef struct
{
  volatile u32 			CR1;
  volatile u32 			CR2;
  volatile u32 			SR;
  volatile u32 			DR;
  volatile u32 			CRCPR;
  volatile u32 			RXCRCR;
  volatile u32 			TXCRCR;
  volatile u32 			I2SCFGR;
  volatile u32 			I2SPR;
} MSPI_RegDef_t;


/******************  SPI Peripheral Defination   **************/
#define SPI_1    						((MSPI_RegDef_t*)MSPI1_BASE_ADDRESS)
#define SPI_2    						((MSPI_RegDef_t*)MSPI2_BASE_ADDRESS)
#define SPI_3    						((MSPI_RegDef_t*)MSPI3_BASE_ADDRESS)

/*******************************************************************/
/* needed enums and defines */
typedef enum {
    CPHA_BIT = 0,
    CPOL_BIT,
    MSTR_BIT,
    BR_0_BIT,
    SPE_BIT=6,
    LSB_BIT,
    SSI_BIT,
    SSM_BIT,
	RX_ONLY_BIT,
    DFF_BIT,
	CRC_NEXT_BIT,
    CRC_EN_BIT,
    BIDI_OE_BIT,
    BIDI_MODE_BIT,
	
} MSPI_CR1Bits_t;

typedef enum {
    RXDMAEN_BIT = 0,
    TXDMAEN_BIT,
    SSOE_BIT,
    Res1,
    Res2,
    ERRIE_BIT,
    RXNEIE_BIT,
    TXEIE_BIT,
	
} MSPI_CR2Bits_t ;

typedef enum {
    RXNE_BIT = 0,
    TXE_BIT,
    CHSIDE_BIT,
    UDR_BIT,
    CRCERR_BIT,
    MODF_BIT,
	OVR_BIT,
	BSY_BIT,
	
}MSPI_SRBits_t;

// typedef enum
// {
    // MSPI_INT_TXE ,
    // MSPI_INT_RXNE,
    // MSPI_INT_ERR ,
	
// } MSPI_INT_SRC_t;


#define SPI_MAX_NUM    						3







#endif