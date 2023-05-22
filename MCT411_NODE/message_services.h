/******************************************************************************
 * Module      : Indicator Led Control System                                 *
 * File Name   : indicator_led_control_system.h                               *
 * Description : Header file for indicator_led_control_system module          *
 * Created on  : Mar 26, 2020                                                 *
 ******************************************************************************/

#ifndef MESSAGE_SERVICES_H_
#define MESSAGE_SERVICES_H_

#include <stdint.h>
#include <stdbool.h>
#include "indicator_led_control_system.h"
#include "configuration.h"

/******************************************************************************
 *                                                                            *
 *                                Data-types                                  *
 *                                                                            *
 ******************************************************************************/

/* Indicator Message data-type */
typedef struct
{
    uint8_t MsgID;          /* Message ID */
    uint8_t NodeID;         /* Node ID */
    bool IsToken;           /* Token flag */
    bool SW1;               /* SW1 pressed flag */
    bool SW2;               /* SW2 pressed flag */
} Message;

extern Message g_Message;

/******************************************************************************
 *                                                                            *
 *                                Definitions                                 *
 *                                                                            *
 ******************************************************************************/

/* Messages Parameters */
#define IND_LED_MSG_ID  ( 0 )
#define DISTANCE_MSG_ID ( 1 )

/* Indicator Message Bits */
#define DISTANCE_BITS   ( (1U << 0) | (1U << 1) | (1U << 2) )
#define NODE_ID_BITS    ( (1U << 0) | (1U << 1) )
#define TOKEN_BIT       ( (1U << 2) )
#define SW1_BIT         ( (1U << 3) )
#define SW2_BIT         ( (1U << 4) )
#define MSG_ID_BIT      ( (1U << 7) )

/******************************************************************************
 *                                                                            *
 *                            Function Prototypes                             *
 *                                                                            *
 ******************************************************************************/

/* Compress message to be sent as a byte. */
extern void MessageServices_Compress(uint8_t *buffer, uint8_t msg_id);

/* Extract data from a message. */
extern void MessageServices_Extract(uint8_t buffer);


#endif /* MESSAGE_SERVICES_H_ */
