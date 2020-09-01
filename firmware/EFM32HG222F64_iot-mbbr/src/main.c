/***************************************************************************//**
 * @file main.c
 * @brief The main file for the IoT-MBBR project.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 * *
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
 *   Some methods also use code obtained from examples from [Silicon Labs' GitHub](https://github.com/SiliconLabs/peripheral_examples).
 *   These sections are licensed under the Silabs License Agreement. See the file
 *   "Silabs_License_Agreement.txt" for details. Before using this software for
 *   any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/


#include <stdint.h>         /* (u)intXX_t */
#include <stdbool.h>        /* "bool", "true", "false" */
#include "em_device.h"      /* Include necessary MCU-specific header file */
#include "em_chip.h"        /* Chip Initialization */
#include "em_cmu.h"         /* Clock management unit */
#include "em_gpio.h"        /* General Purpose IO */
#include "em_rtc.h"         /* Real Time Counter (RTC) */

#include "pin_mapping.h"    /* PORT and PIN definitions */
#include "debug_dbprint.h"  /* Enable or disable printing to UART for debugging */
#include "delay.h"          /* Delay functionality */
#include "util.h"           /* Utility functionality */
#include "util_string.h"    /* String functionality */
#include "interrupt.h"      /* GPIO wake-up initialization and interrupt handlers */
#include "DS18B20.h"        /* Functions related to the temperature sensor */
#include "adc.h"            /* Internal voltage and temperature reading functionality */
#include "datatypes.h"      /* Definitions of the custom data-types */
#include "serlcd.h"         /* serLCD functionality */
#include "BG96_at_driver.h" /* BG96 functionality */
#include "VL53L1X.h"        /* VL53L1X functionality */
#include "SHT30.h"          /* SHT30 functionality */


/* Local definitions */
/** Enable (1) or disable (0) the `status = 0` message */
#define SEND_STATUS_BOOT 1

/** Enable (1) or disable (0) sending of messages (for debugging) */
#define SENDING_DATA 1

/** Maximum measured height for percent calculation [mm] */
#define MAX_LENGTH_MM 300

/** Time between each wake-up in seconds
 *    @li max 500 seconds when using LFXO delay
 *    @li 3600 seconds (one hour) works fine when using ULFRCO delay */
#define WAKE_UP_PERIOD_S 3600 /* 360 = every 5 minutes */

/* Local variables */
/** Keep the state of the state machine */
static MCU_State_t MCUstate; /* Static so it's always kept in memory (@data segment, space provided during compile time) */

/** Keep the measurement data */
MeasurementData_t data;


/**************************************************************************//**
 * @brief
 *   Method to check if any interrupts are triggered by buttons.
 *
 * @return
 *   @li `true` - A button interrupt was triggered.
 *   @li `false` - No button interrupt was triggered.
 *****************************************************************************/
bool checkBTNinterrupts (void)
{
	bool value = false;

	if (BTN_getTriggered())
	{
		value = true;

		BTN_setTriggered(false); /* Clear variable */
	}

	return (value);
}


/**************************************************************************//**
 * @brief
 *   Method to display the latest measurements on the LCD.
 *****************************************************************************/
void displayMeas (void)
{
	setCursorLCD(1, 2); /* Move to second row, first column */
	writeStringLCD("T1 ");

	uint16_t temp1 = data.t1;
	if (data.t1 > 9999) temp1 /= 10; /* Remove last digit */ // TODO: round up/down!
	uint8_t temp1L = temp1 / 100;
	uint8_t temp1R = temp1 - ((temp1 / 100) * 100);
	char temp1L_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	char temp1R_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(temp1L, temp1L_char); // TODO: display negative values!
	uint32_to_charDec(temp1R, temp1R_char); // TODO: display negative values!

	writeStringLCD(temp1L_char);
	writeStringLCD(".");
	writeStringLCD(temp1R_char);
	writeStringLCD("C  T2 ");

	uint16_t temp2= data.t2;
	if (data.t2 > 9999) temp2 /= 10; /* Remove last digit */ // TODO: round up/down!
	uint8_t temp2L = temp2 / 100;
	uint8_t temp2R = temp2 - ((temp2 / 100) * 100);
	char temp2L_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	char temp2R_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(temp2L, temp2L_char); // TODO: display negative values!
	uint32_to_charDec(temp2R, temp2R_char); // TODO: display negative values!

	writeStringLCD(temp2L_char);
	writeStringLCD(".");
	writeStringLCD(temp2R_char);
	writeStringLCD("C");

	setCursorLCD(1, 3); /* Move to third row, first column */
	writeStringLCD("N1 ");

	char nitr1_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(data.n1, nitr1_char);

	writeStringLCD(nitr1_char);
	writeStringLCD("mA N2 ");

	char nitr2_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(data.n2, nitr2_char);

	writeStringLCD(nitr2_char);
	writeStringLCD("mA C");

	char carbon_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(data.c, carbon_char);

	writeStringLCD(carbon_char);
	writeStringLCD("%");

	setCursorLCD(1, 4); /* Move to fourth row, first column */
	writeStringLCD("pH ");

	char pH_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(data.p, pH_char);

	writeStringLCD(pH_char);
	writeStringLCD("mA RP ");

	char red_char[10]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
	uint32_to_charDec(data.r, red_char);

	writeStringLCD(red_char);
	writeStringLCD("mA");

	delay(50); // Quick fix
}


/**************************************************************************//**
 * @brief
 *   Main function.
 *****************************************************************************/
int main (void)
{
	/* Value to keep the remaining sleep time when waking up using the accelerometer */
	uint32_t remainingSleeptime = 0;

	while (1)
	{
		switch (MCUstate)
		{
			case INIT:
			{
				/* Initialize chip */
				CHIP_Init();

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbprint_INIT(DBG_UART, DBG_UART_LOC, false, false);
#endif  /* DEBUG_DBPRINT */

				/* Initialize delay and sleep functionality */
				delay(0);
				sleep(2); /* Time so the I2C devices have time to start up */

				/* Initialize the LCD */
				clearLCD();
				writeStringLCD("Initializing...");

				/* Soft reset SHT30 */ // TODO: SHT30 (0x88) seems to respond to VL53L1X (0x52) commands and break the I2C bus until power cycle
//				softResetSHT30();
//				delay(2000);

				/* Initialize GPIO wake-up */
				initGPIOwakeup();

				/* Init VL53L1X */
				initVL53L1X();

				/* Initialize BG96 */
#if SENDING_DATA == 1 /* SENDING_DATA */
				initBG96();
#endif /* SENDING_DATA */

#if SEND_STATUS_BOOT == 1 /* SEND_STATUS_BOOT */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbwarn("Sending startup status ...");
#endif /* DEBUG_DBPRINT */

				clearLCD();
				writeStringLCD("Sending status (0)");

#if SENDING_DATA == 1 /* SENDING_DATA */
				sendStatus(0); /* Send the status data */
#endif /* SENDING_DATA */

#endif /* SEND_STATUS_BOOT */

				MCUstate = MEASURE;
			} break;

			case MEASURE:
			{
				clearLCD();
				writeStringLCD("Measuring...");
				displayMeas(); /* Display measurements on following rows */

				/* Measure and store the temperatures */
				int32_t temp = readTempDS18B20(0);
				if (temp < 0) data.t1 = 0;
				else data.t1 = temp;

				temp = readTempDS18B20(1);
				if (temp < 0) data.t2 = 0;
				else data.t2 = temp;

//				data.t2 = SHT30_readTemp(); // TODO: SHT30 (0x88) seems to respond to VL53L1X (0x52) commands and break the I2C bus until power cycle

				/* Measure and store distance */
				uint16_t distance = measureVL53L1X();

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbinfoInt("distance = ", distance, " mm");
#endif /* DEBUG_DBPRINT */

				data.c = (uint16_t)(((float)(MAX_LENGTH_MM - measureVL53L1X()) / MAX_LENGTH_MM) * 100.0);

				// TODO: measure more things!
				data.n1 = 20;
				data.n2 = 20;
				data.p = 20;
				data.r = 20;

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbprintln("");
				dbinfoInt(">> t1: ", data.t1, "");
				dbinfoInt(">> t2: ", data.t2, "");
				dbinfoInt(">> c: ", data.c, " %");
				dbprintln("");
#endif /* DEBUG_DBPRINT */

				MCUstate = SEND_DATA;
			} break;

			case SEND_DATA:
			{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbwarn("Sending measurements ...");
#endif /* DEBUG_DBPRINT */

				clearLCD();
				writeStringLCD("Sending measurements");
				displayMeas(); /* Display measurements on following rows */

#if SENDING_DATA == 1 /* SENDING_DATA */
				sendMeasurements(&data);
#endif /* SENDING_DATA */

				MCUstate = SLEEP;
			} break;

			case SEND_STATUS:
			{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
				dbwarn("Sending STATUS ...");
#endif /* DEBUG_DBPRINT */

				// TODO

				MCUstate = SLEEP;
			} break;

			case SLEEP:
			{
				clearLCD();
				writeStringLCD("Waiting...");
				displayMeas(); /* Display measurements on following rows */


				sleep(WAKE_UP_PERIOD_S); /* Go to sleep for xx seconds */

				MCUstate = WAKEUP;
			} break;

			case WAKEUP:
			{
				/* Check if we woke up using a button */
				if (checkBTNinterrupts())
				{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
					dbprintln("    ");
					dbprintln_color("BTN INT", 4);
#endif /* DEBUG_DBPRINT */

					remainingSleeptime = 0; /* Reset passed sleeping time */
				}

				/* Check if we woke up using the RTC sleep functionality and act accordingly */
				if (RTC_checkWakeup())
				{
					RTC_clearWakeup(); /* Clear variable */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
					dbprintln("    ");
					dbprintln_color("RTC INT", 4);
#endif /* DEBUG_DBPRINT */

					remainingSleeptime = 0; /* Reset passed sleeping time since it's an RTC wakeup */
				}

				/* Check if we woke up because of a current pulse */
				if (PULSE_getTriggered(0) || PULSE_getTriggered(1))
				{
					RTC_Enable(false); /* Disable the counter */

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
					dbprintln("    ");
					dbprintln_color("PULSE INT", 4);
#endif /* DEBUG_DBPRINT */

					clearLCD();
					writeStringLCD("Sending pulses...");
					displayMeas(); /* Display measurements on following rows */

					if (PULSE_getTriggered(0))
					{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
					dbwarn("Sending P1 pulses ...");
#endif /* DEBUG_DBPRINT */

#if SENDING_DATA == 1 /* SENDING_DATA */
						sendPulse (0, 1);
#endif /* SENDING_DATA */

						PULSE_setTriggered(0, false);
					}
					else if (PULSE_getTriggered(1))
					{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
					dbwarn("Sending P2 pulses ...");
#endif /* DEBUG_DBPRINT */

#if SENDING_DATA == 1 /* SENDING_DATA */
						sendPulse (1, 1);
#endif /* SENDING_DATA */

						PULSE_setTriggered(1, false);
					}

					MCUstate = WAKEUP;

					clearLCD();
					writeStringLCD("Waiting...");
					displayMeas(); /* Display measurements on following rows */

					remainingSleeptime += RTC_getPassedSleeptime(); /* Add the time spend sleeping to the variable */

					/* Go back to sleep for the remaining time until another measurement (we only take measurements on RTC/button wake-up) */
					sleep(WAKE_UP_PERIOD_S - remainingSleeptime);

				}
				else
				{
					MCUstate = MEASURE;
				}

			} break;

			default:
			{
				error(10);
			} break;
		}
	}
}


/**************************************************************************//**
 * @brief
 *   NMI interrupt service routine.
 *
 * @note
 *   The *weak* definition for this method is located in `startup_gcc_efm32hg.h`.
 *****************************************************************************/
void NMI_Handler(void)
{
	while(1);
}


/**************************************************************************//**
 * @brief
 *   HardFault interrupt service routine.
 *
 * @note
 *   The *weak* definition for this method is located in `startup_gcc_efm32hg.h`.
 *****************************************************************************/
void HardFault_Handler(void)
{
	while(1);
}


/**************************************************************************//**
 * @brief
 *   SVC interrupt service routine.
 *
 * @note
 *   The *weak* definition for this method is located in `startup_gcc_efm32hg.h`.
 *****************************************************************************/
void SVC_Handler(void)
{
	while(1);
}


/**************************************************************************//**
 * @brief
 *   PendSV interrupt service routine.
 *
 * @note
 *   The *weak* definition for this method is located in `startup_gcc_efm32hg.h`.
 *****************************************************************************/
void PendSV_Handler(void)
{
	while(1);
}


