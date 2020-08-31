/***************************************************************************//**
 * @file BG96_at_driver.h
 * @brief BG96 AT-command driver functionality.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
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


/* Include guards prevent multiple inclusions of the same header */
#ifndef _BG96_AT_DRIVER_H_
#define _BG96_AT_DRIVER_H_


/* Includes necessary for this header file */
#include <stdint.h>    /* (u)intXX_t */
#include <stdbool.h>   /* "bool", "true", "false" */

#include "em_device.h" /* Include necessary MCU-specific header file */
#include "em_gpio.h"   /* General Purpose IO */
#include "datatypes.h" /* Definitions of the custom data-types */


/** Public definition to configure the buffer size. */
#define UART_BUFFER_SIZE 100


/* Public prototypes */
void initBG96 (void);
void sendMeasurements (MeasurementData_t *data);
void sendStatus (int8_t status);
void sendPulse (uint8_t number, uint8_t pulse);
void powerBG96 (void);
void disableEcho (void);
void sendCMD (char *message);
void readResponse (char *buf);
bool waitForResponse (char *response, uint8_t timeout);


#endif /* _BG96_AT_DRIVER_H_ */
