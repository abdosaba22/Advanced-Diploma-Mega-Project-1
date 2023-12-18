/* ************************************************ */
/* Author      : 	Abdalrahman Amin                */
/* SWC         : 	Reset & Clock Control	        */
/* MCu         : 	Stm32F446RE		                */
/* Layer       : 	MCAL                            */
/* Version     : 	1.0                             */
/* Date        : 	September 12, 2023              */
/* Last Edit   : 	N/A			                    */
/* ************************************************ */

#ifndef _MRCC_PRIVATE_H_
#define _MRCC_PRIVATE_H_

/************************ BASE ADDRESS RCC **********************/

#define MRCC_BASE_ADDRESS  			(0x40023800UL)
/***************************************************************/

/******************* RCC Register Definition Structure **************/

typedef struct
{
  volatile u32 CR;            /*!< RCC clock control register,                                   */
  volatile u32 PLLCFGR;       /*!< RCC PLL configuration register,                               */
  volatile u32 CFGR;          /*!< RCC clock configuration register,                             */
  volatile u32 CIR;           /*!< RCC clock interrupt register,                                 */
  volatile u32 AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                           */
  volatile u32 AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                           */
  u32      RESERVED0[2];  		/*!< Reserved, 0x18-0x1C                                         */
  volatile u32 APB1RSTR;      /*!< RCC APB1 peripheral reset register,                           */
  volatile u32 APB2RSTR;      /*!< RCC APB2 peripheral reset register,                           */
  u32      RESERVED1[2];  		/*!< Reserved, 0x28-0x2C                                         */
  volatile u32 AHBENR[2];       /*!< RCC arr for AHB1 , AHB2 peripheral clock register,          */
  /*volatile u32 AHB2ENR; */      /*!< RCC AHB2 peripheral clock register,                       */
  u32      RESERVED2[2];  		/*!< Reserved, 0x38-0x3C                                         */
  volatile u32 APBENR[2];       /*!< RCC arr for APB1 , APB2 peripheral clock enable register,   */
  /*volatile u32 APB2ENR; */      /*!< RCC APB2 peripheral clock enable register,                  */
  u32      RESERVED3[2];  		/*!< Reserved, 0x48-0x4C                                         */
  volatile u32 AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register,  */
  volatile u32 AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register,  */
  u32      RESERVED4[2];  		/*!< Reserved, 0x58-0x5C                                         */
  volatile u32 APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register,  */
  volatile u32 APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register,  */
  u32      RESERVED5[2];  		/*!< Reserved, 0x68-0x6C                                         */
  volatile u32 BDCR;          /*!< RCC Backup domain control register,                           */
  volatile u32 CSR;           /*!< RCC clock control & status register,                          */
  u32      RESERVED6[2];  		/*!< Reserved, 0x78-0x7C                                         */
  volatile u32 SSCGR;         /*!< RCC spread spectrum clock generation register,                */
  volatile u32 PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                            */
  u32	   RESERVED7;    		/*!< Reserved, 0x88					                             */
  volatile u32 DCKCFGR;       /*!< RCC Dedicated Clocks configuration register,                  */
} MRCC_RegDef_T;

/******************* RCC Peripheral Definition **************/
#define MRCC 				 ((MRCC_RegDef_T*) MRCC_BASE_ADDRESS)
/**************************************************************/

/******************************** REGs BITs ***************************************/

/**************************** RCC_CR bits **************************************/
typedef enum {
	RCC_CR_HSION = 0,
	RCC_CR_HSIRDY,
	RCC_CR_HSITRIM_0=3,
	RCC_CR_HSICAL_0=8,
	RCC_CR_HSEON = 16,
	RCC_CR_HSERDY,
	RCC_CR_HSEBYP,
	RCC_CR_CSSON,
	RCC_CR_PLLON = 24,
	RCC_CR_PLLRDY,
	RCC_CR_PLLI2SON,
	RCC_CR_PLLI2SRDY,
	RCC_CR_PLLSAION,
	RCC_CR_PLLSAIRDY
}EN_RCC_CR_BITS;
/**************************************************************************/

/**************************** RCC_CFGR bits **************************************/
#define RCC_CFGR_SW_0			 		0u
#define RCC_CFGR_SWS_0 					2u
#define RCC_CFGR_HPRE_0  				4u
#define RCC_CFGR_PPRE1_0 		 		10u
#define RCC_CFGR_PPRE2_0 		 		13u
#define RCC_CFGR_RTCPRE_0 		 		16u
#define RCC_CFGR_MCO1_0 		 		21u
#define RCC_CFGR_MCO1PRE_0 		 		24u
#define RCC_CFGR_MCO2PRE_0 		 		27u
#define RCC_CFGR_MCO2_0 				30u
/**************************************************************************/

/**************************** RCC_PLLCFGR bits **************************************/
#define RCC_PLLCFGR_PLLM_0				0u
#define RCC_PLLCFGR_PLLN_0				6u
#define RCC_PLLCFGR_PLLP_0				16u
#define RCC_PLLCFGR_PLLSRC				22u
#define RCC_PLLCFGR_PLLQ_0				24u
#define RCC_PLLCFGR_PLLR_0				28u
/**************************************************************************/

/************************** Needed MAsk macros **************************/
#define RCC_CFGR_SW_MASK 				(0x3U << RCC_CFGR_SW_0)				// << 0
#define RCC_CFGR_MCO1_MASK 				(0x3U << RCC_CFGR_MCO1_0)			// << 21
#define RCC_CFGR_MCO1PRE_MASK 			(0x7U << RCC_CFGR_MCO1PRE_0)		// << 24


#define RCC_PLLCFGR_PLLM_MASK  			(0x3FU << RCC_PLLCFGR_PLLM_0) 		// << 0
#define RCC_PLLCFGR_PLLN_MASK  			(0x1FFU << RCC_PLLCFGR_PLLN_0) 		// << 6
#define RCC_PLLCFGR_PLLP_MASK  			(0x03U << RCC_PLLCFGR_PLLP_0)		// << 16


#define RCC_PERIPHERAL_BIT_MASK			0x1FU
#define RCC_PERIPHERAL_REG_MASK			0x3U
#define RCC_PERIPHERAL_MAX				128U


#endif
