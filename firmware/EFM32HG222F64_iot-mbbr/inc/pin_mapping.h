/***************************************************************************//**
 * @file pin_mapping.h
 * @brief The pin definitions for the custom board.
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


/* Include guards prevent multiple inclusions of the same header */
#ifndef _PIN_MAPPING_H_
#define _PIN_MAPPING_H_


/* Include necessary for this header file */
#include "em_device.h" /* Include necessary MCU-specific header file */
#include "em_gpio.h"   /* General Purpose IO */


/* I2C */
#define BUS_I2C            	I2C0
#define BUS_I2C_LOC        	I2C_ROUTE_LOCATION_LOC0
#define BUS_SDA_PORT		gpioPortA
#define BUS_SDA_PIN       	0
#define BUS_SCL_PORT      	gpioPortA
#define BUS_SCL_PIN       	1

/* BUTTON */
#define BTN_PORT      		gpioPortA
#define BTN_PIN       		2

/* VL53L1X */
#define VL53L1X_GPIO1_PORT	gpioPortF
#define VL53L1X_GPIO1_PIN	4
#define VL53L1X_XSHUT_PORT	gpioPortF
#define VL53L1X_XSHUT_PIN	5

/* BG96 */
#define BG96_UART           USART1
#define BG96_UART_LOC       0
#define BG96_TXD_PORT       gpioPortC
#define BG96_TXD_PIN        1
#define BG96_RXD_PORT       gpioPortC
#define BG96_RXD_PIN        0
#define BG96_PWRKEY_PORT    gpioPortC
#define BG96_PWRKEY_PIN     2
#define BG96_RESET_PORT     gpioPortC
#define BG96_RESET_PIN      3
#define BG96_STAT_PORT     	gpioPortC
#define BG96_STAT_PIN      	4
#define BG96_DTR_PORT     	gpioPortA
#define BG96_DTR_PIN      	8
#define BG96_RI_PORT     	gpioPortA
#define BG96_RI_PIN      	9

/* DEBUG UART */
#define DBG_UART            USART0
#define DBG_UART_LOC        2
#define DBG_TXD_PORT        gpioPortC
#define DBG_TXD_PIN         11
#define DBG_RXD_PORT        gpioPortC
#define DBG_RXD_PIN         10
#define DBG_GNDD_PORT       gpioPortC
#define DBG_GNDD_PIN        15

/* DS18B20 */
#define TEMP0_DATA_PORT     gpioPortC
#define TEMP0_DATA_PIN      8
#define TEMP0_VDD_PORT      gpioPortC
#define TEMP0_VDD_PIN       9
#define TEMP1_DATA_PORT     gpioPortA
#define TEMP1_DATA_PIN      10
#define TEMP1_VDD_PORT      gpioPortB
#define TEMP1_VDD_PIN       11

/* PULSE INPUTS */
#define PULSE0_PORT         gpioPortC /* PCNT0_S0IN #0 */
#define PULSE0_PIN          13
#define PULSE1_PORT         gpioPortC /* PCNT0_S1IN #0 */
#define PULSE1_PIN          14

/* ADC INPUTS */
#define ADC0_PORT      		gpioPortD /* ADC0_CH4 */
#define ADC0_PIN       		4
#define ADC1_PORT      		gpioPortD /* ADC0_CH5 */
#define ADC1_PIN       		5
#define ADC2_PORT      		gpioPortD /* ADC0_CH6 */
#define ADC2_PIN       		6
#define ADC3_PORT      		gpioPortD /* ADC0_CH7 */
#define ADC3_PIN       		7

/* SPARE */
#define J28_0_PORT			gpioPortE
#define J28_0_PIN			10
#define J28_1_PORT			gpioPortE
#define J28_1_PIN			11
#define J28_2_PORT			gpioPortE
#define J28_2_PIN			12
#define J28_3_PORT			gpioPortE
#define J28_3_PIN			13
#define J29_0_PORT			gpioPortF
#define J29_0_PIN			2
#define J29_1_PORT			gpioPortF
#define J29_1_PIN			3


#endif /* _PIN_MAPPING_H_ */
