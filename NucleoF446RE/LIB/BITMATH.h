/******************************************************************************
 ******************************************************************************
 * @file           : BITMATH.h
 * @author         : Abdalrahman Amin
 * @brief          : library
 ****************************************************************************
 ******************************************************************************/
#ifndef BITMATH_H_
#define BITMATH_H_

#include <stdint.h>

#define SETBIT(x,y) (x|=(1<<y))
#define CLRBIT(x,y) (x&=~(1<<y))
#define TOGBIT(x,y) (x^=(1<<y))
#define READBIT(x,y) ((x>>y)&1)
#define GET_BIT(x,y) ((x>>y)&1)

#endif
