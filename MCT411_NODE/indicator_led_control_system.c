/****************************************************************************** 
 * Module      : Indicator LED Control System                                 *
 * File Name   : indicator_led_control_system.c                               *
 * Description : Source file for control system module                        * 
 * Created on  : Mar 26, 2020                                                 * 
 ******************************************************************************/

#include "indicator_led_control_system.h"
#include "message_services.h"
#include "configuration.h"
#include "can.h"

/****************************************************************************** 
 *                                                                            * 
 *                              Global Variables                              * 
 *                                                                            * 
 ******************************************************************************/

/* Flag to make sure token is being sent to others */
bool g_SendToken = false;

/* Flag to make sure node has token */
bool g_HasToken = NODE_INITIAL_TOKEN_STATE;

/* Indicator LED default color without having token */
static uint8_t g_Default_Color = NODE_DEFAULT_COLOR;

/* Received SW1 container. */
static bool g_SW1_Received = false;

/* Received SW2 container. */
static bool g_SW2_Received = false;

/* Received previous node container. */
static uint8_t g_PrevNodeID = NODE_ID;

/******************************************************************************
 * Name         : IndLEDCtrlSys_ReceiveMessage                                *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Receives message.                                           *
 ******************************************************************************/
void IndLEDCtrlSys_ReceiveMessage(void)
{
    /* Check CAN RX Flag. */
    if (true == g_CANRXFlag)
    {
        /* Receive byte from CAN. */
        CAN_ReceiveByte();

        /* Extract CAN message. */
        MessageServices_Extract(g_rxCAN);

        /* Check ID */
        if ((IND_LED_MSG_ID == g_Message.MsgID) &&
            (NODE_ID != g_Message.NodeID))
        {
            /* Update switch #1 Flag. */
            g_SW1_Received = g_Message.SW1;

            /* Update switch #2 Flag. */
            g_SW2_Received = g_Message.SW2;

            /* Update Has Token Flag. */
            g_HasToken = g_Message.IsToken;

            /* Update previous ID. */
            g_PrevNodeID = g_Message.NodeID;
        }
        else
        {
            /* MISRA */
        }
    }
}

/******************************************************************************
 * Name         : IndLEDCtrlSys_TransmitMessage                               *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Transmits message.                                          *
 ******************************************************************************/
void IndLEDCtrlSys_TransmitMessage(void)
{
    /* Check if token is being sent. */
    if (true == g_SendToken)
    {
        /* Compress message. */
        MessageServices_Compress(&g_txCAN, IND_LED_MSG_ID);

        /* Transmit message over CAN. */
        CAN_TransmitByte();
    }
    else if ((true == g_HasToken) &&
            ((IS_NOT_PRESSED == g_SW1_Status) ||
             (IS_NOT_PRESSED == g_SW2_Status)))
    {
        /* Update button status for message. */
        IndLEDCtrlSys_UpdateButtonStatus();

        /* Compress message. */
        MessageServices_Compress(&g_txCAN, IND_LED_MSG_ID);

        /* Send over CAN. */
        CAN_TransmitByte();
    }
    else
    {
        /* MISRA */
    }
}

/******************************************************************************
 * Name         : IndLEDCtrlSys_UpdateDefaultColor                            *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Updates default ECU indicator LED color.                    *
 ******************************************************************************/
void IndLEDCtrlSys_UpdateDefaultColor(void)
{
    /* Check if ECU has token. */
    if (true == g_HasToken)
    {
        /* Check if SW1 is pressed. */
        if (IS_PRESSED == g_SW1_Status)
        {   
            /* Set default color to start. */
            g_Default_Color = color[START];
        }
        else if (IS_PRESSED == g_SW2_Status)
        {
            /* Set default color to end (reversed). */
            g_Default_Color = color[END];
        }
        else
        {
            /* MISRA */
        }
    }
	else /* NO TOKEN */
	{
        if ((true == g_SW1_Received) && (true == g_SW2_Received))
        {
            /* DO NOTHING */
        }
        else /* AT LEAST ONE SWITCH IS PRESSED */
        {
            /* Check if switch 1 is pressed. */
            if (true == g_SW1_Received)
            {
                /* Set new default color. */
                g_Default_Color = state[NODE_ID][g_PrevNodeID];
            }
            /* Check if switch 2 is pressed. */
            else if (true == g_SW2_Received)
            {
                /* Set new default color (reversed). */
                g_Default_Color = state[NODE_ID][(g_PrevNodeID + MAP) % COUNT];
            }
            else /* NOTHING IS PRESSED */
            {
                /* MISRA */
            }
        }
	}
}

/******************************************************************************
 * Name         : IndLEDCtrlSys_TokenTimeout                                  *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Clears the token if and only if we have a valid token.      *
 ******************************************************************************/
void IndLEDCtrlSys_TokenTimeout(void)
{
/* Static counter for timeout */
static volatile uint16_t Counter = INITIALIZED_TO_ZERO;

    /* Check if ECU has token. */
	if (true == g_HasToken)
	{
        /* Increment counter by 1. */
		++Counter;

        /* Check timeout. */
        if (TOKEN_TIMEOUT == Counter)
        {
            /* Reset counter. */
            Counter = INITIALIZED_TO_ZERO;
            
            /* Remove token from ECU as it is passed to other. */
            g_HasToken = false;
            
            /* Enable sending token. */
            g_SendToken = true;
        }
	}
    else
    {
        /* MISRA */
    }
}

/******************************************************************************
 * Name         : IndLEDCtrlSys_UpdateIndLED                                  *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Update indicator LED color depending on token.              *
 ******************************************************************************/
void IndLEDCtrlSys_UpdateIndLED(void)
{
    /* Check if ECU has token. */
	if (true == g_HasToken)
	{
        /* Set indicator LED color (white). */
		IndicatorLED_SetColor(COLOR_WHITE);
	}
	else
	{
        /* Set indicator LED color. */
		IndicatorLED_SetColor(g_Default_Color);
	}
}

/******************************************************************************
 * Name         : IndLEDCtrlSys_UpdateButtonStatus                            *
 * Inputs       : None                                                        *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Update global variables for TiVA-c switches.                *
 ******************************************************************************/
void IndLEDCtrlSys_UpdateButtonStatus(void)
{
    /* Update switch 1 readings. */
    Button_UpdateStatus(SW1_CH, &g_SW1_Status);
    
    /* Update switch 2 readings. */
	Button_UpdateStatus(SW2_CH, &g_SW2_Status);
}

