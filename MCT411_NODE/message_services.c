#include "message_services.h"

/******************************************************************************
 *                                                                            *
 *                              Global Variables                              *
 *                                                                            *
 ******************************************************************************/

/* Message container */
Message g_Message;

/******************************************************************************
 * Name         : ExtractIndicatorMessage                                     *
 * Inputs       : g_IndMsg, buffer                                            *
 * Outputs      : None                                                        *
 * Return Value : None                                                        *
 * Description  : Extract data from a message.                                *
 ******************************************************************************/
void MessageServices_Extract(uint8_t buffer)
{
    /* Check message type. */
    if (IND_LED_MSG_ID == (buffer & MSG_ID_BIT))
    {
        /* Set Message ID. */
        g_Message.MsgID = IND_LED_MSG_ID;

        /* Get NodeID. */
        g_Message.NodeID = (buffer & NODE_ID_BITS);

        /* Check if token bit is set. */
        if ((buffer & TOKEN_BIT) && (g_Message.NodeID == NODE_ID_PREV))
        {
            g_Message.IsToken = true;       /* Set token flag. */
        }
        else /* TOKEN_BIT IS CLEARED */
        {
            g_Message.IsToken = false;      /* Clear token flag. */
        }

        /* Check if switch 1 bit is set. */
        if (buffer & SW1_BIT)
        {
            g_Message.SW1 = true;           /* Set switch #1 flag. */
        }
        else /* SW1_BIT IS CLEARED */
        {
            g_Message.SW1 = false;          /* Clear switch #1 flag. */
        }

        /* Check if switch 2 bit is set. */
        if (buffer & SW2_BIT)
        {
            g_Message.SW2 = true;           /* Set switch #2 flag. */
        }
        else /* CLEARED */
        {
            g_Message.SW2 = false;          /* Clear switch #2 flag. */
        }
    }
}

/******************************************************************************
 * Name         : MessageServices_Compress                                    *
 * Inputs       : msg_id                                                      *
 * Outputs      : buffer                                                      *
 * Return Value : None                                                        *
 * Description  : Compress message to be sent as a byte.                      *
 ******************************************************************************/
void MessageServices_Compress(uint8_t *buffer, uint8_t msg_id)
{
uint8_t message = 0;            /* Compressed message holder */

    /* Check message type. */
    if (IND_LED_MSG_ID == msg_id)
    {
        /* Copy NODE_ID to message. */
        message |= (NODE_ID & NODE_ID_BITS);

        /* Check if token can be sent. */
        if (true == g_SendToken)
        {
            /* Clear send token flag. */
            g_SendToken = false;

            /* Set token bit. */
            message |= TOKEN_BIT;
        }
        else if (IS_PRESSED == g_SW1_Status)
        {
            /* Set SW1 bit. */
            message |= SW1_BIT;
        }
        else if (IS_PRESSED == g_SW2_Status)
        {
            /* Set SW2 bit. */
            message |= SW2_BIT;
        }
        else
        {
            /* MISRA */
        }

        /* Select message ID. */
        message &= ~MSG_ID_BIT;

        /* Copy message to buffer. */
        *buffer = message;
    }
}
