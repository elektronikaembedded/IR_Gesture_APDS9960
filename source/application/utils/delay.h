/****************************************************************************** *
 * ---------------------------------------------------------------------------- *
 * Copyright (C) elektronikaembedded@gamil.com  	       	                *
 * ---------------------------------------------------------------------------- *
 *                                                                              *
 * File Name  : delay.h                                                         *
 *                                                                              *
 * Description : delay header file                                              *
 *                                                                              *
 * Version     : PrototypeV1.0                                                  *
 *                                                                              *
 * ---------------------------------------------------------------------------  *
 * Authors: Sarath S                                                            *
 * Date: May 16, 2017                                                           *
 ********************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

/* Includes ------------------------------------------------------------------*/
//#include "delay.h"
#include "typedef.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define DELAY_TIMER TIM4
#define DELAY_TIMER_RCC RCC_APB1Periph_TIM4
#define DELAY_PERIODE 65535
#define DELAY_PRESCALER 36000

/* Exported functions ------------------------------------------------------- */


/* -----------------------------------------------------------------------------*
 *
 * 	Function Name : delayInit
 *
 * 	Description   :	initialization Of System Delay Using Timer
 *
 * 	Input	: None
 *
 *	Output  : None
 *
 *	Return  : None
 * -----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * -----------------------------------------------------------------------------*/
void delayInit(void);

/* -----------------------------------------------------------------------------*
 *
 * 	Function Name : delayms
 *
 * 	Description   :	delayms Hardware delay in milli second
 *
 * 	Input	: u16delay
 *
 *	Output  : None
 *
 *	Return  : None
 * -----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * -----------------------------------------------------------------------------*/
void delayms(uint16_t u16delay);


/* -----------------------------------------------------------------------------*
 *
 * 	Function Name : delayStartTimeout
 *
 * 	Description   :	delayStartTimeout Start Time Out
 *
 * 	Input	: None
 *
 *	Output  : None
 *
 *	Return  : None
 * -----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * -----------------------------------------------------------------------------*/
void delayStartTimeout(void);

/* -----------------------------------------------------------------------------*
 *
 * 	Function Name : delayCheckTimeout
 *
 * 	Description   :	delayCheckTimeout( checking Timeout )
 *
 * 	Input	: None
 *
 *	Output  : None
 *
 *	Return  : None
 * -----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * -----------------------------------------------------------------------------*/
U8_t delayCheckTimeout(uint16_t u16timeout);



#endif /* __DELAY_H */

/******* https://elektronikaembedded.wordpress.com  *****END OF FILE***********/
