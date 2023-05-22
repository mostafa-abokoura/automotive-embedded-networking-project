/****************************************************************************** 
 * Module      : Application                                                  * 
 * File Name   : app.c                                                        *
 * Description : Source file for app module                                   * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include <indicator_led_control_system.h>
#include "app.h"
#include "can.h"
#include "button.h"
#include "indicator_led.h"
#include "uart_stdio.h"

/****************************************************************************** 
 *                                                                            * 
 *                              Tasks Container                               * 
 *                                                                            * 
 ******************************************************************************/
Task_t Task[] =
{
    {
        .is_enabled = true,
        .code = IndLEDCtrlSys_TokenTimeout,
        .period = 1
    },
    {
        .is_enabled = true,
        .code = IndLEDCtrlSys_ReceiveMessage,
        .period = 2
    },
    {
        .is_enabled = true,
        .code = IndLEDCtrlSys_TransmitMessage,
        .period = 2
    },
    {
        .is_enabled = true,
        .code = IndLEDCtrlSys_UpdateDefaultColor,
        .period = 2
    },
    {
        .is_enabled = true,
        .code = IndLEDCtrlSys_UpdateIndLED,
        .period = 4
    }
};

/****************************************************************************** 
 *                                                                            * 
 *                              Global Variables                              * 
 *                                                                            * 
 ******************************************************************************/

/* Number of Tasks for scheduler */
const uint8_t Num_Of_Tasks = (sizeof(Task) / sizeof(Task_t));

/******************************************************************************
 * Name         : Task_Init                                                   *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Initializes tasks used in application.                      *
 ******************************************************************************/
void Task_Init(void)
{
    /* Initializes indicator LED. */
    IndicatorLED_Init();
    
    /* Initializes switch 1. */
    Button_Init(SW1_CH);
    
    /* Initializes switch 2. */
    Button_Init(SW2_CH);
    
    /* Initializes CAN bus. */
	CAN_Init();

	/* Configures CAN bus for receiving. */
    CAN_ReceiveConfig();
    
    /* Configures CAN bus for transmitting. */
    CAN_TransmitConfig();

    /* Configures UART for console messaging. */
    UART_Init();
}
