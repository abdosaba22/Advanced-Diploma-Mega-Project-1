/* ******************************************************** */
/* Author      	:	 Abdalrahman Amin						*/
/* SWC         	:	 RCC									*/
/* Layer       	:	 MCAL              						*/
/* MCu     		:	 stm32f103C8T6    						*/
/* Version     	:	 1.0               						*/
/* Date        	:	 July 1, 2023							*/
/* Last Edit   	:	 N/A 									*/
/* ******************************************************** */

#ifndef RCC_Private_H_
#define RCC_Private_H_

#define RCC_BASE_ADDRESS        		0x40021000U

/******************* RCC Register Definition Structure **************/

typedef struct
{
    volatile uint32_t CR;          /*!< RCC clock control register,                                        Address offset: 0x00 */
    volatile uint32_t CFGR;        /*!< RCC clock configuration register,                                  Address offset: 0x04 */
    volatile uint32_t CIR;         /*!< RCC clock interrupt register,                                      Address offset: 0x08 */
    volatile uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                Address offset: 0x0C */
    volatile uint32_t APB1RSTR;    /*!< RCC APB1 peripheral reset register,                                Address offset: 0x10 */
    volatile uint32_t AHBENR;      /*!< RCC AHB peripheral clock enable register,                          Address offset: 0x14 */
    volatile uint32_t APB2ENR;     /*!< RCC APB2 peripheral clock enable register,                          Address offset: 0x18 */
    volatile uint32_t APB1ENR;     /*!< RCC APB1 peripheral clock enable register,                          Address offset: 0x1C */
    volatile uint32_t BDCR;        /*!< RCC Backup domain control register,                                 Address offset: 0x20 */
    volatile uint32_t CSR;         /*!< RCC clock control & status register,                                Address offset: 0x24 */
} RCC_RegDef_t;

/******************* RCC Peripheral Definition **************/
#define RCC   			            	((RCC_RegDef_t*)RCC_BASE_ADDRESS)


#define STARTUP_TIMEOUT  			5000 // val
#define RCC_CLEAR_TRIM_VAL 			0b11111 //
#define RCC_HSI_TRIM_DEFAULT 		0b10000 // 16
#define RCC_PLL_MUL_RESET  			0b1111//


#endif
