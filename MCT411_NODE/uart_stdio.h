#ifndef UART_STDIO_H_
#define UART_STDIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

/****************************************************************************** 
 *                                                                            * 
 *                               Configuration                                * 
 *                                                                            * 
 ******************************************************************************/

/* Baud Rate */
#define UART_BAUDRATE   (115200)

/* Empty byte */
#define UART_EMPTY_BYTE (0)

/****************************************************************************** 
 *                                                                            * 
 *                              Shared Variables                              * 
 *                                                                            * 
 ******************************************************************************/

/* UART available flag */
extern bool g_UART_available;

/****************************************************************************** 
 *                                                                            * 
 *                            Function Prototypes                             * 
 *                                                                            * 
 ******************************************************************************/

/* Initializes UART */
extern void UART_Init(void);

/* Prints string to console */
extern void UART_printf(const char *);

/* Receives byte */
extern char UART_ReceiveByte(void);


#endif /* UART_STDIO_H_ */
