/***************************************************************************//**
 * @file SHT30.c
 * @brief SHT30 functionality.
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

#include "SHT30.h"         /* Corresponding header file */
#include "debug_dbprint.h" /* Enable or disable printing to UART */
#include "pin_mapping.h"   /* PORT and PIN definitions */
#include "i2c.h"           /* I2C initialization */
#include "delay.h"         /* Delay functionality */


/* Local definitions */
#define SHT30_ADDRESS 0x44 /* (7 bit notation) */

/* Sensor commands */
#define SOFT_RESET_CMD 0x30A2
#define HIGH_REP_MEAS_CMD 0x2400 /* High repeatablility, no clock stretching */
#define SEND_MEASUREMENT_COMMAND 0x2C
#define HIGH_REPEATABILITY_COMMAND 0x06


/* Local variables */
bool SHT30_reset = false;


/**************************************************************************//**
 * @brief
 *   Soft reset the SHT30.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *
 * @return
 *   @return
 *   @li `0`  - Byte written correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t softResetSHT30 (void)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate command in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t cmd_buf[2] = {(SOFT_RESET_CMD >> 8), (SOFT_RESET_CMD & 0x00FF)};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = SHT30_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = cmd_buf;
	i2cTransfer.buf[0].len    = 2; /* Command is two bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("Soft reset SHT30");
#endif /* DEBUG_DBPRINT */

	/* Indicate that SHT30 has been soft reset */
	SHT30_reset = true;

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Do I2C transfers to get the temperature from the SHT30.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @return
 *   The temperature (*1000).
 *****************************************************************************/
int32_t SHT30_readTemp (void)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate command in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t cmd_buf[2] = {(HIGH_REP_MEAS_CMD >> 8), (HIGH_REP_MEAS_CMD & 0x00FF)};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Create buffer for received bytes */
	uint8_t data_buf[6] = {0, 0, 0, 0, 0, 0};

	// data_buf[6] = cTemp msb, cTemp lsb, cTemp crc, humidity msb, humidity lsb, humidity crc
	// float cTemp = ((((data_buf[0] * 256.0) + data_buf[1]) * 175) / 65535.0) - 45;
	// float humidity = ((((data_buf[3] * 256.0) + data_buf[4]) * 100) / 65535.0);

	/* Initializing I2C transfer */
	i2cTransfer.addr          = SHT30_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = cmd_buf;
	i2cTransfer.buf[0].len    = 2; /* Command is two bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	delay(10);

	/* Initializing I2C transfer */
	i2cTransfer.flags         = I2C_FLAG_READ; /* Data read into buf[0].data */
	i2cTransfer.buf[0].data   = data_buf;
	i2cTransfer.buf[0].len    = 6; /* Data itself is 6 bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return ((int32_t)((((((data_buf[0] * 256.0) + data_buf[1]) * 175) / 65535.0) - 45) * 1000));
}
