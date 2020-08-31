/***************************************************************************//**
 * @file datatypes.h
 * @brief Definitions of the custom data-types used.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
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
 *   Some methods use code obtained from examples from [Silicon Labs' GitHub](https://github.com/SiliconLabs/peripheral_examples).
 *   These sections are licensed under the Silabs License Agreement. See the file
 *   "Silabs_License_Agreement.txt" for details. Before using this software for
 *   any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


/* Include guards prevent multiple inclusions of the same header */
#ifndef _DATATYPES_H_
#define _DATATYPES_H_


/* Include necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/** Enum type for the state machine */
typedef enum mcu_states
{
	INIT,
	MEASURE,
	SEND_DATA,
	SEND_STATUS,
	SLEEP,
	WAKEUP
} MCU_State_t;


/** Struct type to store the gathered data */
typedef struct
{
	int32_t t1;  /* Temperature 1 */
	int32_t t2;  /* Temperature 2 */
	uint32_t p;  /* pH */
	uint32_t n1; /* Nitrate concentration 1 */
	uint32_t n2; /* Nitrate concentration 2 */
	uint32_t r;  /* Redox potential */
	uint16_t c;  /* Measured height in carbon source container */
} MeasurementData_t;


#endif /* _DATATYPES_H_ */
