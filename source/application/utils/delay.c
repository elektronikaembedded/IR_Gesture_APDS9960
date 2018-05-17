/*******************************************************************************
 * ----------------------------------------------------------------------------*
 * Copyright (C) elektronikaembedded@gamil.com  	       	               *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : delay.c                                                        *
 *                                                                             *
 * Description : delay program body                                            *
 *                                                                             *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "misc.h"
#include "delay.h"
#include "typedef.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/* ----------------------------------------------------------------------------*
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
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void delayInit(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB1PeriphClockCmd(DELAY_TIMER_RCC, ENABLE);
  
  TIM_TimeBaseStructure.TIM_Period = DELAY_PERIODE;
  TIM_TimeBaseStructure.TIM_Prescaler = DELAY_PRESCALER;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(DELAY_TIMER, &TIM_TimeBaseStructure);
  TIM_Cmd(DELAY_TIMER, ENABLE);

}/* End of this function */

/* ----------------------------------------------------------------------------*
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
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void delayms(uint16_t u16delay)
{
  u16delay = u16delay & 0x7FFF;
  u16delay *= 2;
  TIM_SetCounter(DELAY_TIMER, 0);
  while(TIM_GetCounter(DELAY_TIMER) < u16delay);
}/* End of this function */


/* ----------------------------------------------------------------------------*
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
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void delayStartTimeout(void)
{
  TIM_SetCounter(DELAY_TIMER, 0);
}/* End of this function */


/* ----------------------------------------------------------------------------*
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
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
uint8_t delayCheckTimeout(uint16_t u16timeout)
{
  if(TIM_GetCounter(DELAY_TIMER) < u16timeout)
  {
    return 1; //Timeout
  }
  return 0; //No Timeout
}/* End of this function */



/*******************************************************************************
			* End of file															     *
*******************************************************************************/
