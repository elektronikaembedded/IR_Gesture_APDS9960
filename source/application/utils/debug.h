/*******************************************************************************
 * ----------------------------------------------------------------------------*
 *  elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com   *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : debug.h                                                        *
 *                                                                             *
 * Description : debug.c header file                                           *
 *                                                                             *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : debugInit
 *
 *  Description  :UART3 GPIO Pin Initialization
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void debugInit(void);


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : debugPutChar
 *
 *  Description : Sending Char to USART3 TX Line
 *
 *  Input : char (Data to be Send)
 *
 *  Output : None
 *
 * Return : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void debugPutChar(char data);

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : debugPutString
 *
 *  Description : Sending String to USART3 TX Line
 *
 *  Input : *char (String Data)
 *
 *  Output : None
 *
 * Return : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void debugPutString(char *data);




#endif /* __DEBUG_H */

/******* https://elektronikaembedded.wordpress.com  *****END OF FILE***********/
