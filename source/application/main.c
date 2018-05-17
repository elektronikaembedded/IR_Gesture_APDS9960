/***************************************************************************** *
 * ----------------------------------------------------------------------------*
 * elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com    *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : main.c                                                         *
 *                                                                             *
 * Description : main program body                                             *
 *                                                                             *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * Authors: Sarath S                                                           *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
/* System Files */

/* MCU Files */
#include "stm32f10x.h"
#include "stm32f10x_it.h"
/* User Files */
//Low Level
#include "led.h"
#include "delay.h"
#include "debug.h"
#include "apds9960.h"
#include "typedef.h"
//Application
volatile int Gesture_Flag;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int gesture = 0;
/* Private function prototypes -----------------------------------------------*/
void systemClockInit(void);

/* ----------------------------------------------------------------------------*
 *
 * Function Name : EXTI0_Config
 *
 * Description   : Configuring External Interrupt for Gesture INT Pin
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
void EXTI0_Config(void);
/* ----------------------------------------------------------------------------*
 *
 * Function Name : reportSerial
 *
 * Description   : Report to Serial (Debug Port)
 *
 * Input: Gesture
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void reportSerial(int8_t gesture_t);


/* Private functions ---------------------------------------------------------*/

void systemClockInit(void)
{
  SysTick_Config(SystemCoreClock / 1000);
}

 

/* ----------------------------------------------------------------------------*
 *
 * Function Name : main
 *
 * Description   : main block
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
int main()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  systemClockInit();            /* Initialize the System Clock */
  delayInit();                  /* System Delay Initialization */
  ledInit();                    /* System Led Initialization */
  debugInit();                  /* System Serial-Debug Initialization */
  ledBlinkDemo();               /* Play Led Demo Pattern*/
  debugPutString("\r\n +-------------------------------------------------+");
  debugPutString("\r\n |     Gesture Sensor APDS-9960 Demo        |");
  debugPutString("\r\n +-------------------------------------------------+\r\n");
  if(apds9960init()) 
  {
    debugPutString("APDS-9960 initialization complete\r\n");
  } 
  else 
  {
    ledSetMainLed(LED_ON);
    debugPutString("Something went wrong during APDS-9960 init!\r\n");
    debugPutString("Error!!! Re-Start Board\r\n");
    while(1);                /* Error!!! Re-Start Board */
  }
  // Start running the APDS-9960 gesture sensor engine
  if(enableGestureSensor(true)) 
  {
    debugPutString("Gesture sensor is now running\r\n");
  } 
  else 
  {
    ledSetMainLed(LED_ON);
    debugPutString("Something went wrong during gesture sensor init!\r\n");
    debugPutString("Error!!! Re-Start Board\r\n");
    while(1); /* Error!!! Re-Start Board */
  }
  
  EXTI0_Config();               /* Configuring External Interuput0 */
  ledSetMainLed(LED_BLINK);     /* System Led Start to Blink */
  while (1)
  {
    if(Gesture_Flag)  /*  External Interuput0 Flag */
    {
      NVIC_DisableIRQ(EXTI0_IRQn);
      gesture = apds9960ReadSensor(); /* Read Gesture */
      //reportLed(gesture);           /* Report to Sysstem Leds */
      reportSerial(gesture);    /* Report to Serial Port(Debug Port) */
      delayms(500);
      Gesture_Flag = 0;
      NVIC_EnableIRQ(EXTI0_IRQn);
    }
  }

}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 * Function Name : reportSerial
 *
 * Description   : Report to Serial 
 *
 * Input: Gesture
 *
 * Output  : None
 *
 * Return  : None
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
void reportSerial(int8_t gesture_t)
{
  switch (gesture_t) {
      case DIR_UP:
        debugPutString("Gesture Up....!\r\n");
        break;
      case DIR_DOWN:
        debugPutString("Gesture Down....!\r\n");
        break;
      case DIR_LEFT:
        debugPutString("Gesture Left....!\r\n");
        break;
      case DIR_RIGHT:
        debugPutString("Gesture Right....!\r\n");
        break;
      case DIR_NEAR:
        debugPutString("Gesture Near....!\r\n");
        break;
      case DIR_FAR:
        debugPutString("Gesture Far....!\r\n");
        break;
      //default:
        //debugPutString("NONE\r\n");
    }

}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 * Function Name : EXTI0_Config
 *
 * Description   : Configuring External Interrupt for Gesture INT Pin
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
void EXTI0_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
  /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure PA.00 pin as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  /* Connect EXTI0 Line to PA.00 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
  
  EXTI_ClearITPendingBit(EXTI_Line0);

  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}/* End of this function */


void EXTI0_IRQHandler(void)
{
 if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    Gesture_Flag = 1;
    // Clear the  EXTI line 0 pending bit //
    EXTI_ClearITPendingBit(EXTI_Line0);
  }

}
/*******************************************************************************
			* End of file															     *
*******************************************************************************/





