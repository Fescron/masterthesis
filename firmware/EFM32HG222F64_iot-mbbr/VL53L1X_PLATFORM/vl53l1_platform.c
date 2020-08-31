/***************************************************************************//**
 * @file vl53l1_platform.c
 * @brief Platform-specific implementation for using the VL53L1X API on the EFM32HG322.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0:
 *
 * ******************************************************************************
 *
 * @section License
 *
 *   **Copyright (C) 2019 - Brecht Van Eeckhoudt**
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
 *   @n
 *
 *   **This file is part of VL53L1 Platform**, the method names remained but
 *   they were filled in with code by Brecht Van Eeckhoudt.
 *
 *   **Copyright (c) 2016, STMicroelectronics - All Rights Reserved**
 *
 *   License terms: BSD 3-clause "New" or "Revised" License.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 *   3. Neither the name of the copyright holder nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/


#include "vl53l1_platform.h"
#include <string.h>
#include <time.h>
#include <math.h>

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"

#include "debug_dbprint.h"
#include "i2c.h"           /* I2C initialisation */


/**************************************************************************//**
 * @brief
 *   This method is not used by the API and thereby not implemented.
 *****************************************************************************/
int8_t VL53L1_WriteMulti( uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count)
{
	/* Not used */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbcrit("Method not implemented since it doesn't seem to be used!");
#endif /* DEBUG_DBPRINT */

	return (0);
}


/**************************************************************************//**
 * @brief
 *   TODO
 *
 * @details
 *   This method also initializes i2C if necessary.@n
 *   This method is only used in `VL53L1X_GetResult`.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] pdata
 *   Pointer to the data (`uint8_t`) to put the read bytes in.
 *
 * @param[in] count
 *   Counter (`uint32_t`).
 *
 * @return
 *   @li `0`  - TODO
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_ReadMulti (uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbcrit("Not yet implemented!");
#endif /* DEBUG_DBPRINT */

	return (0); // to be implemented
}


/**************************************************************************//**
 * @brief
 *   Write a byte (8 bits) to the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   The data (`uint8_t`) to put on the I2C bus.
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
int8_t VL53L1_WrByte (uint16_t dev, uint16_t index, uint8_t data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Separate data in bytes */
	uint8_t data_buf[1] = {data};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_WRITE; /* Data written from buf[0].data and buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data_buf;
	i2cTransfer.buf[1].len    = 1; /* Data itself is one byte */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Write a word (16 bits) to the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   The data (`uint16_t`) to put on the I2C bus.
 *
 * @return
 *   @li `0`  - Word written correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_WrWord (uint16_t dev, uint16_t index, uint16_t data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Separate data in bytes */
	uint8_t data_buf[2] = {((data & 0xFF00) >> 8), (data & 0x00FF)};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_WRITE; /* Data written from buf[0].data and buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data_buf;
	i2cTransfer.buf[1].len    = 2; /* Data itself is two byte */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Write a double word (32 bits) to the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   The data (`uint32_t`) to put on the I2C bus.
 *
 * @return
 *   @li `0`  - Double word written correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_WrDWord (uint16_t dev, uint16_t index, uint32_t data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Separate data in bytes */
	uint8_t data_buf[4] = {((data & 0xFF000000) >> 24), ((data & 0xFF0000) >> 16), ((data & 0xFF00) >> 8), (data & 0x00FF)};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_WRITE; /* Data written from buf[0].data and buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data_buf;
	i2cTransfer.buf[1].len    = 4; /* Data itself is four byte */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Read a byte (8 bits) from the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   Pointer to the data (`uint8_t`) to put the read byte in.
 *
 * @return
 *   @li `0`  - Byte read correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_RdByte (uint16_t dev, uint16_t index, uint8_t *data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_READ; /* Data written from buf[0].data and read into buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data;
	i2cTransfer.buf[1].len    = 1; /* Data itself is one byte */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Read a word (16 bits) from the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   Pointer to the data (`uint16_t`) to put the read word in.
 *
 * @return
 *   @li `0`  - Word read correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_RdWord (uint16_t dev, uint16_t index, uint16_t *data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Create buffer for received bytes */
	uint8_t data_buf[2] = {0, 0};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_READ; /* Data written from buf[0].data and read into buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data_buf;
	i2cTransfer.buf[1].len    = 2; /* Data itself is two bytes */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	/* Store received bytes correctly in given data location */
	(*data) = ((uint16_t)data_buf[0] << 8) | data_buf[1];

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Read a double word (32 bits) from the I2C bus.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] dev
 *   Device ID (`uint16_t`).
 *
 * @param[in] index
 *   Index (`uint16_t`).
 *
 * @param[in] data
 *   Pointer to the data (`uint32_t`) to put the read double word in.
 *
 * @return
 *   @li `0`  - Double word read correctly.
 *   @li `-1` - `i2cTransferNack`, NACK received during transfer.
 *   @li `-2` - `i2cTransferBusErr`, Bus error during transfer (misplaced START/STOP).
 *   @li `-3` - `i2cTransferArbLost`, Arbitration lost during transfer.
 *   @li `-4` - `i2cTransferUsageFault`, Usage fault.
 *   @li `-5` - `i2cTransferSwFault`, SW fault.
 *   @li `-6` - Coudldn't configure I2C.
 *****************************************************************************/
int8_t VL53L1_RdDWord (uint16_t dev, uint16_t index, uint32_t *data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate index in two bytes (ANDing with a mask and shifting one byte (8 bits) per position) */
	uint8_t index_buf[2] = {((index & 0xFF00) >> 8), (index & 0x00FF)};

	/* Create buffer for received bytes */
	uint8_t data_buf[4] = {0, 0, 0, 0};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = dev;
	i2cTransfer.flags         = I2C_FLAG_WRITE_READ; /* Data written from buf[0].data and read into buf[1].data */
	i2cTransfer.buf[0].data   = index_buf;
	i2cTransfer.buf[0].len    = 2; /* Index is two bytes */
	i2cTransfer.buf[1].data   = data_buf;
	i2cTransfer.buf[1].len    = 4; /* Data itself is four bytes */
	result = I2C_TransferInit(I2C0, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(I2C0);

	/* Store received bytes correctly in given data location */
	(*data) = ((uint32_t)data_buf[0] << 24) | ((uint32_t)data_buf[1] << 16) | ((uint32_t)data_buf[2] << 8) | data_buf[3];

	return (result);
}


/**************************************************************************//**
 * @brief
 *   This method is not used by the API and thereby not implemented.
 *****************************************************************************/
int8_t VL53L1_WaitMs (uint16_t dev, int32_t wait_ms)
{
	/* Not used */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbcrit("Method not implemented since it doesn't seem to be used!");
#endif /* DEBUG_DBPRINT */

	return (0);
}
