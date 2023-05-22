/****************************************************************************** 
 * Module      : None                                                         * 
 * File Name   : main.c                                                       * 
 * Description : Source file for main                                         * 
 * Created on  : Mar 23, 2020                                                 * 
 ******************************************************************************/

#include <scheduler.h>

int main(void)
{
    Scheduler_Init();           /* Initialize Scheduler */
    Scheduler_Loop();           /* Start Scheduler */
    
	for (;;)
    {
        /* NOT REACHABLE */
	}
}
