/***************************************************************************//**
 * @file serlcd.h
 * @brief serLCD functionality.
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
 *   @n
 *
 *   Code based on: https://github.com/sparkfun/SparkFun_SerLCD_Arduino_Library/blob/master/src/SerLCD.cpp
 *
 ******************************************************************************/

/* Include guards prevent multiple inclusions of the same header */
#ifndef _SERLCD_H_
#define _SERLCD_H_


/* Includes necessary for this header file */
#include <stdint.h>  /* (u)intXX_t */
#include <stdbool.h> /* "bool", "true", "false" */


/* Public prototypes */
int8_t clearLCD (void);
int8_t writeCharLCD (uint8_t data);
int8_t writeStringLCD (char *message);
int8_t setCursorLCD (uint8_t col, uint8_t row);
int8_t heartBeatLCD (void);


#endif /* _SERLCD_H_ */
