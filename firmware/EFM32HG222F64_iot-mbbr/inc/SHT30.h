/***************************************************************************//**
 * @file SHT30.h
 * @brief SHT30 functionality.
 * @version 1.0
 * @author Modified by Brecht Van Eeckhoudt
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
#ifndef _SHT30_H_
#define _SHT30_H_


/* Include necessary for this header file */
#include <stdint.h> /* (u)intXX_t */


/* Public prototype */
int8_t softResetSHT30 (void);
int32_t SHT30_readTemp (void);


#endif /* _SHT30_H_ */
