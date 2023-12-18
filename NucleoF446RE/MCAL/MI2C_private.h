/* **************************************************** */
/* Author      	:	 Abdalrahman Amin					*/
/* SWC         	:	 I2C								*/
/* MCu         	:	 Stm32F446RE						*/
/* Layer       	:	 MCAL              					*/
/* Version     	:	 1.1               					*/
/* Date        	:	 November 29, 2023					*/
/* Last Edit   	:	 December 3,2023					*/
/* **************************************************** */

#ifndef M_I2C_PRIVATE_H_
#define M_I2C_PRIVATE_H_


#define MI2C1_BASE_ADDRESS ((volatile u32 *)0x40005400)
#define MI2C2_BASE_ADDRESS ((volatile u32 *)0x40005800)
#define MI2C3_BASE_ADDRESS ((volatile u32 *)0x40005C00)


typedef struct 
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 OAR1;
	volatile u32 OAR2;
	volatile u32 DR;
	volatile u32 SR1;
	volatile u32 SR2;
	volatile u32 CCR;
	volatile u32 TRISE;
	volatile u32 FLTR;
}MI2C_REGDEF_t;

#define I2C1 						(( MI2C_REGDEF_t *)MI2C1_BASE_ADDRESS)
#define I2C2 						(( MI2C_REGDEF_t *)MI2C2_BASE_ADDRESS)
#define I2C3 						(( MI2C_REGDEF_t *)MI2C3_BASE_ADDRESS)



/********************** Private defines ************************/

/*Control Register 1 Bits*/
#define MI2C_CR1_PE                 0
#define MI2C_CR1_SMBUS              1
#define MI2C_CR1_SMBTYPE            3
#define MI2C_CR1_ENARP              4
#define MI2C_CR1_ENPEC              5
#define MI2C_CR1_ENGC               6
#define MI2C_CR1_NOSTRETCH          7
#define MI2C_CR1_START              8
#define MI2C_CR1_STOP               9
#define MI2C_CR1_ACK                10
#define MI2C_CR1_POS                11
#define MI2C_CR1_PEC                12
#define MI2C_CR1_ALERT              13
#define MI2C_CR1_SWRST              15


/*Control Register 2 Bits*/
#define MI2C_CR2_FREQ0              0
#define MI2C_CR2_FREQ5              5
#define MI2C_CR2_ITERREN            8
#define MI2C_CR2_ITEVTEN            9
#define MI2C_CR2_ITBUFEN            10
#define MI2C_CR2_DMAEN              11
#define MI2C_CR2_LAST               12

/*Own Address Register 1 Bits*/
#define MI2C_OAR1_ADD0              0
#define MI2C_OAR1_ADD1              1
#define MI2C_OAR1_ADD7              7
#define MI2C_OAR1_ADD8              8
#define MI2C_OAR1_ADD9              9
#define MI2C_OAR1_ADDMODE           15

/*Own Address Register 2 Bits*/
#define MI2C_OAR2_ENDUAL            0
#define MI2C_OAR2_ADD20             1
#define MI2C_OAR2_ADD27             7

/*Status Register 1 Bits*/
#define MI2C_SR1_SB                 0
#define MI2C_SR1_ADDR               1
#define MI2C_SR1_BTF                2
#define MI2C_SR1_ADD10              3
#define MI2C_SR1_STOPF              4
#define MI2C_SR1_RxNE               6
#define MI2C_SR1_TxE                7
#define MI2C_SR1_BERR               8
#define MI2C_SR1_ARLO               9
#define MI2C_SR1_AF                 10
#define MI2C_SR1_OVR                11
#define MI2C_SR1_PECERR             12
#define MI2C_SR1_TIMEOUT            14
#define MI2C_SR1_SMBALERT           15

/*Status Register 2 Bits*/
#define MI2C_SR2_MSL                0
#define MI2C_SR2_BUSY               1
#define MI2C_SR2_TRA                2
#define MI2C_SR2_GENCALL            4
#define MI2C_SR2_SMBDEFAULT         5
#define MI2C_SR2_SMBHOST            6
#define MI2C_SR2_DUALF              7
#define MI2C_SR2_PEC0               8
#define MI2C_SR2_PEC7               15

/*Clock Control Register Bits*/
#define MI2C_CCR_CCR0               0
#define MI2C_CCR_CCR11              11
#define MI2C_CCR_DUTY               14
#define MI2C_CCR_FS                 15

/*Rise Time Register Bits*/
#define MI2C_TRISE_TRISE0           0
#define MI2C_TRISE_TRISE5           5

/* Enables */
#define MI2C_ENABLE					1
#define MI2C_DISABLE				0



/*  APB1 Freq */
#define APB1_FREQUENCY				8u


#define START_BIT                   8u
#define STOP_BIT                    9u
#define TXE_BIT                     7u
#define RXE_BIT                     6u
#define POS_BIT                     11u
#define BTF_BIT                     2u
#define OAR1_MASK                   0x00004000u
#define OAR1_7BIT_ADDRESS_ACCESS    1u
#define SPEED_MOOD_ACCESS   15u
#define CCR_MASK                    0x0000u
#define CR2_MASK                    0x0000u
#define CR1_MASK                    0x0000u
#define DMA_BIT                     11u
#define LAST_BIT                    12u
#define ITBUFF_BIT                  10u
#define ACK_BIT                     10u
#define TRISE_MASK                  0x0000
#define SM_CCR_MUL                  5u
#define FM_CCR_MUL                  125u
#define FM_CCR_DIV                  100u
#define FM_TRISE_MUL                3u
#define FM_TRISE_DIV                10u
#define TRISE_KEY                   1u
#define ENABLE                      1u
#define ADDR_ACCESS                 1u
#define R_W_ACCESS                  1u
#define TIME_OUT                    640000u
#define RECEIVE_2BYTES              2u
#define LAST_3BYTES                 2u


#endif
