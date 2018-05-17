/*******************************************************************************
 * ----------------------------------------------------------------------------*
 * Copyright (C) elektronikaembedded@gamil.com  	       	               *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : main.c                                                         *
 *                                                                             *
 * Description : main program body                                             *
 *                                                                             *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "delay.h"
#include "apds9960.h"
#include "debug.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t u8ledstate;  /* Led States On (0),Off (1),Blink (2)*/

uint8_t u8mainled_state; /* Led States On (0),Off (1),Blink (2)*/
uint8_t u8mainled_time = 0; /* Led Blink Counter*/

uint8_t u8topled_state; /* Led States On (0),Off (1),Blink (2)*/
uint8_t u8topled_time = 0; /* Led Blink Counter*/

uint8_t u8bottomled_state; /* Led States On (0),Off (1),Blink (2)*/
uint8_t u8bottomled_time = 0; /* Led Blink Counter*/

uint8_t u8leftled_state; /* Led States On (0),Off (1),Blink (2)*/
uint8_t u8leftled_time = 0; /* Led Blink Counter*/

uint8_t u8rightled_state; /* Led States On (0),Off (1),Blink (2)*/
uint8_t u8rightled_time = 0; /* Led Blink Counter*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

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
void ledInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | D1_D3_LED_CLOCK | MAIN_LED_CLOCK, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

  GPIO_InitStructure.GPIO_Pin = TOP_LED;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(TOP_LED_GPIO, TOP_LED); /* Led State ON*/

  GPIO_InitStructure.GPIO_Pin = BOTTOM_LED;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(BOTTOM_LED_GPIO, BOTTOM_LED); /* Led State ON*/

  GPIO_InitStructure.GPIO_Pin = RIGHT_LED;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(RIGHT_LED_GPIO, RIGHT_LED); /* Led State ON*/

  GPIO_InitStructure.GPIO_Pin = LEFT_LED;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(LEFT_LED_GPIO, LEFT_LED); /* Led State ON*/
  
  GPIO_InitStructure.GPIO_Pin = MAIN_LED;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_ResetBits(MAIN_LED_GPIO, MAIN_LED); /* Led State ON*/

}/* End of this function */

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
void ledSetMainLed(uint8_t u8val)
{
  switch(u8val)
  {
    case 0:  //ON
      GPIO_ResetBits(MAIN_LED_GPIO,MAIN_LED);
      u8mainled_state = LED_OFF;
      break;

    case 1:  //OFF
      GPIO_SetBits(MAIN_LED_GPIO,MAIN_LED);
      u8mainled_state = LED_ON;
      break;
    case 2:  //Blink;
    u8mainled_state = LED_BLINK;
      break;
    default:
      break;
  }
}/* End of this function */


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
void ledSetTopLed(uint8_t u8val)
{
  switch(u8val)
  {
    case 0:  //ON
      GPIO_ResetBits(TOP_LED_GPIO,TOP_LED);
      u8topled_state = LED_OFF;
      break;

    case 1:  //OFF
      GPIO_SetBits(TOP_LED_GPIO,TOP_LED);
      u8topled_state = LED_ON;
      break;
    case 2:  //Blink;
    u8topled_state = LED_BLINK;
      break;
    default:
      break;
  }
}/* End of this function */

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
void ledSetBottomLed(uint8_t u8val)
{
  switch(u8val)
  {
    case 0:  //ON
      GPIO_ResetBits(BOTTOM_LED_GPIO,BOTTOM_LED);
      u8bottomled_state = LED_OFF;
      break;

    case 1:  //OFF
      GPIO_SetBits(BOTTOM_LED_GPIO,BOTTOM_LED);
      u8bottomled_state = LED_ON;
      break;
    case 2:  //Blink;
    u8bottomled_state = LED_BLINK;
      break;
    default:
      break;
  }
}/* End of this function */

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
void ledSetRightLed(uint8_t u8val)
{
  switch(u8val)
  {
    case 0:  //ON
      GPIO_ResetBits(RIGHT_LED_GPIO,RIGHT_LED);
      u8rightled_state = LED_OFF;
      break;

    case 1:  //OFF
      GPIO_SetBits(RIGHT_LED_GPIO,RIGHT_LED);
      u8rightled_state = LED_ON;
      break;
    case 2:  //Blink;
    u8rightled_state = LED_BLINK;
      break;
    default:
      break;
  }
}/* End of this function */

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
void ledSetLeftLed(uint8_t u8val)
{
  switch(u8val)
  {
    case 0:  //ON
      GPIO_ResetBits(LEFT_LED_GPIO,LEFT_LED);
      u8leftled_state = LED_OFF;
      break;

    case 1:  //OFF
      GPIO_SetBits(LEFT_LED_GPIO,LEFT_LED);
      u8leftled_state = LED_ON;
      break;
    case 2:  //Blink;
    u8leftled_state = LED_BLINK;
      break;
    default:
      break;
  }
}/* End of this function */


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
void ledBlinkHandler(void)
{
  	if(u8mainled_state == LED_BLINK) /*Main Led Handiler Starts*/
	{
		u8mainled_time++;
		if(u8mainled_time > 100)
		{
			GPIO_ResetBits(MAIN_LED_GPIO,MAIN_LED);
		}else
		{
			GPIO_SetBits(MAIN_LED_GPIO,MAIN_LED);
		}
		if(u8mainled_time > 200)
		{
			u8mainled_time = 0;
		}
	} /* Main Led Handiler End*/
	if(u8topled_state == LED_BLINK)/* Top Led Handiler Starts*/
	{
		u8topled_time++;
		if(u8topled_time > 50)
		{
			GPIO_ResetBits(TOP_LED_GPIO,TOP_LED);
		}else
		{
			GPIO_SetBits(TOP_LED_GPIO,TOP_LED);
		}
		if(u8topled_time > 100)
		{
			u8topled_time = 0;
		}
	}/* Top Led Handiler End*/

	if(u8bottomled_state == LED_BLINK)/* Bottom Led Handiler Starts */
	{
		u8bottomled_time++;
		if(u8bottomled_time > 50)
		{
			GPIO_ResetBits(BOTTOM_LED_GPIO,BOTTOM_LED);
		}else
		{
			GPIO_SetBits(BOTTOM_LED_GPIO,BOTTOM_LED);
		}
		if(u8bottomled_time > 100)
		{
			u8bottomled_time = 0;
		}
	}/* Bottom Led Handiler End*/
	if(u8rightled_state == LED_BLINK)/* Right Led Handiler Starts*/
	{
		u8rightled_time++;
		if(u8rightled_time > 50)
		{
			GPIO_ResetBits(RIGHT_LED_GPIO,RIGHT_LED);
		}else
		{
			GPIO_SetBits(RIGHT_LED_GPIO,RIGHT_LED);
		}
		if(u8rightled_time > 100)
		{
			u8rightled_time = 0;
		}
	}/* Right Led Handiler Ends*/
	if(u8leftled_state == LED_BLINK)/* Left Led Handiler Starts*/
	{
		u8leftled_time++;
		if(u8leftled_time > 50)
		{
			GPIO_ResetBits(RIGHT_LED_GPIO,LEFT_LED);
		}else
		{
			GPIO_SetBits(RIGHT_LED_GPIO,LEFT_LED);
		}
		if(u8leftled_time > 100)
		{
			u8leftled_time = 0;
		}
	}/* Left Led Handiler Ends*/

}/* End of this function */

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

void ledBlinkDemo(void)
{
  unsigned char u8Index = 0;
  
  GPIO_ResetBits(TOP_LED_GPIO, TOP_LED);
  GPIO_ResetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
  GPIO_ResetBits(RIGHT_LED_GPIO, RIGHT_LED);
  GPIO_ResetBits(LEFT_LED_GPIO, LEFT_LED);
  delayms(1000);
  GPIO_SetBits(TOP_LED_GPIO, TOP_LED);
  GPIO_SetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
  GPIO_SetBits(RIGHT_LED_GPIO, RIGHT_LED);
  GPIO_SetBits(LEFT_LED_GPIO, LEFT_LED);
  delayms(1000);
  while(u8Index < Initial_Count)
  {
    GPIO_ResetBits(TOP_LED_GPIO, TOP_LED);
    delayms(100);
    GPIO_ResetBits(RIGHT_LED_GPIO, RIGHT_LED);
    delayms(100);
    GPIO_ResetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
    delayms(100);
    GPIO_ResetBits(LEFT_LED_GPIO, LEFT_LED);
    delayms(100);
    GPIO_SetBits(TOP_LED_GPIO, TOP_LED);
    delayms(100);
    GPIO_SetBits(RIGHT_LED_GPIO, RIGHT_LED);
    delayms(100);
    GPIO_SetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
    delayms(100);
    GPIO_SetBits(LEFT_LED_GPIO, LEFT_LED);
    delayms(100);
    u8Index++;
  }
  u8Index = 0;
  while(u8Index < Initial_Count)
  {
    GPIO_ResetBits(TOP_LED_GPIO, TOP_LED);
    delayms(100);
    GPIO_ResetBits(LEFT_LED_GPIO, LEFT_LED);
    delayms(100);
    GPIO_ResetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
    delayms(100);
    GPIO_ResetBits(RIGHT_LED_GPIO, RIGHT_LED);
    delayms(100);
    GPIO_SetBits(TOP_LED_GPIO, TOP_LED);
    delayms(100);
    GPIO_SetBits(LEFT_LED_GPIO, LEFT_LED);
    delayms(100);
    GPIO_SetBits(BOTTOM_LED_GPIO, BOTTOM_LED);
    delayms(100);
    GPIO_SetBits(RIGHT_LED_GPIO, RIGHT_LED);
    delayms(100);
    u8Index++;
  }
}/* End of this function */


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

void GestureLeft(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetTopLed(LED_ON);
    ledSetRightLed(LED_OFF);
    ledSetBottomLed(LED_ON);
    ledSetLeftLed(LED_ON);  /*Left Led On*/
    delayms(100);
    ledSetTopLed(LED_ON);
    ledSetRightLed(LED_OFF);
    ledSetBottomLed(LED_ON);
    ledSetLeftLed(LED_OFF); /*Left Led Off*/
    delayms(100);
  }
  ledSetTopLed(LED_OFF);
  ledSetRightLed(LED_OFF);
  ledSetBottomLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
}/* End of this function */

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
void GestureRight(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetTopLed(LED_ON);
    ledSetLeftLed(LED_OFF);
    ledSetBottomLed(LED_ON);
    ledSetRightLed(LED_ON);
    delayms(100);
    ledSetTopLed(LED_ON);
    ledSetLeftLed(LED_OFF);
    ledSetBottomLed(LED_ON);
    ledSetRightLed(LED_OFF);
    delayms(100);
  }
  ledSetTopLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
  ledSetBottomLed(LED_OFF);
  ledSetRightLed(LED_OFF);
}/* End of this function */

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
void GestureDown(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetTopLed(LED_OFF);
    ledSetRightLed(LED_ON);
    ledSetLeftLed(LED_ON);
    ledSetBottomLed(LED_ON);
    delayms(100);
    ledSetTopLed(LED_OFF);
    ledSetRightLed(LED_ON);
    ledSetLeftLed(LED_ON);
    ledSetBottomLed(LED_OFF);
    delayms(100);
  }
  ledSetTopLed(LED_OFF);
  ledSetRightLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
  ledSetBottomLed(LED_OFF);
}/* End of this function */

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
void GestureUp(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetTopLed(LED_ON);
    ledSetBottomLed(LED_OFF);
    ledSetRightLed(LED_ON);
    ledSetLeftLed(LED_ON);
    delayms(100);
    ledSetTopLed(LED_OFF);
    ledSetBottomLed(LED_OFF);
    ledSetRightLed(LED_ON);
    ledSetLeftLed(LED_ON);
    delayms(100);
  }
  ledSetTopLed(LED_OFF);
  ledSetRightLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
  ledSetBottomLed(LED_OFF);
}/* End of this function */
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
void GestureFar(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetTopLed(LED_ON);
    ledSetRightLed(LED_ON);
    ledSetLeftLed(LED_OFF);
    ledSetBottomLed(LED_OFF);
    delayms(100);
    ledSetTopLed(LED_OFF);
    ledSetRightLed(LED_OFF);
    ledSetLeftLed(LED_OFF);
    ledSetBottomLed(LED_OFF);
    delayms(100);
  }
  ledSetBottomLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
  ledSetTopLed(LED_OFF);
  ledSetRightLed(LED_OFF);
}/* End of this function */
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
void GestureNear(void)
{
  unsigned char u8Index;
  for(u8Index=0;u8Index<4;u8Index++)
  {
    ledSetBottomLed(LED_ON);
    ledSetLeftLed(LED_ON);
    ledSetTopLed(LED_OFF);
    ledSetRightLed(LED_OFF);
    delayms(100);
    ledSetBottomLed(LED_OFF);
    ledSetLeftLed(LED_OFF);
    ledSetTopLed(LED_OFF);
    ledSetRightLed(LED_OFF);
    delayms(100);
  }
  ledSetBottomLed(LED_OFF);
  ledSetLeftLed(LED_OFF);
  ledSetTopLed(LED_OFF);
  ledSetRightLed(LED_OFF);
}/* End of this function */





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




void reportLed(int gesture_t)
{
  switch (gesture_t) {
      case DIR_UP:
        GestureUp();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Up....!\r\n");
        #endif
        break;
      case DIR_DOWN:
        GestureDown();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Down....!\r\n");
        #endif
        break;
      case DIR_LEFT:
        GestureLeft();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Left....!\r\n");
        #endif
        break;
      case DIR_RIGHT:
        GestureRight();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Right....!\r\n");
        #endif
        break;
      case DIR_NEAR:
        GestureNear();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Near....!\r\n");
        #endif
        break;
      case DIR_FAR:
        GestureFar();
        #ifdef DEBUGPRINT
        debugPutString("Gesture Far....!\r\n");
        #endif
        break;
      //default:
        //debugPutString("NONE\r\n");
    }

}/* End of this function */

/*******************************************************************************
			* End of file															     *
*******************************************************************************/


