/***************************************************************************//**
 * @file VL53L1X.c
 * @brief Code for the VL53L1X sensor.
 * @version 1.0
 * @author by Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Initial version
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
 *   Some methods also use code obtained from examples from [Silicon Labs' GitHub](https://github.com/SiliconLabs/peripheral_examples).
 *   These sections are licensed under the Silabs License Agreement. See the file
 *   "Silabs_License_Agreement.txt" for details. Before using this software for
 *   any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#include <stdint.h>        /* (u)intXX_t */
#include <stdbool.h>       /* "bool", "true", "false" */

#include "debug_dbprint.h" /* Enable or disable printing to UART for debugging */
#include "delay.h"         /* Delay functionality */
#include "i2c.h"           /* I2C initialization */
#include "VL53L1X_api.h"   /* VL53L1X API */


/* Local variables */
int16_t offset; /* Calibration value */
uint16_t xtalk; /* Calibration value */


/**************************************************************************//**
 * @brief
 *   Initialize the sensor.
 *
 * @details
 *   This method wait until the sensor is booted, initializes it and
 *   gets offset values.
 *
 * @return
 *   @return
 *   @li `0`  - Calibration successful.
 *   @li `-1` - Calibration failed.
 *****************************************************************************/
int8_t initVL53L1X (void)
{
	/* Returned status */
	int8_t status;

	/* Wait for device booted */
	uint8_t bootState = 0;
	uint8_t exitWhile = 0;

	while ((bootState != 1) && (exitWhile < 5))
	{
		status = VL53L1X_BootState(0x52, &bootState);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		if (status != 0) dbcritInt("VL53L1X_BootState status = ", status, "");
		dbinfoInt("VL53L1X_BootState = ", bootState, "");
#endif /* DEBUG_DBPRINT */

		/* 1s delay */
		delay(1000);

		/* Functionality so we don't end up forever in this loop */
		exitWhile++;
	}

	/* Initialize sensor */
	status = VL53L1X_SensorInit(0x52);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_SensorInit status = ", status, "");
#endif /* DEBUG_DBPRINT */

	/* Get offset */
	status = VL53L1X_GetOffset(0x52, &offset);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_GetOffset status = ", status, "");
	dbwarnInt("VL53L1X_GetOffset = ", offset, " mm");
#endif /* DEBUG_DBPRINT */

	/* Get Xtalk */
	status = VL53L1X_GetXtalk(0x52, &xtalk);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_GetXtalk status = ", status, "");
	dbwarnInt("VL53L1X_GetXtalk = ", xtalk, " cps");
#endif /* DEBUG_DBPRINT */

	/* Configure distance mode to short (1.3m), better ambient immunity */
	status = VL53L1X_SetDistanceMode(0x52, 2); /* default = long (4m in the dark with 200 ms timing budget) */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
#if DBPRINT_VERBOSE == 1 /* DBPRINT_VERBOSE */
	if (status != 0) dbcritInt("VL53L1X_SetDistanceMode status = ", status, "");
#endif /* DBPRINT_VERBOSE */
#endif /* DEBUG_DBPRINT */

	/* Configure inter-measurement period to 500 ms (IMP, has to be the same or greater than the timing budget) */
	status = VL53L1X_SetInterMeasurementInMs(0x52, 500); /* default = 100 ms */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_SetInterMeasurementInMs status = ", status, "");
#endif /* DEBUG_DBPRINT */

	/* Configure timing budget to 200 ms */
	status = VL53L1X_SetTimingBudgetInMs(0x52, 200); /* default = 100 ms */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_SetTimingBudgetInMs status = ", status, "");
#endif /* DEBUG_DBPRINT */

	/* Get sensor ID */
	uint16_t id; // must be 0xEEAC ??
	status = VL53L1X_GetSensorId(0x52, &id);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_GetSensorId status = ", status, "");
	dbinfoInt_hex("VL53L1X_GetSensorId = ", id, "");
#endif /* DEBUG_DBPRINT */

	return (status);
}


/**************************************************************************//**
 * @brief
 *   Get a sensor reading.
 *
 * @return
 *   The measured distance in mm.
 *****************************************************************************/
uint16_t measureVL53L1X (void)
{
	/* Start ranging */
	int8_t status = VL53L1X_StartRanging(0x52);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_StartRanging status = ", status, "");
#endif /* DEBUG_DBPRINT */

	uint8_t dataReady;
	uint16_t distance;

	/* Wait for data ready */
	while (dataReady != 1)
	{
		status = VL53L1X_CheckForDataReady(0x52, &dataReady);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		if (status != 0) dbcritInt("VL53L1X_CheckForDataReady status = ", status, "");
#endif /* DEBUG_DBPRINT */

	}

	/* Get range status */
	uint8_t state;
	status = VL53L1X_GetRangeStatus(0x52, &state);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_GetRangeStatus status = ", status, "");
	if (state != 0) dbcritInt("VL53L1X_GetRangeStatus = ", state, "");
#endif /* DEBUG_DBPRINT */

	/* Get distance */
	status = VL53L1X_GetDistance(0x52, &distance);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_GetDistance status = ", status, "");
#endif /* DEBUG_DBPRINT */

	/* Clear interrupt */
	status = VL53L1X_ClearInterrupt(0x52);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	if (status != 0) dbcritInt("VL53L1X_ClearInterrupt status = ", status, "");
#endif /* DEBUG_DBPRINT */

	return (distance);
}
