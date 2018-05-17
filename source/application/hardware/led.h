/*******************************************************************************
 * ----------------------------------------------------------------------------*
 *  elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com   *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : led.h                                                          *
 *                                                                             *
 * Description : led.c header file                                             *
 *                                                                             *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

/* Includes ------------------------------------------------------------------*/
//#include "led.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define TOP_LED   	GPIO_Pin_12 //D1
#define BOTTOM_LED 	GPIO_Pin_15 //D4

#define RIGHT_LED 	GPIO_Pin_13 //D3
#define LEFT_LED 	GPIO_Pin_14 //D2

#define TOP_LED_GPIO    GPIOB
#define BOTTOM_LED_GPIO GPIOB
#define RIGHT_LED_GPIO  GPIOB
#define LEFT_LED_GPIO   GPIOB
#define D1_D3_LED_CLOCK  RCC_APB2Periph_GPIOB

#define MAIN_LED        GPIO_Pin_13
#define MAIN_LED_GPIO   GPIOC
#define MAIN_LED_CLOCK  RCC_APB2Periph_GPIOC


#define LED_ON 		0
#define LED_OFF 	1
#define LED_BLINK 	2

#define Initial_Count 3

/* Exported functions ------------------------------------------------------- */

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledInit
 *
 * Description   : Initialize System Leds(LED Port,Direction,Initial State)
 *
 * Input : None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledInit(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledSetMain
 *
 * Description   : Led State (ON,OFF,Blink)
 *
 * Input : LED_ON (0),LED_OFF (1),LED_BLINK (2)
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledSetMainLed(uint8_t u8val);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledSetTopLed
 *
 * Description   : Led State (ON,OFF,Blink)
 *
 * Input : LED_ON (0),LED_OFF (1),LED_BLINK (2)
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledSetTopLed(uint8_t u8val);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledSetBottomLed
 *
 * Description   : Led State (ON,OFF,Blink)
 *
 * Input : LED_ON (0),LED_OFF (1),LED_BLINK (2)
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledSetBottomLed(uint8_t u8val);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledSetRightLed
 *
 * Description   : Led State (ON,OFF,Blink)
 *
 * Input : LED_ON (0),LED_OFF (1),LED_BLINK (2)
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledSetRightLed(uint8_t u8val);


/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledSetLeftLed
 *
 * Description   : Led State (ON,OFF,Blink)
 *
 * Input : LED_ON (0),LED_OFF (1),LED_BLINK (2)
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors : Sarath S
 * Date : May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledSetLeftLed(uint8_t u8val);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledBlinkHandler
 *
 * Description   :ledBlinkHandler 1ns interrupt (Call Form void SysTickHandler(void) stm32fx_it.c file)
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledBlinkHandler(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : ledBlinkDemo
 *
 * Description   : This is a Simple Led On off Blink Demo
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void ledBlinkDemo(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureLeft
 *
 * Description   : while moving to Left side Top,Bottom Leds ON,Left Led Blink 4 times Right Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/

void GestureLeft(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureRight
 *
 * Description   : while moving to Right side Top,Bottom Leds ON,Left Right Blink 4 times Left Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void GestureRight(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureDown
 *
 * Description   : while moving to Down side Left,Right Leds ON,Bottom Led Blink 4 times Top Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void GestureDown(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureUp
 *
 * Description   : while moving to Up side Left,Right Leds ON,Top Led Blink 4 times Bottom Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void GestureUp(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureFar
 *
 * Description   : while moving to Up side Left,Right Leds ON,Top Led Blink 4 times Bottom Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void GestureFar(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : GestureNear
 *
 * Description   : while moving to Up side Left,Right Leds ON,Top Led Blink 4 times Bottom Led OFF
 *
 * Input: None
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void GestureNear(void);


/* ----------------------------------------------------------------------------*
 *
 * Function Name : reportLed
 *
 * Description   : Reporting Gesture to Led Pattern
 *
 * Input: gesture_t Gesture type
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/

void reportLed(int gesture_t);

#endif /* __LED_H */

/******* https://elektronikaembedded.wordpress.com  *****END OF FILE***********/
