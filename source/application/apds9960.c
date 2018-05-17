/*******************************************************************************
 * ----------------------------------------------------------------------------*
 *  elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com   *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : apds9960.c                                                     *
 *                                                                             *
 * Description : APDS9960 IR Gesture Driver(Library for the SparkFun APDS-9960 breakout board)*
 *               SparkFun_APDS-9960.cpp Modified apds9960.c                    *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * Authors: Sarath S (Modified Shawn Hymel (SparkFun Electronics))             *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
/* MCU Files */
#include "stm32f10x.h"
/*Std Library Files */
#include "stdlib.h"
/* User Files */
#include "i2c_hal.h"
#include "apds9960.h"
#include "delay.h"
#include "led.h"
#include "debug.h"
#include "typedef.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
gesture_data_type gesture_data_;
int gesture_ud_delta_;
int gesture_lr_delta_;
int gesture_ud_count_;
int gesture_lr_count_;
int gesture_near_count_;
int gesture_far_count_;
int gesture_state_;
int gesture_motion_;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : apds9960init
 *
 *  Description  : Configures I2C communications and initializes registers to defaults
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : True if initialized successfully. False otherwise
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int apds9960init(void)
{
    uint8_t id;
    //ledSetLeftLed(LED_ON);  

    /* Initialize I2C */
    I2C1_init();
    delayms(700);
    /* Read ID register and check against known values for APDS-9960 */
    if( !i2c1_read(APDS9960_ID, &id,1) ) {
       ledSetRightLed(LED_ON);  
      return false;
        
    }
    ledSetLeftLed(LED_ON);  
    if( !(id == APDS9960_ID_1 || id == APDS9960_ID_2) ) {
        return false;
    }
     
    /* Set ENABLE register to 0 (disable all features) */
    if( !setMode(ALL, OFF) ) {
        return false;
    }
    
    /* Set default values for ambient light and proximity registers */
    if( !i2c1_write(APDS9960_ATIME, DEFAULT_ATIME) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_WTIME, DEFAULT_WTIME) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_PPULSE, DEFAULT_PROX_PPULSE) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_POFFSET_UR, DEFAULT_POFFSET_UR) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_POFFSET_DL, DEFAULT_POFFSET_DL) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_CONFIG1, DEFAULT_CONFIG1) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_LDRIVE) ) {
        return false;
    }
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( !setProxIntLowThresh(DEFAULT_PILT) ) {
        return false;
    }
    if( !setProxIntHighThresh(DEFAULT_PIHT) ) {
        return false;
    }
    if( !setLightIntLowThreshold(DEFAULT_AILT) ) {
        return false;
    }
    if( !setLightIntHighThreshold(DEFAULT_AIHT) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_PERS, DEFAULT_PERS) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_CONFIG2, DEFAULT_CONFIG2) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_CONFIG3, DEFAULT_CONFIG3) ) {
        return false;
    }
    
    /* Set default values for gesture sense registers */
    if( !setGestureEnterThresh(DEFAULT_GPENTH) ) {
        return false;
    }
    if( !setGestureExitThresh(DEFAULT_GEXTH) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GCONF1, DEFAULT_GCONF1) ) {
        return false;
    }
    if( !setGestureGain(DEFAULT_GGAIN) ) {
        return false;
    }
    if( !setGestureLEDDrive(DEFAULT_GLDRIVE) ) {
        return false;
    }
    if( !setGestureWaitTime(DEFAULT_GWTIME) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GOFFSET_U, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GOFFSET_D, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GOFFSET_L, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GOFFSET_R, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GPULSE, DEFAULT_GPULSE) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_GCONF3, DEFAULT_GCONF3) ) {
        return false;
    }
    if( !setGestureIntEnable(DEFAULT_GIEN) ) {
        return false;
    }
    
#if 0
    /* Gesture config register dump */
    uint8_t reg;
    uint8_t val;
  
    for(reg = 0x80; reg <= 0xAF; reg++) {
        if( (reg != 0x82) && \
            (reg != 0x8A) && \
            (reg != 0x91) && \
            (reg != 0xA8) && \
            (reg != 0xAC) && \
            (reg != 0xAD) )
        {
            i2c1_read(reg, val,1);
            //debugPutChar(reg);
            debugPutString(": 0x");
            //debugPutChar(val);

        }
    }

    for(reg = 0xE4; reg <= 0xE7; reg++) {
        i2c1_read(reg, val,1);
        //debugPutChar(reg);
        debugPutString(": 0x");
        //debugPutChar(val);
    }
#endif

    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setMode(uint8_t mode, uint8_t enable)
 *
 *  Description  :Enables or disables a feature in the APDS-9960
 *
 *  Input : mode which feature to enable,enable ON (1) or OFF (0)
 *
 *  Output : None
 *
 *  Return : True if operation success. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setMode(uint8_t mode, uint8_t enable)
{
    uint8_t reg_val;

    /* Read current ENABLE register */
    reg_val = getMode();
    if( reg_val == ERROR ) {
        return false;
    }
    
    /* Change bit(s) in ENABLE register */
    enable = enable & 0x01;
    if( mode >= 0 && mode <= 6 ) {
        if (enable) {
            reg_val |= (1 << mode);
        } else {
            reg_val &= ~(1 << mode);
        }
    } else if( mode == ALL ) {
        if (enable) {
            reg_val = 0x7F;
        } else {
            reg_val = 0x00;
        }
    }
        
    /* Write value back to ENABLE register */
    if( !i2c1_write(APDS9960_ENABLE, reg_val) ) {
        return false;
    }
        
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setMode(uint8_t mode, uint8_t enable)
 *
 *  Description  :Reads and returns the contents of the ENABLE register
 *
 *  Input : mode which feature to enable,enable ON (1) or OFF (0)
 *
 *  Output : None
 *
 *  Return : Contents of the ENABLE register. 0xFF if error.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
uint8_t getMode(void)
{
  uint8_t enable_value;
    
    /* Read current ENABLE register */
    if( !i2c1_read(APDS9960_ENABLE,&enable_value,1) ) 
    {
        return ERROR;
    }
    
    return enable_value;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setLEDDrive(uint8_t drive)
 *
 *  Description  : Sets the LED drive strength for proximity and ALS
 *  Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *  Input : drive the value (0-3) for the LED drive strength
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setLEDDrive(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !i2c1_read(APDS9960_CONTROL, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0x03;
    drive = drive << 6;
    val &= 0x3F;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !i2c1_write(APDS9960_CONTROL, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setProximityGain(uint8_t drive)
 *
 *  Description  :Sets the receiver gain for proximity detection
 *  Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *  Input : drive the value (0-3) for the gain
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setProximityGain(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !i2c1_read(APDS9960_CONTROL, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0x03;
    drive = drive << 2;
    val &= 0xF3;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !i2c1_write(APDS9960_CONTROL, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setAmbientLightGain(uint8_t drive)
 *
 *  Description  :Sets the receiver gain for the ambient light sensor (ALS)
 *  Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *  Input : drive the value (0-3) for the gain
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setAmbientLightGain(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from CONTROL register */
    if( !i2c1_read(APDS9960_CONTROL, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0x03;
    val &= 0xFC;
    val |= drive;
    
    /* Write register value back into CONTROL register */
    if( !i2c1_write(APDS9960_CONTROL, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */
/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setProxIntLowThresh(uint8_t threshold)
 *
 *  Description  :Sets the lower threshold for proximity detection
 *
 *  Input : threshold the lower proximity threshold
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/

int setProxIntLowThresh(uint8_t threshold)
{
    if( !i2c1_write(APDS9960_PILT, threshold) ) {
        return false;
    }
    
    return true;
}/* End of this function */
/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setProxIntHighThresh(uint8_t threshold)
 *
 *  Description  :Sets the high threshold for proximity detection
 *
 *  Input : threshold the high proximity threshold
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setProxIntHighThresh(uint8_t threshold)
{
    if( !i2c1_write(APDS9960_PIHT, threshold) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setLightIntLowThreshold(uint16_t threshold)
 *
 *  Description  :Sets the low threshold for ambient light interrupts
 *
 *  Input : threshold low threshold value for interrupt to trigger
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setLightIntLowThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;
    
    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;
    
    /* Write low byte */
    if( !i2c1_write(APDS9960_AILTL, val_low) ) {
        return false;
    }
    
    /* Write high byte */
    if( !i2c1_write(APDS9960_AILTH, val_high) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setLightIntHighThreshold(uint16_t threshold)
 *
 *  Description  :Sets the high threshold for ambient light interrupts
 *
 *  Input : threshold high threshold value for interrupt to trigger
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setLightIntHighThreshold(uint16_t threshold)
{
    uint8_t val_low;
    uint8_t val_high;
    
    /* Break 16-bit threshold into 2 8-bit values */
    val_low = threshold & 0x00FF;
    val_high = (threshold & 0xFF00) >> 8;
    
    /* Write low byte */
    if( !i2c1_write(APDS9960_AIHTL, val_low) ) {
        return false;
    }
    
    /* Write high byte */
    if( !i2c1_write(APDS9960_AIHTH, val_high) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureIntEnable(uint8_t enable)
 *
 *  Description  :Turns gesture-related interrupts on or off
 *
 *  Input : enable 1 to enable interrupts, 0 to turn them off
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureIntEnable(uint8_t enable)
{
    uint8_t val;
    
    /* Read value from GCONF4 register */
    if( !i2c1_read(APDS9960_GCONF4, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    enable &= 0x01;
    enable = enable << 1;
    val &= 0xFD;
    val |= enable;
    
    /* Write register value back into GCONF4 register */
    if( !i2c1_write(APDS9960_GCONF4, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureWaitTime(uint8_t time)
 *
 *  Description  :Sets the time in low power mode between gesture detections
 *  Value    Wait time
 *   0          0 ms
 *   1          2.8 ms
 *   2          5.6 ms
 *   3          8.4 ms
 *   4         14.0 ms
 *   5         22.4 ms
 *   6         30.8 ms
 *   7         39.2 ms
 *  Input : the value for the wait time
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureWaitTime(uint8_t time)
{
    uint8_t val;
    
    /* Read value from GCONF2 register */
    if( !i2c1_read(APDS9960_GCONF2, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    time &= 0x07;
    val &= 0xF8;
    val |= time;
    
    /* Write register value back into GCONF2 register */
    if( !i2c1_write(APDS9960_GCONF2, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureLEDDrive(uint8_t drive)
 *
 *  Description  :Sets the LED drive current during gesture mode
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 *  Input : drive the value for the LED drive current
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureLEDDrive(uint8_t drive)
{
    uint8_t val;
    
    /* Read value from GCONF2 register */
    if( !i2c1_read(APDS9960_GCONF2, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    drive &= 0x03;
    drive = drive << 3;
    val &= 0xE7;
    val |= drive;
    
    /* Write register value back into GCONF2 register */
    if( !i2c1_write(APDS9960_GCONF2, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureGain(uint8_t gain)
 *
 *  Description  :Sets the gain of the photodiode during gesture mode
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *  Input : gain the value for the photodiode gain
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureGain(uint8_t gain)
{
    uint8_t val;
    
    /* Read value from GCONF2 register */
    if( !i2c1_read(APDS9960_GCONF2, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    gain &= 0x03;
    gain = gain << 5;
    val &= 0x9F;
    val |= gain;
    
    /* Write register value back into GCONF2 register */
    if( !i2c1_write(APDS9960_GCONF2, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureExitThresh(uint8_t threshold)
 *
 *  Description  :Sets the exit proximity threshold for gesture sensing
 *
 *  Input : threshold proximity value needed to end gesture mode
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureExitThresh(uint8_t threshold)
{
    if( !i2c1_write(APDS9960_GEXTH, threshold) ) {
        return false;
    }
    
    return true;
}/* End of this function */


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureEnterThresh(uint8_t threshold)
 *
 *  Description  :Sets the entry proximity threshold for gesture sensing
 *
 *  Input : threshold proximity value needed to start gesture mode
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureEnterThresh(uint8_t threshold)
{
    if( !i2c1_write(APDS9960_GPENTH, threshold) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : enableGestureSensor(int interrupts)
 *
 *  Description  :Starts the gesture recognition engine on the APDS-9960
 *
 *  Input : interrupts true to enable hardware external interrupt on gesture
 *
 *  Output : None
 *
 *  Return : True if engine enabled correctly. False on error.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int enableGestureSensor(int interrupts)
{
    
    /* Enable gesture mode
       Set ENABLE to 0 (power off)
       Set WTIME to 0xFF
       Set AUX to LED_BOOST_300
       Enable PON, WEN, PEN, GEN in ENABLE 
    */
    resetGestureParameters();
    if( !i2c1_write(APDS9960_WTIME, 0xFF) ) {
        return false;
    }
    if( !i2c1_write(APDS9960_PPULSE, DEFAULT_GESTURE_PPULSE) ) {
        return false;
    }
    if( !setLEDBoost(LED_BOOST_300) ) {
        return false;
    }
    if( interrupts ) {
        if( !setGestureIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setGestureIntEnable(0) ) {
            return false;
        }
    }
    if( !setGestureMode(1) ) {
        return false;
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(WAIT, 1) ) {
        return false;
    }
    if( !setMode(PROXIMITY, 1) ) {
        return false;
    }
    if( !setMode(GESTURE, 1) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : resetGestureParameters(void)
 *
 *  Description  :Resets all the parameters in the gesture data member
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
void resetGestureParameters(void)
{
    gesture_data_.index = 0;
    gesture_data_.total_gestures = 0;
    
    gesture_ud_delta_ = 0;
    gesture_lr_delta_ = 0;
    
    gesture_ud_count_ = 0;
    gesture_lr_count_ = 0;
    
    gesture_near_count_ = 0;
    gesture_far_count_ = 0;
    
    gesture_state_ = 0;
    gesture_motion_ = DIR_NONE;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setLEDBoost(uint8_t boost)
 *
 *  Description  :Sets the LED current boost value
 * Value  Boost Current
 *   0        100%
 *   1        150%
 *   2        200%
 *   3        300%
 *  Input : drive the value (0-3) for current boost (100-300%)
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setLEDBoost(uint8_t boost)
{
    uint8_t val;
    
    /* Read value from CONFIG2 register */
    if( !i2c1_read(APDS9960_CONFIG2, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    boost &= 0x03;
    boost = boost << 4;
    val &= 0xCF;
    val |= boost;
    
    /* Write register value back into CONFIG2 register */
    if( !i2c1_write(APDS9960_CONFIG2, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */    

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : setGestureMode(uint8_t mode)
 *
 *  Description  :Tells the state machine to either enter or exit gesture state machine
 *
 *  Input : mode 1 to enter gesture state machine, 0 to exit.
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int setGestureMode(uint8_t mode)
{
    uint8_t val;
    
    /* Read value from GCONF4 register */
    if( !i2c1_read(APDS9960_GCONF4, &val,1) ) {
        return false;
    }
    
    /* Set bits in register to given value */
    mode &= 0x01;
    val &= 0xFE;
    val |= mode;
    
    /* Write register value back into GCONF4 register */
    if( !i2c1_write(APDS9960_GCONF4, val) ) {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : enablePower(void)
 *
 *  Description  :Turn the APDS-9960 on
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : True if operation successful. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int enablePower(void)
{
    if( !setMode(POWER, 1) ) {
        return false;
    }
    
    return true;
}/* End of this function */


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : isGestureAvailable(void)
 *
 *  Description  :Determines if there is a gesture available for reading
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : True if gesture available. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int isGestureAvailable(void)
{
    uint8_t val;
    /* Read value from GSTATUS register */
    if( !i2c1_read(APDS9960_GSTATUS, &val,1) ) {
        return ERROR;
    }
    
    /* Shift and mask out GVALID bit */
    val &= APDS9960_GVALID;
    
    /* Return true/false based on GVALID bit */
    if( val == 1) {
        return true;
    } else {
        return false;
    }
}/* End of this function */


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : readGesture(void)
 *
 *  Description  :Processes a gesture event and returns best guessed gesture
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : Number corresponding to gesture. -1 on error.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int readGesture(void)
{
    uint8_t fifo_level = 0;
    int bytes_read = 0;
    uint8_t fifo_data[128];
    uint8_t gstatus;
    int motion;
    int i;
    
    /* Make sure that power and gesture is on and data is valid */
    if( !isGestureAvailable() || !(getMode() & 0x41) ) {
        return DIR_NONE;
    }
    
    /* Keep looping as long as gesture data is valid */
    while(1) {
    
        /* Wait some time to collect next batch of FIFO data */
        delayms(FIFO_PAUSE_TIME);
        
        /* Get the contents of the STATUS register. Is data still valid? */
        if( !i2c1_read(APDS9960_GSTATUS, &gstatus,1) ) {
            return ERROR;
        }
        
        /* If we have valid data, read in FIFO */
        if( (gstatus & APDS9960_GVALID) == APDS9960_GVALID ) {
        
            /* Read the current FIFO level */
            if( !i2c1_read(APDS9960_GFLVL, &fifo_level,1) ) {
                return ERROR;
            }

#if DEBUGPRINT
            debugPutString("FIFO Level: ");
            debugPutChar(fifo_level);
#endif

            /* If there's stuff in the FIFO, read it into our data block */
            if( fifo_level > 0) {
                bytes_read = i2c1_read(APDS9960_GFIFO_U, 
                                                fifo_data, 
                                                (fifo_level * 4) );
                if( bytes_read == -1 ) {
                    return ERROR;
                }
#if DEBUGPRINT
                debugPutString("FIFO Dump: ");
                for ( i = 0; i < bytes_read; i++ ) {
                    debugPutChar(fifo_data[i]);
                    debugPutString(" ");
                }
                debugPutString("\r\n");
#endif

                /* If at least 1 set of data, sort the data into U/D/L/R */
                if( bytes_read >= 4 ) {
                    for( i = 0; i < bytes_read; i += 4 ) {
                        gesture_data_.u_data[gesture_data_.index] = \
                                                            fifo_data[i + 0];
                        gesture_data_.d_data[gesture_data_.index] = \
                                                            fifo_data[i + 1];
                        gesture_data_.l_data[gesture_data_.index] = \
                                                            fifo_data[i + 2];
                        gesture_data_.r_data[gesture_data_.index] = \
                                                            fifo_data[i + 3];
                        gesture_data_.index++;
                        gesture_data_.total_gestures++;
                    }
                    
#if DEBUGPRINT
                debugPutString("Up Data: ");
                for ( i = 0; i < gesture_data_.total_gestures; i++ ) {
                    debugPutChar(gesture_data_.u_data[i]);
                    debugPutString(" ");
                }
                debugPutString("\r\n");
#endif

                    /* Filter and process gesture data. Decode near/far state */
                    if( processGestureData() ) {
                        if( decodeGesture() ) {
                            //***TODO: U-Turn Gestures
#if DEBUGPRINT
                           debugPutChar(gesture_motion_);
#endif
                        }
                    }
                    
                    /* Reset data */
                    gesture_data_.index = 0;
                    gesture_data_.total_gestures = 0;
                }
            }
        } else {
    
            /* Determine best guessed gesture and clean up */
            delayms(FIFO_PAUSE_TIME);
            decodeGesture();
            motion = gesture_motion_;
#if DEBUGPRINT
            debugPutString("END: ");
            debugPutChar(gesture_motion_);
#endif
            resetGestureParameters();
            return motion;
        }
    }
}

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : processGestureData(void)
 *
 *  Description  :Processes the raw gesture data to determine swipe direction
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : True if near or far state seen. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int processGestureData(void)
{
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    int ud_ratio_first;
    int lr_ratio_first;
    int ud_ratio_last;
    int lr_ratio_last;
    int ud_delta;
    int lr_delta;
    int i;

    /* If we have less than 4 total gestures, that's not enough */
    if( gesture_data_.total_gestures <= 4 ) {
        return false;
    }
    
    /* Check to make sure our data isn't out of bounds */
    if( (gesture_data_.total_gestures <= 32) && \
        (gesture_data_.total_gestures > 0) ) {
        
        /* Find the first value in U/D/L/R above the threshold */
        for( i = 0; i < gesture_data_.total_gestures; i++ ) {
            if( (gesture_data_.u_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.d_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.l_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.r_data[i] > GESTURE_THRESHOLD_OUT) ) {
                
                u_first = gesture_data_.u_data[i];
                d_first = gesture_data_.d_data[i];
                l_first = gesture_data_.l_data[i];
                r_first = gesture_data_.r_data[i];
                break;
            }
        }
        
        /* If one of the _first values is 0, then there is no good data */
        if( (u_first == 0) || (d_first == 0) || \
            (l_first == 0) || (r_first == 0) ) {
            
            return false;
        }
        /* Find the last value in U/D/L/R above the threshold */
        for( i = gesture_data_.total_gestures - 1; i >= 0; i-- ) {
#if DEBUGPRINT
            debugPutString("Finding last: ");
            debugPutString("U:");
            debugPutChar(gesture_data_.u_data[i]);
            debugPutString(" D:");
            debugPutChar(gesture_data_.d_data[i]);
            debugPutString(" L:");
            debugPutChar(gesture_data_.l_data[i]);
            debugPutString(" R:");
            debugPutChar(gesture_data_.r_data[i]);
            debugPutString("\r\n");
#endif
            if( (gesture_data_.u_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.d_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.l_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.r_data[i] > GESTURE_THRESHOLD_OUT) ) {
                
                u_last = gesture_data_.u_data[i];
                d_last = gesture_data_.d_data[i];
                l_last = gesture_data_.l_data[i];
                r_last = gesture_data_.r_data[i];
                break;
            }
        }
    }
    
    /* Calculate the first vs. last ratio of up/down and left/right */
    ud_ratio_first = ((u_first - d_first) * 100) / (u_first + d_first);
    lr_ratio_first = ((l_first - r_first) * 100) / (l_first + r_first);
    ud_ratio_last = ((u_last - d_last) * 100) / (u_last + d_last);
    lr_ratio_last = ((l_last - r_last) * 100) / (l_last + r_last);
       
#if DEBUGPRINT
    debugPutString("Last Values: ");
    debugPutString("U:");
    debugPutChar(u_last);
    debugPutString(" D:");
    debugPutChar(d_last);
    debugPutString(" L:");
    debugPutChar(l_last);
    debugPutString(" R:");
    debugPutChar(r_last);
    debugPutString("\r\n");

    debugPutString("Ratios: ");
    debugPutString("UD Fi: ");
    debugPutChar(ud_ratio_first);
    debugPutString(" UD La: ");
    debugPutChar(ud_ratio_last);
    debugPutString(" LR Fi: ");
    debugPutChar(lr_ratio_first);
    debugPutString(" LR La: ");
    debugPutChar(lr_ratio_last);
    debugPutString("\r\n");

#endif
       
    /* Determine the difference between the first and last ratios */
    ud_delta = ud_ratio_last - ud_ratio_first;
    lr_delta = lr_ratio_last - lr_ratio_first;
    
#if DEBUGPRINT
    debugPutString("Deltas: ");
    debugPutString("UD: ");
    debugPutChar(ud_delta);
    debugPutString(" LR: ");
    debugPutChar(lr_delta);
    debugPutString("\r\n");
#endif

    /* Accumulate the UD and LR delta values */
    gesture_ud_delta_ += ud_delta;
    gesture_lr_delta_ += lr_delta;
    
#if DEBUGPRINT
    debugPutString("Accumulations: ");
    debugPutString("UD: ");
    debugPutChar(gesture_ud_delta_);
    debugPutString(" LR: ");
    debugPutChar(gesture_lr_delta_);
    debugPutString("\r\n");
#endif
    
    /* Determine U/D gesture */
    if( gesture_ud_delta_ >= GESTURE_SENSITIVITY_1 ) {
        gesture_ud_count_ = 1;
    } else if( gesture_ud_delta_ <= -GESTURE_SENSITIVITY_1 ) {
        gesture_ud_count_ = -1;
    } else {
        gesture_ud_count_ = 0;
    }
    
    /* Determine L/R gesture */
    if( gesture_lr_delta_ >= GESTURE_SENSITIVITY_1 ) {
        gesture_lr_count_ = 1;
    } else if( gesture_lr_delta_ <= -GESTURE_SENSITIVITY_1 ) {
        gesture_lr_count_ = -1;
    } else {
        gesture_lr_count_ = 0;
    }
    
    /* Determine Near/Far gesture */
    if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == 0) ) {
        if( (abs(ud_delta) < GESTURE_SENSITIVITY_2) && \
            (abs(lr_delta) < GESTURE_SENSITIVITY_2) ) {
            
            if( (ud_delta == 0) && (lr_delta == 0) ) {
                gesture_near_count_++;
            } else if( (ud_delta != 0) || (lr_delta != 0) ) {
                gesture_far_count_++;
            }
            
            if( (gesture_near_count_ >= 10) && (gesture_far_count_ >= 2) ) {
                if( (ud_delta == 0) && (lr_delta == 0) ) {
                    gesture_state_ = NEAR_STATE;
                } else if( (ud_delta != 0) && (lr_delta != 0) ) {
                    gesture_state_ = FAR_STATE;
                }
                return true;
            }
        }
    } else {
        if( (abs(ud_delta) < GESTURE_SENSITIVITY_2) && \
            (abs(lr_delta) < GESTURE_SENSITIVITY_2) ) {
                
            if( (ud_delta == 0) && (lr_delta == 0) ) {
                gesture_near_count_++;
            }
            
            if( gesture_near_count_ >= 10 ) {
                gesture_ud_count_ = 0;
                gesture_lr_count_ = 0;
                gesture_ud_delta_ = 0;
                gesture_lr_delta_ = 0;
            }
        }
    }
    
#if DEBUGPRINT
    debugPutString("UD_CT: ");
    debugPutChar(gesture_ud_count_);
    debugPutString(" LR_CT: ");
    debugPutChar(gesture_lr_count_);
    debugPutString(" NEAR_CT: ");
    debugPutChar(gesture_near_count_);
    debugPutString(" FAR_CT: ");
    debugPutChar(gesture_far_count_);
    debugPutString("----------");
#endif
    
    return false;
}/* End of this function */


/* ----------------------------------------------------------------------------*
 *
 *  Function Name : decodeGesture(void)
 *
 *  Description  :Determines swipe direction or near/far state
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : True if near/far event. False otherwise.
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/
int decodeGesture(void)
{
    /* Return if near or far event is detected */
    if( gesture_state_ == NEAR_STATE ) {
        gesture_motion_ = DIR_NEAR;
        return true;
    } else if ( gesture_state_ == FAR_STATE ) {
        gesture_motion_ = DIR_FAR;
        return true;
    }
    
    /* Determine swipe direction */
    if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == 0) ) {
        gesture_motion_ = DIR_UP;
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == 0) ) {
        gesture_motion_ = DIR_DOWN;
    } else if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == 1) ) {
        gesture_motion_ = DIR_RIGHT;
    } else if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == -1) ) {
        gesture_motion_ = DIR_LEFT;
    } else if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == 1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_UP;
        } else {
            gesture_motion_ = DIR_RIGHT;
        }
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == -1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_DOWN;
        } else {
            gesture_motion_ = DIR_LEFT;
        }
    } else if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == -1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_UP;
        } else {
            gesture_motion_ = DIR_LEFT;
        }
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == 1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_DOWN;
        } else {
            gesture_motion_ = DIR_RIGHT;
        }
    } else {
        return false;
    }
    
    return true;
}/* End of this function */

/* ----------------------------------------------------------------------------*
 *
 *  Function Name : apds9960ReadSensor(void)
 *
 *  Description  :Read apd9960 Gesture 
 *
 *  Input : None
 *
 *  Output : None
 *
 *  Return : Gesture Value( UP,Down,Near,Far,Right,Left)
 * ----------------------------------------------------------------------------*
 * Authors: Sarath S
 * Date: May 17, 2017
 * ---------------------------------------------------------------------------*/

int apds9960ReadSensor(void)
{
  int Gesture = 0;
   if(isGestureAvailable()) 
   {
     Gesture = readGesture();
     
   }
    return Gesture;
}

/*******************************************************************************
			* End of file *
*******************************************************************************/
