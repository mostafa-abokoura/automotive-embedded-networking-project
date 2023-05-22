/****************************************************************************** 
 * Module      : Indicator LED Control System                                 *
 * File Name   : indicator_led_control_system.h                               *
 * Description : Header file for control system module                        *
 * Created on  : Mar 26, 2020                                                 * 
 ******************************************************************************/

#ifndef INDICATOR_LED_CONTROL_SYSTEM_H_
#define INDICATOR_LED_CONTROL_SYSTEM_H_

#include "indicator_led.h"
#include "button.h"

/******************************************************************************
 *                                                                            *
 *                              Shared Variables                              *
 *                                                                            *
 ******************************************************************************/

/* Send Token Flag */
extern bool g_SendToken;

/* Has Token Flag */
extern bool g_HasToken;

/****************************************************************************** 
 *                                                                            * 
 *                                Definitions                                 * 
 *                                                                            * 
 ******************************************************************************/

/* Node IDs */
#define NODE_1          ( 0 )
#define NODE_2          ( 1 )
#define NODE_3          ( 2 )

/* Token timeout in milliseconds */
#define TOKEN_TIMEOUT   ( 100 )

/* Node definitions */
#define START           ( 0 )
#define END             ( 2 )
#define COUNT           ( 3 )
#define MAP             ( 1 )

/* Colors order */
static const uint8_t color[3] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

/* State Machine */
static const uint8_t state[][3] = {{1, 3, 2},
                                   {2, 1, 3},
                                   {3, 2, 1}};

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Checks for received messages */
extern void IndLEDCtrlSys_ReceiveMessage(void);

/* Transmits message */
extern void IndLEDCtrlSys_TransmitMessage(void);

/* Updates default ECU LED color variable (not white) */
extern void IndLEDCtrlSys_UpdateDefaultColor(void);

/* Checks for token Timeout */
extern void IndLEDCtrlSys_TokenTimeout(void);

/* Updates indicator LED color */
extern void IndLEDCtrlSys_UpdateIndLED(void);

/* Updates buttons status */
extern void IndLEDCtrlSys_UpdateButtonStatus(void);


#endif /* INDICATOR_LED_CONTROL_SYSTEM_H_ */
