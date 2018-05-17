/*******************************************************************************
 * -----------------------------------------------------------------------------
 * elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com    * 	     					  
 * -----------------------------------------------------------------------------
 *
 *  File Name   :  GestureTypes.H
 *
 *  Description :  Type definitions for STM32
 *  
 *  Compiler    :  IAR Workbench / coocox IDE 			
 *
 * -----------------------------------------------------------------------------
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017 
 ******************************************************************************/

#ifndef __TYPEDEF_H_
#define __TYPEDEF_H_

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
typedef unsigned char 		bool;  //Range -128 to 127
typedef signed char 		S8_t;  //Range -128 to 127
typedef unsigned char 		U8_t;  //Range 0 to 255
typedef	signed int 			S16_t; //Range -32768 to 32767
typedef	unsigned int 		U16_t; //Range 0 to 65535
typedef	signed long int 	S32_t; //Range -2147483648 to 2147483647
typedef	unsigned long int 	U32_t; //Range 0 to 4294967295
typedef float			F24_t; //Range Real Numbers
typedef double			D32_t; //Range Real Numbers

typedef _Bool 			B1;  //Bool--8 Bit Range 0 or 1
typedef signed char 		S8;  //signed numbers--1 Byte   Range -127 to +127
typedef unsigned char 		U8;  //unsigned numbers--1 Byte Range 0 to 255
typedef signed int 			S16; //signed numbers--2 Byte   Range -32.768 to +32.767
typedef unsigned int 		U16; //signed numbers--2 Byte   Range 0 to +65535
typedef signed long 		S32; //signed numbers--4 Byte   Range -2.147.483.648 to +2.147.483.647
typedef unsigned long 		U32; //signed numbers--4 Byte   Range 0 to +4.294.967.2

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define DEBUGPRINT 0

#define false 0
#define true 1

#define success 1
#define fail    0
/* Exported functions ------------------------------------------------------- */

#endif /* __TYPEDEF_H_  */


/******************* https://elektronikaembedded.wordpress.com *****END OF FILE****/

