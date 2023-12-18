#ifndef STM32F103XX_H
#define STM32F103XX_H

#include <stdint.h>

/********************* Various Memories Base Addresses ****************/

#define FLASH_BASE_ADDRESS      	0x08000000UL
#define SRAM_BASE_ADDRESS       	0x20000000UL


/********************* Core peripheral Base Addresses *****************/ 
 
#define SYSTICK_BASE_ADDRESS		0xE000E010U
 
#define NVIC_BASE_ADDRESS  			0xE000E100

#define SCB_BASE_ADDRESS			0xE000ED00U
/********************* AHB Peripheral Base Addresses ****************/

#define GPIOA_BASE_ADDRESS      		0x40010800U
#define GPIOB_BASE_ADDRESS      		0x40010C00U
#define GPIOC_BASE_ADDRESS      		0x40011000U
#define GPIOD_BASE_ADDRESS      		0x40011400U
#define GPIOE_BASE_ADDRESS      		0x40011800U
#define GPIOF_BASE_ADDRESS      		0x40011C00U
#define GPIOG_BASE_ADDRESS      		0x40012000U

#define AFIO_BASE_ADDRESS  	 			0x40010000U

#define RCC_BASE_ADDRESS        		0x40021000U

/********************* APB1 Peripheral Base Addresses ****************/
#define USART2_BASE_ADDRESS       		0x40004400UL
#define USART3_BASE_ADDRESS       		0x40004800UL
#define USART4_BASE_ADDRESS        		0x40004C00UL
#define USART5_BASE_ADDRESS        		0x40005000UL



#define SPI2_BASE_ADDRESS 				0x40003800
/********************* APB2 Peripheral Base Addresses ****************/
#define USART1_BASE_ADDRESS       	 	0x40013800UL

#define EXTI_BASE_ADDRESS   			0x40010400
#define SPI1_BASE_ADDRESS 				0x40013000

/******************* GPIO Register Definition Structure **************/

typedef struct
{
    volatile uint32_t  CRL;        /*!< GPIO port configuration register low,                   Address offset: 0x00 */
    volatile uint32_t  CRH;        /*!< GPIO port configuration register high,                  Address offset: 0x04 */
    volatile uint32_t  IDR;        /*!< GPIO port input data register,                          Address offset: 0x08 */
    volatile uint32_t  ODR;        /*!< GPIO port output data register,                         Address offset: 0x0C */
    volatile uint32_t  BSRR;       /*!< GPIO port bit set/reset register,                       Address offset: 0x10 */
    volatile uint32_t  BRR;        /*!< GPIO port bit reset register,                           Address offset: 0x14 */
    volatile uint32_t  LCKR;       /*!< GPIO port configuration lock register,                  Address offset: 0x18 */
} GPIO_RegDef_t;


/******************* AFIO Register Definition Structure **************/

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t MAPR2;
} AFIO_RegDef_t;


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


/*************** SYSTICK Register Definition Structure **********/
typedef struct {
	volatile uint32_t CSR;       /*!< SYSTICK Control and Status Register,                                   */
	volatile uint32_t RVR;       /*!< SYSTICK Reload Value Register,                               */
	volatile uint32_t CVR;       /*!< SYSTICK Current Value Register,                             */
	volatile uint32_t CALIB;     /*!< SYSTICK Calibration Value Register,                                 */	
} SYSTICK_RegDef_t;

/*************** NVIC Register Definition Structure **********/
typedef struct
{
  volatile uint32_t ISER[3]; //IRQ set-enable registers ID 0-80
  uint32_t   RESERVED0[29];
  volatile uint32_t ICER[3]; //IRQ clear-enable registers ID 0-80
  uint32_t   RESERVED1[29];
  volatile uint32_t ISPR[3]; //IRQ set-pending registers ID 0-80
  uint32_t   RESERVED2[29];
  volatile uint32_t ICPR[3]; //IRQ clear-pending registers ID 0-80
  uint32_t   RESERVED3[29];
  volatile uint32_t IABR[3]; //IRQ active bit registers ID 0-80
  uint32_t   RESERVED4[60];
  volatile uint8_t IPR[81]; //IRQ priority registers
}NVIC_RegDef_t;

/************************** SCB Register Definition Structure ***********************/

typedef struct
{
	volatile uint32_t CPUID;					/*CPUID base register*/
	volatile uint32_t ICSR;                  /*Interrupt control and state register*/
	volatile uint32_t VTOR;                  /*Vector table offset register*/
	volatile uint32_t AIRCR;                 /*Application interrupt and reset control register*/
	volatile uint32_t SCR;                   /*System control register*/
	volatile uint32_t CCR;                   /*Configuration and control register*/
	volatile uint32_t SHPR[3];               /*System handler priority registers*/
	volatile uint32_t SHCSR;                 /*System handler control and state register*/
	volatile uint32_t CFSR;                  /*Configurable fault status register*/
	volatile uint32_t HFSR;                  /*Hard fault status register*/
	volatile uint32_t Reserved;
	volatile uint32_t MMAR;                  /*Memory management fault address register*/
	volatile uint32_t BFAR;                  /*Bus fault status register*/
	volatile uint32_t AFSR;                  /*Auxiliary fault status register*/
}SCB_RegDef_t;


/*************** EXTI Register Definition Structure **********/
typedef struct
{
  volatile uint32_t IMR;
  volatile uint32_t EMR;
  volatile uint32_t RTSR;
  volatile uint32_t FTSR;
  volatile uint32_t SWIER;
  volatile uint32_t PR;
} EXTI_RegDef_t;

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
}USART_RegDef_t	;

/*************** SPI Register Definition Structure **********/
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t CRCPR;
  volatile uint32_t RXCRCR;
  volatile uint32_t TXCRCR;
  volatile uint32_t I2SCFGR;
  volatile uint32_t I2SPR;
} SPI_RegDef_t;

/******************* GPIO Peripheral Definition **************/

#define GPIOA               			((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB               			((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC               			((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD               			((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE               			((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF               			((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG               			((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)

#define GPIO_AFIO            			((AFIO_RegDef_t*)AFIO_BASE_ADDRESS)

/******************* RCC Peripheral Definition **************/

#define RCC   			            	((RCC_RegDef_t*)RCC_BASE_ADDRESS)
	
/******************* SYSTICK Peripheral Definition **************/

#define SYSTICK 						((SYSTICK_RegDef_t*) SYSTICK_BASE_ADDRESS)

/******************* EXTI Peripheral Definition **************/
#define EXTI        	     	 		((EXTI_RegDef_t *) EXTI_BASE_ADDRESS)

/******************* NVIC Peripheral Definition **************/
#define NVIC 			            	((NVIC_RegDef_t *) NVIC_BASE_ADDRESS)

/************************ SCB Peripheral Definition **********************/
#define SCB								((SCB_RegDef_t*) SCB_BASE_ADDRESS)

/******************  USART Peripheral Defination   **************/
#define UART1              			((USART_RegDef_t*)USART1_BASE_ADDRESS)
#define USART2              			((USART_RegDef_t*)USART2_BASE_ADDRESS)
#define USART3              			((USART_RegDef_t*)USART3_BASE_ADDRESS)
#define USART4              			((USART_RegDef_t*)USART4_BASE_ADDRESS)
#define USART5              			((USART_RegDef_t*)USART5_BASE_ADDRESS)
//#define USART6              			((USART_RegDef_t*)USART6_BASE_ADDRESS)

/******************  SPI Peripheral Defination   **************/

#define SPI_1    						((SPI_RegDef_t*)SPI1_BASE_ADDRESS)
#define SPI_2    						((SPI_RegDef_t*)SPI2_BASE_ADDRESS)



#endif 
