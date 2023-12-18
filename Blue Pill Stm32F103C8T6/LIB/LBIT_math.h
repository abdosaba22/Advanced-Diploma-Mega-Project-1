/* ************************************************ */
/* Author      : Abd-alrahman Amin                  */
/* SWC         : BIT Math                           */
/* Layer       : LIB                                */
/* Version     : 1.1                                */
/* Date        : August 2, 2023                     */
/* Last Edit   : August 3, 2023                     */
/* ************************************************ */

#ifndef _LBIT_MATH_H_		
#define _LBIT_MATH_H_


#define GET_BIT(REG,BIT)  		 ( (REG>>BIT) & 1 )
#define SET_BIT(REG,BIT)  		 ( REG|= ( 1<<BIT ) )
#define CLEAR_BIT(REG,BIT) 		 ( REG&=~( 1<<BIT ) )
#define CLR_BIT(REG,BIT) 		 ( REG&=~( 1<<BIT ) )
#define TOGGLE_BIT(REG,BIT) 	 ( REG^= ( 1<<BIT ) )

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))

#endif
