/*******************************************************************************
 * ----------------------------------------------------------------------------*
 *  elektronikaembedded@gamil.com ,https://elektronikaembedded.wordpress.com   *
 * ----------------------------------------------------------------------------*
 *                                                                             *
 * File Name  : apds9960.h                                                     *
 *                                                                             *
 * Description : APDS9960 IR Gesture Driver(Library for the SparkFun APDS-9960 breakout board)*
 *               SparkFun_APDS-9960.cpp Modified apds9960.c                    *
 * Version     : PrototypeV1.0                                                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * Authors: Sarath S (Modified Shawn Hymel (SparkFun Electronics))             *
 * Date: May 16, 2017                                                          *
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APDS9960_H
#define __APDS9960_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Debug */

#define DEBUG                   0

/* APDS-9960 I2C address */
#define APDS9960_I2C_ADDR       0x39

/* Gesture parameters */
#define GESTURE_THRESHOLD_OUT   10
#define GESTURE_SENSITIVITY_1   50
#define GESTURE_SENSITIVITY_2   20

/* Error code for returned values */
#define ERROR                   0xFF

/* Acceptable device IDs */
#define APDS9960_ID_1           0xAB
#define APDS9960_ID_2           0x9C 

/* Misc parameters */
#define FIFO_PAUSE_TIME         30      // Wait period (ms) between FIFO reads

/* APDS-9960 register addresses */
#define APDS9960_ENABLE         0x80
#define APDS9960_ATIME          0x81
#define APDS9960_WTIME          0x83
#define APDS9960_AILTL          0x84
#define APDS9960_AILTH          0x85
#define APDS9960_AIHTL          0x86
#define APDS9960_AIHTH          0x87
#define APDS9960_PILT           0x89
#define APDS9960_PIHT           0x8B
#define APDS9960_PERS           0x8C
#define APDS9960_CONFIG1        0x8D
#define APDS9960_PPULSE         0x8E
#define APDS9960_CONTROL        0x8F
#define APDS9960_CONFIG2        0x90
#define APDS9960_ID             0x92
#define APDS9960_STATUS         0x93
#define APDS9960_CDATAL         0x94
#define APDS9960_CDATAH         0x95
#define APDS9960_RDATAL         0x96
#define APDS9960_RDATAH         0x97
#define APDS9960_GDATAL         0x98
#define APDS9960_GDATAH         0x99
#define APDS9960_BDATAL         0x9A
#define APDS9960_BDATAH         0x9B
#define APDS9960_PDATA          0x9C
#define APDS9960_POFFSET_UR     0x9D
#define APDS9960_POFFSET_DL     0x9E
#define APDS9960_CONFIG3        0x9F
#define APDS9960_GPENTH         0xA0
#define APDS9960_GEXTH          0xA1
#define APDS9960_GCONF1         0xA2
#define APDS9960_GCONF2         0xA3
#define APDS9960_GOFFSET_U      0xA4
#define APDS9960_GOFFSET_D      0xA5
#define APDS9960_GOFFSET_L      0xA7
#define APDS9960_GOFFSET_R      0xA9
#define APDS9960_GPULSE         0xA6
#define APDS9960_GCONF3         0xAA
#define APDS9960_GCONF4         0xAB
#define APDS9960_GFLVL          0xAE
#define APDS9960_GSTATUS        0xAF
#define APDS9960_IFORCE         0xE4
#define APDS9960_PICLEAR        0xE5
#define APDS9960_CICLEAR        0xE6
#define APDS9960_AICLEAR        0xE7
#define APDS9960_GFIFO_U        0xFC
#define APDS9960_GFIFO_D        0xFD
#define APDS9960_GFIFO_L        0xFE
#define APDS9960_GFIFO_R        0xFF

/* Bit fields */
#define APDS9960_PON            0x01
#define APDS9960_AEN            0x02
#define APDS9960_PEN            0x04
#define APDS9960_WEN            0x08
#define APSD9960_AIEN           0x10
#define APDS9960_PIEN           0x20
#define APDS9960_GEN            0x40
#define APDS9960_GVALID         0x01

/* On/Off definitions */
#define OFF                     0
#define ON                      1

/* Acceptable parameters for setMode */
#define POWER                   0
#define AMBIENT_LIGHT           1
#define PROXIMITY               2
#define WAIT                    3
#define AMBIENT_LIGHT_INT       4
#define PROXIMITY_INT           5
#define GESTURE                 6
#define ALL                     7

/* LED Drive values */
#define LED_DRIVE_100MA         0
#define LED_DRIVE_50MA          1
#define LED_DRIVE_25MA          2
#define LED_DRIVE_12_5MA        3

/* Proximity Gain (PGAIN) values */
#define PGAIN_1X                0
#define PGAIN_2X                1
#define PGAIN_4X                2
#define PGAIN_8X                3

/* ALS Gain (AGAIN) values */
#define AGAIN_1X                0
#define AGAIN_4X                1
#define AGAIN_16X               2
#define AGAIN_64X               3

/* Gesture Gain (GGAIN) values */
#define GGAIN_1X                0
#define GGAIN_2X                1
#define GGAIN_4X                2
#define GGAIN_8X                3

/* LED Boost values */
#define LED_BOOST_100           0
#define LED_BOOST_150           1
#define LED_BOOST_200           2
#define LED_BOOST_300           3    

/* Gesture wait time values */
#define GWTIME_0MS              0
#define GWTIME_2_8MS            1
#define GWTIME_5_6MS            2
#define GWTIME_8_4MS            3
#define GWTIME_14_0MS           4
#define GWTIME_22_4MS           5
#define GWTIME_30_8MS           6
#define GWTIME_39_2MS           7

/* Default values */
#define DEFAULT_ATIME           219     // 103ms
#define DEFAULT_WTIME           246     // 27ms
#define DEFAULT_PROX_PPULSE     0x87    // 16us, 8 pulses
#define DEFAULT_GESTURE_PPULSE  0x89    // 16us, 10 pulses
#define DEFAULT_POFFSET_UR      0       // 0 offset
#define DEFAULT_POFFSET_DL      0       // 0 offset      
#define DEFAULT_CONFIG1         0x60    // No 12x wait (WTIME) factor
#define DEFAULT_LDRIVE          LED_DRIVE_100MA
#define DEFAULT_PGAIN           PGAIN_4X
#define DEFAULT_AGAIN           AGAIN_4X
#define DEFAULT_PILT            0       // Low proximity threshold
#define DEFAULT_PIHT            50      // High proximity threshold
#define DEFAULT_AILT            0xFFFF  // Force interrupt for calibration
#define DEFAULT_AIHT            0
#define DEFAULT_PERS            0x11    // 2 consecutive prox or ALS for int.
#define DEFAULT_CONFIG2         0x01    // No saturation interrupts or LED boost  
#define DEFAULT_CONFIG3         0       // Enable all photodiodes, no SAI
#define DEFAULT_GPENTH          40      // Threshold for entering gesture mode
#define DEFAULT_GEXTH           30      // Threshold for exiting gesture mode    
#define DEFAULT_GCONF1          0x40    // 4 gesture events for int., 1 for exit
#define DEFAULT_GGAIN           GGAIN_4X
#define DEFAULT_GLDRIVE         LED_DRIVE_100MA
#define DEFAULT_GWTIME          GWTIME_2_8MS
#define DEFAULT_GOFFSET         0       // No offset scaling for gesture mode
#define DEFAULT_GPULSE          0xC9    // 32us, 10 pulses
#define DEFAULT_GCONF3          0       // All photodiodes active during gesture
#define DEFAULT_GIEN            0       // Disable gesture interrupts

/* Direction definitions */
enum {
  DIR_NONE,
  DIR_LEFT,
  DIR_RIGHT,
  DIR_UP,
  DIR_DOWN,
  DIR_NEAR,
  DIR_FAR,
  DIR_ALL
};

/* State definitions */
enum {
  NA_STATE,
  NEAR_STATE,
  FAR_STATE,
  ALL_STATE
};

/* Container for gesture data */
typedef struct gesture_data_type {
    uint8_t u_data[32];
    uint8_t d_data[32];
    uint8_t l_data[32];
    uint8_t r_data[32];
    uint8_t index;
    uint8_t total_gestures;
    uint8_t in_threshold;
    uint8_t out_threshold;
} gesture_data_type;

/* Exported functions ------------------------------------------------------- */


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
int apds9960init(void);

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
int setMode(uint8_t mode, uint8_t enable);


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
uint8_t getMode(void);


 /* Turn the APDS-9960 on and off */

//int disablePower(void);

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
int enablePower(void);

  /* Enable or disable specific sensors */

//int enableLightSensor(int interrupts = false);
//int disableLightSensor();
//int enableProximitySensor(int interrupts = false);
//int disableProximitySensor();
//int disableGestureSensor();

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
int enableGestureSensor(int interrupts);

    /* LED drive strength control */

//uint8_t getLEDDrive();
//uint8_t getGestureLEDDrive();

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
int setLEDDrive(uint8_t drive);

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
int setGestureLEDDrive(uint8_t drive);

    /* Gain control */

//uint8_t getAmbientLightGain();
//int getProximityGain();
//int getGestureGain();

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
int setAmbientLightGain(uint8_t drive);
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
int setProximityGain(uint8_t drive);

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
int setGestureGain(uint8_t gain);


    /* Get and set light interrupt thresholds */

//int getLightIntLowThreshold(uint16_t &threshold);
//int getLightIntHighThreshold(uint16_t &threshold);

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
int setLightIntLowThreshold(uint16_t threshold);


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
int setLightIntHighThreshold(uint16_t threshold);

    /* Get and set proximity interrupt thresholds */

//int getProximityIntLowThreshold(uint8_t &threshold);
//int setProximityIntLowThreshold(uint8_t threshold);
//int getProximityIntHighThreshold(uint8_t &threshold);
//int setProximityIntHighThreshold(uint8_t threshold);

    /* Get and set interrupt enables */

//uint8_t getAmbientLightIntEnable();
//int setAmbientLightIntEnable(uint8_t enable);
//int getProximityIntEnable();
//int setProximityIntEnable(uint8_t enable);
//uint8_t getGestureIntEnable();

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
int setGestureIntEnable(uint8_t enable);
  
    /* Clear interrupts */

//int clearAmbientLightInt();
//int clearProximityInt();  

    /* Ambient light methods */

//int readAmbientLight(uint16_t &val);
//int readRedLight(uint16_t &val);
//int readGreenLight(uint16_t &val);
//int readBlueLight(uint16_t &val);

    /* Proximity methods */

//int readProximity(uint8_t &val);
    
    /* Gesture methods */

//int isGestureAvailable();

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
int readGesture(void);


    /* Gesture processing */

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
int decodeGesture(void);

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
void resetGestureParameters(void);

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
int processGestureData(void);


    /* Proximity Interrupt Threshold */

//uint8_t getProxIntLowThresh();
//uint8_t getProxIntHighThresh();

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
int setProxIntHighThresh(uint8_t threshold);
    

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

int setProxIntLowThresh(uint8_t threshold);

/* LED Boost Control */

//uint8_t getLEDBoost();
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
int setLEDBoost(uint8_t boost);
    
    /* Proximity photodiode select */

//uint8_t getProxGainCompEnable(void);
//int setProxGainCompEnable(uint8_t enable);
//uint8_t getProxPhotoMask();
//int setProxPhotoMask(uint8_t mask);

/* Gesture threshold control */

//uint8_t getGestureEnterThresh();
//uint8_t getGestureExitThresh();
    
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
int setGestureEnterThresh(uint8_t threshold);

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
int setGestureExitThresh(uint8_t threshold);

    /* Gesture LED, gain, and time control */

//uint8_t getGestureWaitTime(void);
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
int setGestureWaitTime(uint8_t time);
    
    /* Gesture mode */

//uint8_t getGestureMode();
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
int setGestureMode(uint8_t mode);

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

int apds9960ReadSensor(void);


#endif /* __APDS9960_H */

/******* https://elektronikaembedded.wordpress.com  *****END OF FILE***********/
