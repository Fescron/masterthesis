/***************************************************************************//**
 * @file i2c.c
 * @brief I2C functionality.
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
#include "em_i2c.h"

#include "i2c.h"           /* Corresponding header file */
#include "debug_dbprint.h" /* Enable or disable printing to UART */
#include "pin_mapping.h"   /* PORT and PIN definitions */


/* Local variables */
bool I2C_initialized = false;


/**************************************************************************//**
 * @brief
 *   I2C initialization (if not already initialized).
 *
 * @return
 *   @li `0`  - Initialized correctly.
 *   @li `-1` - Initialization failed.
 *****************************************************************************/
int8_t initI2C (void)
{
	/* Initialize I2C if not already the case */
	if (!I2C_initialized)
	{
		/* Enabling clock to the I2C, GPIO, LE */
		CMU_ClockEnable(cmuClock_I2C0, true);
		CMU_ClockEnable(cmuClock_GPIO, true);
		CMU_ClockEnable(cmuClock_HFLE, true);

		/* Starting LFXO and waiting until it is stable */
		CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

		/* Setup I2C using default settings */
		I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
		/* Use ~400khz SCK */
		i2cInit.freq = I2C_FREQ_FAST_MAX;

		/* Configure GPIO */
		GPIO_PinModeSet(BUS_SDA_PORT, BUS_SDA_PIN, gpioModeWiredAndPullUpFilter, 1);
		GPIO_PinModeSet(BUS_SCL_PORT, BUS_SCL_PIN, gpioModeWiredAndPullUpFilter, 1);

		/* Enable pins at location as specified in datasheet */
		I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
		I2C0->ROUTE = (I2C0->ROUTE & (~_I2C_ROUTE_LOCATION_MASK)) | BUS_I2C_LOC;

		/* Initializing the I2C */
		I2C_Init(I2C0, &i2cInit);

		/* Indicate that I2C is initialized */
		I2C_initialized = true;

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbinfo("I2C initialized.");
#endif /* DEBUG_DBPRINT */

	}

	return (0);
}
