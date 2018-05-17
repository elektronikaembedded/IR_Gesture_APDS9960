/*******************************************************************************
 * ----------------------------------------------------------------------------*
 *  elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com   *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : i2c_hal.c                                                        *
 *                                                                             *
 * Description : i2c                                                           *
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
#include "stm32f10x_i2c.h"
#include "stm32f10x_gpio.h"
#include "i2c_hal.h"
#include "apds9960.h"
#include "debug.h"
#include "typedef.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/* ----------------------------------------------------------------------------*
 *
 * Function Name : I2C1_init
 *
 * Description   : Stm32x I2C1_init
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
void I2C1_init(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB| RCC_APB2Periph_AFIO , ENABLE);
  /*  Configure I2C_EE pins: SCL and SDA */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*  I2C configuration */
  // Connect I2C1 pins to AF
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  //I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 200000;
    /* Apply I2C configuration after enabling it */
  I2C_Init(I2C1, &I2C_InitStructure);
    /*  I2C Peripheral Enable */
  I2C_Cmd(I2C1, ENABLE);
  //I2C_AcknowledgeConfig(I2C1, ENABLE);
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 * Function Name : i2c1_read
 *
 * Description   : Read i2c1 Register Data
 *
 * Input: addr,data ,number of bytes
 *
 * Output  : data Pointer
 *
 * Return  : no of bytes wites if successfully. False otherwise
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/

int i2c1_read(uint8_t u8addr, uint8_t *u8data,uint8_t u8qty)
{
  volatile uint32_t u32timeout;
  uint8_t recived = 0;
  /* While the bus is busy */
  //u32timeout = I2C_WAIT_TIMEOUT;
  //while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY)&& --u32timeout);
  //if (!u32timeout) return 1;
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send paj7620 address for write */
  I2C_Send7bitAddress(I2C1, APDS9960_I2C_ADDR << 1, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C1, ENABLE);
  /* Send the paj7620's internal address to write to */
  I2C_SendData(I2C1, u8addr);
  /* Test on EV8 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send STRAT condition a second time */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send paj7620 address for read */
  I2C_Send7bitAddress(I2C1, APDS9960_I2C_ADDR << 1, I2C_Direction_Receiver);
  /* Test on EV6 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* While there is data to be read */
  while(u8qty)
  {
    if(u8qty == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C1, DISABLE);

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2C1, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the paj7620 */
      //*u8data = I2C_ReceiveData(I2C1);
      u8data[recived] = I2C_ReceiveData(I2C1);

      /* Point to the next location where the byte read will be saved */
      //u8data++;
      recived++;

      /* Decrement the read bytes counter */
      u8qty--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);

  return recived;

}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 * Function Name : i2c1_write
 *
 * Description   : write date to i2c1 
 *
 * Input: addr register ,data
 *
 * Output  : None
 *
 * Return  : True if successfully write. False otherwise
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int i2c1_write(uint8_t u8addr,uint8_t u8data)
{
  volatile uint32_t u32timeout;
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send paj7620 address for write */
  I2C_Send7bitAddress(I2C1, APDS9960_I2C_ADDR << 1, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send the paj7620's internal address to write to */
  I2C_SendData(I2C1, u8addr);
  /* Test on EV8 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send the byte to be written */
  I2C_SendData(I2C1, u8data);
  /* Test on EV8 and clear it */
  u32timeout = I2C_WAIT_TIMEOUT;
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)&& --u32timeout);
  if (!u32timeout) return fail;
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  return success;
}/* End of this function */


/*******************************************************************************
			* End of file *
*******************************************************************************/