/***************************************************************************//**
 * @file serlcd.c
 * @brief Sparkfun serLCD functionality.
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
 *   @n
 *
 *   Code based on: https://github.com/sparkfun/SparkFun_SerLCD_Arduino_Library/blob/master/src/SerLCD.cpp
 *
 * ******************************************************************************
 *
 * @section cheatsheet Command cheat sheet:
 *
 *   ASCII / DEC / HEX
 *   '|'    / 124 / 0x7C - Put into setting mode
 *   Ctrl+c / 3 / 0x03 - Change width to 20
 *   Ctrl+d / 4 / 0x04 - Change width to 16
 *   Ctrl+e / 5 / 0x05 - Change lines to 4
 *   Ctrl+f / 6 / 0x06 - Change lines to 2
 *   Ctrl+g / 7 / 0x07 - Change lines to 1
 *   Ctrl+h / 8 / 0x08 - Software reset of the system
 *   Ctrl+i / 9 / 0x09 - Enable/disable splash screen
 *   Ctrl+j / 10 / 0x0A - Save currently displayed text as splash
 *   Ctrl+k / 11 / 0x0B - Change baud to 2400bps
 *   Ctrl+l / 12 / 0x0C - Change baud to 4800bps
 *   Ctrl+m / 13 / 0x0D - Change baud to 9600bps
 *   Ctrl+n / 14 / 0x0E - Change baud to 14400bps
 *   Ctrl+o / 15 / 0x0F - Change baud to 19200bps
 *   Ctrl+p / 16 / 0x10 - Change baud to 38400bps
 *   Ctrl+q / 17 / 0x11 - Change baud to 57600bps
 *   Ctrl+r / 18 / 0x12 - Change baud to 115200bps
 *   Ctrl+s / 19 / 0x13 - Change baud to 230400bps
 *   Ctrl+t / 20 / 0x14 - Change baud to 460800bps
 *   Ctrl+u / 21 / 0x15 - Change baud to 921600bps
 *   Ctrl+v / 22 / 0x16 - Change baud to 1000000bps
 *   Ctrl+w / 23 / 0x17 - Change baud to 1200bps
 *   Ctrl+x / 24 / 0x18 - Change the contrast. Follow Ctrl+x with number 0 to 255. 120 is default.
 *   Ctrl+y / 25 / 0x19 - Change the TWI address. Follow Ctrl+x with number 0 to 255. 114 (0x72) is default.
 *   Ctrl+z / 26 / 0x1A - Enable/disable ignore RX pin on startup (ignore emergency reset)
 *   '+'    / 43 / 0x2B - Set RGB backlight with three following bytes, 0-255
 *   ','    / 44 / 0x2C - Display current firmware version
 *   '-'    / 45 / 0x2D - Clear display. Move cursor to home position.
 *   '.'    / 46 / 0x2E - Enable system messages (ie, display 'Contrast: 5' when changed)
 *   '/'    / 47 / 0x2F - Disable system messages (ie, don't display 'Contrast: 5' when changed)
 *   '0'    / 48 / 0x30 - Enable splash screen
 *   '1'    / 49 / 0x31 - Disable splash screen
 *          / 128-157 / 0x80-0x9D - Set the primary backlight brightness. 128 = Off, 157 = 100%.
 *          / 158-187 / 0x9E-0xBB - Set the green backlight brightness. 158 = Off, 187 = 100%.
 *          / 188-217 / 0xBC-0xD9 - Set the blue backlight brightness. 188 = Off, 217 = 100%.
 *  		For example, to change the baud rate to 115200 send 124 followed by 18.
 *
 ******************************************************************************/


#include <stdint.h>        /* (u)intXX_t */
#include <stdbool.h>       /* "bool", "true", "false" */
#include "em_device.h"     /* Include necessary MCU-specific header file */
#include "em_cmu.h"        /* Clock management unit */
#include "em_gpio.h"       /* General Purpose IO */
#include "em_i2c.h"

#include "serlcd.h"        /* Corresponding header file */
#include "debug_dbprint.h" /* Enable or disable printing to UART */
#include "pin_mapping.h"   /* PORT and PIN definitions */
#include "i2c.h"           /* I2C initialization */


/* Local definitions */
#define DISPLAY_ADDRESS 0x72 /* This is the default address of the OpenLCD (7 bit notation) */

/* OpenLCD command characters */
#define SPECIAL_COMMAND 254  /* Magic number for sending a special command */
#define SETTING_COMMAND 0x7C /* 124, |, the pipe character: The command to change settings: baud, lines, width, backlight, splash, etc */

/* OpenLCD commands */
#define CLEAR_COMMAND 0x2D					//45, -, the dash character: command to clear and home the display
#define CONTRAST_COMMAND 0x18				//Command to change the contrast setting
#define ADDRESS_COMMAND 0x19				//Command to change the i2c address
#define SET_RGB_COMMAND 0x2B				//43, +, the plus character: command to set backlight RGB value
#define ENABLE_SYSTEM_MESSAGE_DISPLAY 0x2E  //46, ., command to enable system messages being displayed
#define DISABLE_SYSTEM_MESSAGE_DISPLAY 0x2F //47, /, command to disable system messages being displayed
#define ENABLE_SPLASH_DISPLAY 0x30			//48, 0, command to enable splash screen at power on
#define DISABLE_SPLASH_DISPLAY 0x31			//49, 1, command to disable splash screen at power on
#define SAVE_CURRENT_DISPLAY_AS_SPLASH 0x0A //10, Ctrl+j, command to save current text on display as splash

// special commands
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00


/* Local variables */
bool heartBeat = false; /* Heartbeat status (doesn't mean it's enabled or disabled) */


/**************************************************************************//**
 * @brief
 *   Clear the LCD.
 *
 * @details
 *   This method also initializes i2C if necessary.
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
int8_t clearLCD (void)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Put commands in array */
	uint8_t data_buf[2] = {SETTING_COMMAND, CLEAR_COMMAND};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = DISPLAY_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = data_buf;
	i2cTransfer.buf[0].len    = 2; /* Data is two bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Write a character (one byte) to the LCD.
 *
 * @details
 *   This method also initializes i2C if necessary.
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
int8_t writeCharLCD (uint8_t data)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate data in bytes */
	uint8_t data_buf[1] = {data};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = DISPLAY_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = data_buf;
	i2cTransfer.buf[0].len    = 1; /* Data is one byte */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to the LCD.
 *
 * @note
 *   If the input is not a string (ex.: `"Hello world!"`) but a char array,
 *   the input message (array) needs to end with NULL (`"\0"`)!
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] message
 *   The string to print to the LCD.
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
int8_t writeStringLCD (char *message)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Check string length */
	uint8_t length = 0;

	/* Count up until we reach a NULL */
	while (message[length] != '\0') length++;

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = DISPLAY_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = (unsigned char *)message;
	i2cTransfer.buf[0].len    = length; /* Data is one byte */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Set the cursor to a specific location on the LCD.
 *
 * @details
 *   This method also initializes i2C if necessary.
 *
 * @param[in] col
 *   Column (`uint8_t`, MAX = 20).
 *
 * @param[in] row
 *   Row (`uint8_t`, MAX = 4).
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
int8_t setCursorLCD (uint8_t col, uint8_t row)
{
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};

	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate data in bytes */
	uint8_t data_buf[2] = {254, LCD_SETDDRAMADDR | (col-1 + row_offsets[row-1])};

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = DISPLAY_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = data_buf;
	i2cTransfer.buf[0].len    = 2; /* Data is two bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return (result);
}


/**************************************************************************//**
 * @brief
 *   Update the heartbeat icon.
 *
 * @details
 *   This method also initializes i2C if necessary.
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
int8_t heartBeatLCD (void)
{
	/* Initialize I2C if not already the case */
	if (initI2C() != 0) return (-6);

	/* Separate data in bytes */
	uint8_t data_buf[3] = {254, LCD_SETDDRAMADDR | 19 }; /* 19th position on first row */

	/* Fill last location of data_buf according to heartBeat status */
	if (heartBeat) data_buf[2] = '+';
	else data_buf[2] = '*';
	heartBeat = !heartBeat;

	/* Transfer structure */
	I2C_TransferSeq_TypeDef i2cTransfer;
	I2C_TransferReturn_TypeDef result;

	/* Initializing I2C transfer */
	i2cTransfer.addr          = DISPLAY_ADDRESS << 1; /* Left shift so we go to 8 bit notation instead of 7 */
	i2cTransfer.flags         = I2C_FLAG_WRITE; /* Data written from buf[0].data */
	i2cTransfer.buf[0].data   = data_buf;
	i2cTransfer.buf[0].len    = 3; /* Data is two bytes */
	result = I2C_TransferInit(BUS_I2C, &i2cTransfer);

	/* Transmitting I2C data (busy-wait until transfer is complete) */
	while (result == i2cTransferInProgress) result = I2C_Transfer(BUS_I2C);

	return (result);
}



