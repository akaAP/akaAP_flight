 /*************************************
 * stm32_datatypes.h
 * author: stm
 * last modifications: 10.08.2009 1452
 * 
 * description: 
 **************************************/

#ifndef STM32_DATATYPES_H_
#define STM32_DATATYPES_H_

 /*Definitions******************************/
typedef unsigned char boolean;

typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

#define TRUE       1
#define FALSE	   0
#define ON  	   1
#define OFF		   0
#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)2147483648uL)
 /*Function Prototypes**********************/

#endif /* STM32_DATATYPES_H_ */
