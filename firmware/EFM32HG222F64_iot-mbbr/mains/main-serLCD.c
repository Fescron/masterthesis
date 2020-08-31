/***************************************************************************//**
 * @file
 * @brief Simple LED Blink Demo for SLSTK3400A_EFM32HG
 * @version 5.6.1
 *******************************************************************************
 * # License
 * <b>Copyright 2015 Silicon Labs, Inc. http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include "em_device.h"
#include <stdint.h>
#include "em_chip.h"
#include "em_cmu.h"

#include "delay.h"
#include "serlcd.h"

#include "debug_dbprint.h" /* Enable or disable printing to UART */



/***************************************************************************//**
 * @brief  Main function
 ******************************************************************************/
int main(void)
{
	/* Chip errata */
	CHIP_Init();

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbprint_INIT(USART0, 2, false, false); /* Initialize dbprint */
#endif /* DEBUG_DBPRINT */

	/* Init delay logic */
	delay(0);

	/* Clear the LCD */
	int8_t status = clearLCD();

	status = writeStringLCD("SENDING TO CLOUD...");
	status = setCursorLCD(1, 2); /* Move to second row, first column */
	status = writeStringLCD("23.00C  Water 23.00C");
	status = setCursorLCD(1, 3); /* Move to third row, first column */
	status = writeStringLCD("Na#1 10  Na#2 10");
	status = setCursorLCD(1, 4); /* Move to fourth row, first column */
	status = writeStringLCD("pH 10    Redox 10");

	while (1)
	{
		heartBeatLCD();
		delay(1000);
	}
}
