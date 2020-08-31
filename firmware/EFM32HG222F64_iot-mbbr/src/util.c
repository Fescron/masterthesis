/***************************************************************************//**
 * @file util.c
 * @brief Utility functionality.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version.
 *
 * ******************************************************************************
 *
 * @section License
 *
 *   **Copyright (C) 2020 - Brecht Van Eeckhoudt**
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the **GNU General Public License** as published by
 *   the Free Software Foundation, either **version 3** of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   *A copy of the GNU General Public License can be found in the `LICENSE`
 *   file along with this source code.*
 *
 *   @n
 *
 *   Some methods use code obtained from examples from [Silicon Labs' GitHub](https://github.com/SiliconLabs/peripheral_examples).
 *   These sections are licensed under the Silabs License Agreement. See the file
 *   "Silabs_License_Agreement.txt" for details. Before using this software for
 *   any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#include <stdint.h>        /* (u)intXX_t */
#include <stdbool.h>       /* "bool", "true", "false" */
#include "em_cmu.h"        /* Clock Management Unit */
#include "em_gpio.h"       /* General Purpose IO */

#include "util.h"          /* Corresponding header file */
#include "pin_mapping.h"   /* PORT and PIN definitions */
#include "debug_dbprint.h" /* Enable or disable printing to UART */
#include "delay.h"         /* Delay functionality */

#if ERROR_FORWARDING == 1 /* ERROR_FORWARDING */
//#include "lora_wrappers.h" /* LoRaWAN functionality */
#endif /* ERROR_FORWARDING */


/* Local variables */
uint8_t errorNumber = 0;
bool GNDd_initialized = false;


/* Local prototype */
static void initGNDd (void);


/**************************************************************************//**
 * @brief
 *   Enable or disable the GNDd pin.
 *
 * @details
 *   This method also initializes the pin-mode if necessary.
 *
 * @param[in] enabled
 *   @li `true` - Enable GNDd.
 *   @li `false` - Disable GNDd.
 *****************************************************************************/
void gndd (bool enabled)
{
	/* Initialize GNDd if not already the case */
	if (!GNDd_initialized) initGNDd();

	/* Set the selected state */
	if (enabled) GPIO_PinOutSet(DBG_GNDD_PORT, DBG_GNDD_PIN);
	else GPIO_PinOutClear(DBG_GNDD_PORT, DBG_GNDD_PIN);
}


/**************************************************************************//**
 * @brief
 *   Error method.
 *
 * @details
 *   **ERROR_FORWARDING == 0**@n
 *   The method flashes the LED, displays a UART message and holds the MCU
 *   forever in a loop until it gets reset. The error value gets stored in
 *   a global variable.
 *
 *   **ERROR_FORWARDING == 1**@n
 *   The method sends the error value to the cloud using LoRaWAN if the error
 *   number doesn't correspond to LoRaWAN-related functionality (numbers 30 - 55).
 *
 * @param[in] number
 *   The number to indicate where in the code the error was thrown.
 *****************************************************************************/
void error (uint8_t number)
{
	/* Initialize GNDd if not already the case */
	if (!GNDd_initialized) initGNDd();

	/* Save the given number in the global variable */
	errorNumber = number;

#if ERROR_FORWARDING == 0 /* ERROR_FORWARDING */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbprint_color(">>> Error (", 5);
	dbprintInt(number);
	dbprintln_color(")! Please reset MCU. <<<", 5);
#endif /* DEBUG_DBPRINT */

	while (1)
	{
		/* Nothing here */
	}

#else /* ERROR_FORWARDING */

	/* Check if the error number isn't called in BG96 functionality */
	if ((number < 30) || (number > 55))
	{
#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprint_color(">>> Error (", 5);
		dbprintInt(number);
		dbprintln_color(")! Sending the message to the cloud. <<<", 5);
#endif /* DEBUG_DBPRINT */

//		initLoRaWAN(); /* Initialize LoRaWAN functionality */
//
//		sendStatus(number); /* Send the status value */
//
//		disableLoRaWAN(); /* Disable RN2483 */
	}
	else
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprint_color(">>> Error in BG96 functionality (", 5);
		dbprintInt(number);
		dbprintln_color(")! <<<", 5);
#endif /* DEBUG_DBPRINT */

	}

#endif /* ERROR_FORWARDING */

}


/**************************************************************************//**
 * @brief
 *   Initialize the initGNDd pin.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *****************************************************************************/
static void initGNDd (void)
{
	/* Enable necessary clocks (just in case) */
	CMU_ClockEnable(cmuClock_HFPER, true); /* GPIO is a High Frequency Peripheral */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* In the case of gpioModePushPull, the last argument directly sets the pin state */
	GPIO_PinModeSet(DBG_GNDD_PORT, DBG_GNDD_PIN, gpioModePushPull, 0);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("GNDd pin initialized");
#endif /* DEBUG_DBPRINT */

	GNDd_initialized = true;
}