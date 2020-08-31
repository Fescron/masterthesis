/***************************************************************************//**
 * @file interrupt.c
 * @brief Interrupt functionality.
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
#include "em_device.h"     /* Include necessary MCU-specific header file */
#include "em_cmu.h"        /* Clock management unit */
#include "em_gpio.h"       /* General Purpose IO */
#include "em_rtc.h"        /* Real Time Counter (RTC) */

#include "interrupt.h"     /* Corresponding header file */
#include "pin_mapping.h"   /* PORT and PIN definitions */
#include "debug_dbprint.h" /* Enable or disable printing to UART */
#include "util.h"     	   /* Utility functionality */


/* Local variables */
volatile bool BTN_triggered = false; /* Volatile because it's modified by an interrupt service routine */
volatile bool PULSE0_triggered = false;
volatile bool PULSE1_triggered = false;


/**************************************************************************//**
 * @brief
 *   Initialize GPIO wake-up functionality.
 *
 * @details
 *   Initialize falling-edge interrupts.
 *****************************************************************************/
void initGPIOwakeup (void)
{
	/* Enable necessary clocks (just in case) */
	CMU_ClockEnable(cmuClock_HFPER, true); /* GPIO is a High Frequency Peripheral */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Configure inputs (external pull-up-resistors), the last argument enables the filter */
	GPIO_PinModeSet(BTN_PORT, BTN_PIN, gpioModeInput, 1);
	GPIO_PinModeSet(PULSE0_PORT, PULSE0_PIN, gpioModeInput, 1);
	GPIO_PinModeSet(PULSE1_PORT, PULSE1_PIN, gpioModeInput, 1);

	/* Clear all odd pin interrupt flags (just in case)
	 * NVIC_ClearPendingIRQ(GPIO_ODD_IRQn); would also work but is less "readable" */
	GPIO_IntClear(0xAAAA);

	/* Clear all even pin interrupt flags (just in case)
	 * NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn); would also work but is less "readable" */
	GPIO_IntClear(0x5555);

	/* All pending interrupts can be cleared with GPIO_IntClear(0xFFFF); */

	/* Enable IRQ for even numbered GPIO pins */
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);

	/* Enable IRQ for odd numbered GPIO pins */
	NVIC_EnableIRQ(GPIO_ODD_IRQn);

	/* Enable falling-edge interrupts */
	GPIO_ExtIntConfig(BTN_PORT, BTN_PIN, BTN_PIN, false, true, true);
	GPIO_ExtIntConfig(PULSE0_PORT, PULSE0_PIN, PULSE0_PIN, false, true, true);
	GPIO_ExtIntConfig(PULSE1_PORT, PULSE1_PIN, PULSE1_PIN, false, true, true);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("GPIO wake-up initialized");
#endif /* DEBUG_DBPRINT */

}


/**************************************************************************//**
 * @brief
 *   Getter for the `BTN_triggered` variable.
 *
 * @return
 *   The value of `BTN_triggered`.
 *****************************************************************************/
bool BTN_getTriggered (void)
{
	return (BTN_triggered);
}


/**************************************************************************//**
 * @brief
 *   Setter for the `BTN_triggered` variable.
 *
 * @param[in] value
 *   The boolean value to set to the selected variable.
 *****************************************************************************/
void BTN_setTriggered (bool value)
{
	BTN_triggered = value;
}


/**************************************************************************//**
 * @brief
 *   Getter for the `PULSE0/1_triggered` variable.
 *
 * @param[in] number
 *   @li `0` - PULSE0 selected.
 *   @li `1` - PULSE1 selected.
 *
 * @return
 *   The value of `PULSE0/1_triggered`.
 *****************************************************************************/
bool PULSE_getTriggered (uint8_t number)
{
	if (number == 0) return (PULSE0_triggered);
	else if (number == 1) return (PULSE1_triggered);

	return (false);
}


/**************************************************************************//**
 * @brief
 *   Setter for the `PULSE0/1_triggered` variable.
 *
 * @param[in] number
 *   @li `0` - PULSE0 selected.
 *   @li `1` - PULSE1 selected.
 *
 * @param[in] value
 *   The boolean value to set to the selected variable.
 *****************************************************************************/
void PULSE_setTriggered (uint8_t number, bool value)
{
	if (number == 0) PULSE0_triggered = value;
	else if (number == 1) PULSE1_triggered = value;
}


/**************************************************************************//**
 * @brief
 *   GPIO Even IRQ for even-numbered pins.
 *
 * @details
 *   The RTC is also disabled on a button press (*manual wake-up*)
 *
 * @note
 *   The *weak* definition for this method is located in `system_efm32hg.h`.
 *****************************************************************************/
void GPIO_EVEN_IRQHandler (void) // TODO
{
	/* Read interrupt flags */
	uint32_t flags = GPIO_IntGet();

	/* Check if BTN is pushed */
	if (flags == 0x0004)
	{
		/* Disable the counter (manual wakeup) */
		RTC_Enable(false);

		BTN_triggered = true;
	}

	/* Check if P2 (PULSE1) is triggered */
	if (flags == 0x4000) PULSE1_triggered = true;

	/* Clear all even pin interrupt flags */
	GPIO_IntClear(0x5555);
}


/**************************************************************************//**
 * @brief
 *   GPIO Odd IRQ for odd-numbered pins.
 *
 * @note
 *   The *weak* definition for this method is located in `system_efm32hg.h`.
 *****************************************************************************/
void GPIO_ODD_IRQHandler (void) // TODO
{
	/* Read interrupt flags */
	uint32_t flags = GPIO_IntGet();

	/* Check if P1 (PULSE0) is triggered */
	if (flags == 0x2000) PULSE0_triggered = true;

	/* Clear all odd pin interrupt flags */
	GPIO_IntClear(0xAAAA);
}
