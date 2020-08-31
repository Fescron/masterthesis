/***************************************************************************//**
 * @file BG96_at_driver.c
 * @brief BG96 AT-command driver functionality.
 * @version 1.0
 * @author Brecht Van Eeckhoudt
 *
 * ******************************************************************************
 *
 * @section Versions
 *
 *   @li v1.0: Basic functionality to send measurements to the cloud using NB-IoT
 *             without timeout functionality.
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


#include <stdint.h>         /* (u)intXX_t */
#include <stdbool.h>        /* "bool", "true", "false" */
#include "em_cmu.h"         /* Clock Management Unit */
#include "em_device.h"      /* Include necessary MCU-specific header file */
#include "em_gpio.h"        /* General Purpose IO */

#include "BG96_at_driver.h" /* Corresponding header file */
#include "debug_dbprint.h"  /* Enable or disable printing to UART */
#include "delay.h"          /* Delay functionality */
#include "util_string.h"    /* String functionality */
#include "datatypes.h"      /* Definitions of the custom data-types */
#include "credentials.h"    /* DEVICE_ID and DEVICE_TOKEN */
#include "pin_mapping.h"    /* PORT and PIN definitions */


/* Local definitions */
#define PRINT_ID_TOKEN 0 /* 0 = don't print ID & Token, 1 = print ID & Token */


/* Local variables */
/*   Convert ASCII to hex:
 *    => "-1" to get the correct length because the NULL termination character is at the end of the array
 *    => "*2" because one ASCII char becomes two HEX chars
 *    => "+1" to add the NULL termination character at the end
 */
char DEVICE_ID_hex[2*(sizeof(DEVICE_ID)-1) +1];
char DEVICE_TOKEN_hex[2*(sizeof(DEVICE_TOKEN)-1) +1];


/* Local prototypes */
static bool transmissionBegin (bool continueCode);
static bool transmissionEnd (bool continueCode);


/**************************************************************************//**
 * @brief
 *   Initialize the GPIO pins and UART0 module necessary to communicate with
 *   the BG96 module.
 *****************************************************************************/
void initBG96 (void)
{
	/* Convert ID & Token */
	charASCII_to_charHex(DEVICE_ID, DEVICE_ID_hex);
	charASCII_to_charHex(DEVICE_TOKEN, DEVICE_TOKEN_hex);

#if PRINT_ID_TOKEN == 1 /* PRINT_ID_TOKEN */
#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprint("INFO: DEVICE_ID = ");
		dbprintln(DEVICE_ID);
		dbprint("INFO: DEVICE_ID_hex = ");
		dbprintln(DEVICE_ID_hex);
		dbprintln("");
		dbprint("INFO: DEVICE_TOKEN = ");
		dbprintln(DEVICE_TOKEN);
		dbprint("INFO: DEVICE_TOKEN_hex = ");
		dbprintln(DEVICE_TOKEN_hex);
		dbprintln("");
#endif /* DEBUG_DBPRINT */
#endif /* PRINT_ID_TOKEN */

	/* Enable oscillator to GPIO*/
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Initialize GPIO pin for PWR key */
	/* In the case of gpioModePushPull, the last argument directly sets the pin state */
	GPIO_PinModeSet(BG96_PWRKEY_PORT, BG96_PWRKEY_PIN, gpioModePushPull, 0);

	/*
	 * USART_INITASYNC_DEFAULT:
	 *   config.enable = usartEnable       // Specifies whether TX and/or RX is enabled when initialization is completed
	 *                                     // (Enable RX/TX when initialization is complete).
	 *   config.refFreq = 0                // USART/UART reference clock assumed when configuring baud rate setup
	 *                                     // (0 = Use current configured reference clock for configuring baud rate).
	 *   config.baudrate = 115200          // Desired baudrate (115200 bits/s).
	 *   config.oversampling = usartOVS16  // Oversampling used (16x oversampling).
	 *   config.databits = usartDatabits8  // Number of data bits in frame (8 data bits).
	 *   config.parity = usartNoParity     // Parity mode to use (no parity).
	 *   config.stopbits = usartStopbits1  // Number of stop bits to use (1 stop bit).
	 *   config.mvdis = false              // Majority Vote Disable for 16x, 8x and 6x oversampling modes (Do not disable majority vote).
	 *   config.prsRxEnable = false        // Enable USART Rx via PRS (Not USART PRS input mode).
	 *   config.prsRxCh = 0                // Select PRS channel for USART Rx. (Only valid if prsRxEnable is true - PRS channel 0).
	 *   config.autoCsEnable = false       // Auto CS enabling (Auto CS functionality enable/disable switch - disabled).
	 */

	USART_InitAsync_TypeDef config = USART_INITASYNC_DEFAULT;

	/* Enable oscillator to USARTx modules */
	if (BG96_UART == USART0) CMU_ClockEnable(cmuClock_USART0, true);
	else if (BG96_UART == USART1) CMU_ClockEnable(cmuClock_USART1, true);

	/* Set pin modes for UART TX and RX pins */
	if (BG96_UART == USART0)
	{
		switch (BG96_UART_LOC)
		{
			case 0:
				GPIO_PinModeSet(gpioPortE, 11, gpioModeInput, 0);    /* RX */
				GPIO_PinModeSet(gpioPortE, 10, gpioModePushPull, 1); /* TX */
				break;
			case 2:
				GPIO_PinModeSet(gpioPortC, 10, gpioModeInput, 0);    /* RX */
				/* No TX pin in this mode */
				break;
			case 3:
				GPIO_PinModeSet(gpioPortE, 12, gpioModeInput, 0);    /* RX */
				GPIO_PinModeSet(gpioPortE, 13, gpioModePushPull, 1); /* TX */
				break;
			case 4:
				GPIO_PinModeSet(gpioPortB, 8, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortB, 7, gpioModePushPull, 1);  /* TX */
				break;
			case 5:
			case 6:
				GPIO_PinModeSet(gpioPortC, 1, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 1);  /* TX */
				break;
			/* default: */
				/* No default */
		}
	}
	else if (BG96_UART == USART1)
	{
		switch (BG96_UART_LOC)
		{
			case 0:
				GPIO_PinModeSet(gpioPortC, 1, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 1);  /* TX */
				break;
			case 2:
			case 3:
				GPIO_PinModeSet(gpioPortD, 6, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortD, 7, gpioModePushPull, 1);  /* TX */
				break;
			case 4:
				GPIO_PinModeSet(gpioPortA, 0, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortF, 2, gpioModePushPull, 1);  /* TX */
				break;
			case 5:
				GPIO_PinModeSet(gpioPortC, 2, gpioModeInput, 0);     /* RX */
				GPIO_PinModeSet(gpioPortC, 1, gpioModePushPull, 1);  /* TX */
				break;
			/* default: */
				/* No default */
		}
	}

	/* Initialize USART asynchronous mode */
	USART_InitAsync(BG96_UART, &config);

	/* Route pins */
	switch (BG96_UART_LOC)
	{
		case 0:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC0;
			break;
		case 1:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC1;
			break;
		case 2:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC2;
			break;
		case 3:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC3;
			break;
		case 4:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC4;
			break;
		case 5:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC5;
			break;
		case 6:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_LOC6;
			break;
		default:
			BG96_UART->ROUTE |= USART_ROUTE_TXPEN | USART_ROUTE_RXPEN | USART_ROUTE_LOCATION_DEFAULT;
	}

}


/**************************************************************************//**
 * @brief
 *   Send measurements to the cloud using NB-IoT.
 *
 * @param[in] data
 *   The measurements to send
 *****************************************************************************/
void sendMeasurements (MeasurementData_t *data)
{
	/* Begin transmission */
	bool continueCode = transmissionBegin(true);

	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprintln("INFO: Sending the following values to the cloud:");
		dbprint("      t1 = ");
		dbprintInt(data->t1);
		dbprint(", t2 = ");
		dbprintInt(data->t2);
		dbprint(", p = ");
		dbprintInt(data->p);
		dbprint(", n1 = ");
		dbprintInt(data->n1);
		dbprint(", n2 = ");
		dbprintInt(data->n2);
		dbprint(", r = ");
		dbprintInt(data->r);
		dbprint(", c = ");
		dbprintlnInt(data->c);
#endif /* DEBUG_DBPRINT */

		/* Convert values */
		char t1_hex[9]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
		uint32_to_charHex(data->t1, t1_hex); // TODO: Make sure we can send negative values!
		char t2_hex[9];
		uint32_to_charHex(data->t2, t2_hex); // TODO: Make sure we can send negative values!
		char p_hex[9];
		uint32_to_charHex(data->p, p_hex);
		char n1_hex[9];
		uint32_to_charHex(data->n1, n1_hex);
		char n2_hex[9];
		uint32_to_charHex(data->n2, n2_hex);
		char r_hex[9];
		uint32_to_charHex(data->r, r_hex);
		char c_hex[9];
		uint32_to_charHex(data->c, c_hex);

		/*
		 * http://cbor.me/
		 *
		 * Diagnostic:
		 * {
		 *   "t1": 2345,
		 *   "t2": 2345,
		 *   "p":  2345,
		 *   "n1": 2345,
		 *   "n2": 2345,
		 *   "r":  2345,
		 *   "c":  2345
		 * }
		 *
		 * CBOR:
		 * A7         # map(7)
		 *    62      # text(2)
		 *       7431 # "t1"
		 *    19 0929 # unsigned(2345) (19 ~ uint16_t)
		 *    62      # text(2)
		 *       7432 # "t2"
		 *    19 0929 # unsigned(2345)
		 *    61      # text(1)
		 *       70   # "p"
		 *    19 0929 # unsigned(2345)
		 *    62      # text(2)
		 *       6E31 # "n1"
		 *    19 0929 # unsigned(2345)
		 *    62      # text(2)
		 *       6E32 # "n2"
		 *    19 0929 # unsigned(2345)
		 *    61      # text(1)
		 *       72   # "r"
		 *    19 0929 # unsigned(2345)
		 *    61      # text(1)
		 *       63   # "c"
		 *    19 0929 # unsigned(2345)
		 */

		/* Send commands */
		sendCMD("AT+QISENDEX=0,\"");
		sendCMD(DEVICE_ID_hex);
		sendCMD("0a"); /* \n */
		sendCMD(DEVICE_TOKEN_hex);
		sendCMD("0a"); /* \n */
		sendCMD("a762743119"); /* 0xa6 = map(7), 0x62 = text(2), 0x7431 = "t1", 0x19 = uint16_t */
		sendCMD(t1_hex);
		sendCMD("62743219"); /* 0x62 = text(2), 0x7432 = "t2", 0x19 = uint16_t */
		sendCMD(t2_hex);
		sendCMD("617019"); /* 0x61 = text(1), 0x70 = "p", 0x19 = uint16_t */
		sendCMD(p_hex);
		sendCMD("626e3119"); /* 0x62 = text(2), 0x6e31 = "n1", 0x19 = uint16_t */
		sendCMD(n1_hex);
		sendCMD("626e3219"); /* 0x62 = text(2), 0x6e32 = "n2", 0x19 = uint16_t */
		sendCMD(n2_hex);
		sendCMD("617219"); /* 0x61 = text(1), 0x72 = "r", 0x19 = uint16_t */
		sendCMD(r_hex);
		sendCMD("616319"); /* 0x61 = text(1), 0x63 = "c", 0x19 = uint16_t */
		sendCMD(c_hex);
		sendCMD("\"\n\r");

		/* Wait for the correct response */
		continueCode = waitForResponse("SEND OK", 5);
	}

	/* End transmission */
	continueCode = transmissionEnd(continueCode);
}


/**************************************************************************//**
 * @brief
 *   Send status to the cloud using NB-IoT.
 *
 * @param[in] status
 *   The status value to send
 *****************************************************************************/
void sendStatus (int8_t status)
{
	/* Begin transmission */
	bool continueCode = transmissionBegin(true);

	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprintln("INFO: Sending status ");
		dbprintInt(status);
		dbprintln(" to the cloud.");
#endif /* DEBUG_DBPRINT */

		/* Convert values */
		char s_hex[9]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
		uint32_to_charHex(status, s_hex); // TODO: Make sure we can send negative values!

		/*
		 * http://cbor.me/
		 *
		 * Diagnostic:
		 * {
		 *   "s": 2345
		 * }
		 *
		 * CBOR:
		 * A1         # map(1)
		 *    61      # text(1)
		 *       73   # "s"
		 *    19 0929 # unsigned(2345) (19 ~ uint16_t)
		 */

		/* Send commands */
		sendCMD("AT+QISENDEX=0,\"");
		sendCMD(DEVICE_ID_hex);
		sendCMD("0a"); /* \n */
		sendCMD(DEVICE_TOKEN_hex);
		sendCMD("0a"); /* \n */
		sendCMD("a1617319"); /* 0xa1 = map(1), 0x61 = text(1), 0x73 = "s", 0x19 = uint16_t */
		sendCMD(s_hex);
		sendCMD("\"\n\r");

		/* Wait for the correct response */
		continueCode = waitForResponse("SEND OK", 5);
	}

	/* End transmission */
	continueCode = transmissionEnd(continueCode);
}


/**************************************************************************//**
 * @brief
 *   Send current pulses to the cloud using NB-IoT.
 *
 * @param[in] number
 *   @li `0` - PULSE0 selected.
 *   @li `1` - PULSE0 selected.
 *
 * @param[in] pulse
 *   The pulse value to send
 *****************************************************************************/
void sendPulse (uint8_t number, uint8_t pulse)
{
	/* Begin transmission */
	bool continueCode = transmissionBegin(true);

	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbprintln("INFO: Sending pulse(s) [");
		dbprintInt(pulse);
		dbprintln("] to the cloud.");
#endif /* DEBUG_DBPRINT */

		/* Convert values */
		char pulse_hex[9]; // TODO: Use less chars here because we use uint16_t (check if values aren't bigger than 0xFFFF)
		uint32_to_charHex(pulse, pulse_hex);

		/*
		 * http://cbor.me/
		 *
		 * Diagnostic:
		 * {
		 *   "p1": 2345
		 * }
		 *
		 * CBOR:
		 * A1         # map(1)
		 *    62      # text(2)
		 *       7031 # "p1"
		 *    19 0929 # unsigned(2345) (19 ~ uint16_t)
		 */

		/* Send commands */
		sendCMD("AT+QISENDEX=0,\"");
		sendCMD(DEVICE_ID_hex);
		sendCMD("0a"); /* \n */
		sendCMD(DEVICE_TOKEN_hex);
		sendCMD("0a"); /* \n */
		if (number == 0) sendCMD("a162703119"); /* 0xa1 = map(1), 0x62 = text(2), 0x7031 = "p1", 0x19 = uint16_t */
		else if (number == 1) sendCMD("a162703219"); /* 0xa1 = map(1), 0x62 = text(2), 0x7032 = "p2", 0x19 = uint16_t */
		sendCMD(pulse_hex);
		sendCMD("\"\n\r");

		/* Wait for the correct response */
		continueCode = waitForResponse("SEND OK", 5);
	}

	/* End transmission */
	continueCode = transmissionEnd(continueCode);
}


/**************************************************************************//**
 * @brief
 *   Code for the start of a NB-IoT transmission.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *
 * @param[in] continueCode
 *   Functionality to skip code if previous code failed.
 *
 * @return
 *   If the code finished okay/failed.
 *****************************************************************************/
static bool transmissionBegin (bool continueCode)
{
#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("Powering on BG96");
#endif /* DEBUG_DBPRINT */

	powerBG96(); /* Power up BG96 */
	continueCode = waitForResponse("APP RDY", 5); /* Wait for the correct response */

	sleep(8); // TODO: Wait some time before activating PDP?

	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbinfo("Sending Activate PDP command...");
#endif /* DEBUG_DBPRINT */

		sendCMD("AT+QIACT=1\r");
		continueCode = waitForResponse("OK", 5); /* Wait for the correct response */

		while (!continueCode) // TODO: update timeout functionality
		{
			sleep(2); /* Sleep for 2s */
			sendCMD("AT+QIACT=1\r");
			continueCode = waitForResponse("OK", 5); /* Wait for the correct response */
		}
	}


	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbinfo("Sending Create UDP command...");
#endif /* DEBUG_DBPRINT */

		sendCMD("AT+QIOPEN=1,0,\"UDP\",\"40.68.172.187\",8891\r"); // BEFORE: api.allthingstalk.io
		continueCode = waitForResponse("OK", 5); /* Wait for the correct response */
		continueCode = waitForResponse("+QIOPEN: 0,0", 5); /* Wait for the correct response */
	}

	return (continueCode);
}


/**************************************************************************//**
 * @brief
 *   Code for the end of a NB-IoT transmission.
 *
 * @note
 *   This is a static method because it's only internally used in this file
 *   and called by other methods if necessary.
 *
 * @param[in] continueCode
 *   Functionality to skip code if previous code failed.
 *
 * @return
 *   If the code finished okay/failed.
 *****************************************************************************/
static bool transmissionEnd (bool continueCode)
{
#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("Sending Deactivate PDP command...");
#endif /* DEBUG_DBPRINT */

	sendCMD("AT+QIDEACT=1\r");
	continueCode = waitForResponse("OK", 5); /* Wait for the correct response */

	if (continueCode)
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbinfo("Sending Power down command...");
#endif /* DEBUG_DBPRINT */

		sendCMD("AT+QPOWD\r");
		continueCode = waitForResponse("OK", 5); /* Wait for the correct response */
		continueCode = waitForResponse("POWERED DOWN", 5); /* Wait for the correct response */
	}
	else
	{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
		dbwarn("Powering down BG96 using hardware...");
#endif /* DEBUG_DBPRINT */

		powerBG96();
	}

	sleep(2); // TODO: Wait less

	return (continueCode);
}


/**************************************************************************//**
 * @brief
 *   Method to enable the `power key` for 100ms to enable/disable the module.
 *****************************************************************************/
void powerBG96 (void)
{
	/* Set PWK high for 100ms */
	GPIO_PinOutSet(BG96_PWRKEY_PORT, BG96_PWRKEY_PIN);
	delay(100);
	GPIO_PinOutClear(BG96_PWRKEY_PORT, BG96_PWRKEY_PIN);
}


/**************************************************************************//**
 * @brief
 *   Disable echo.
 *****************************************************************************/
void disableEcho (void)
{

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbinfo("Sending Disable Echo command...");
#endif /* DEBUG_DBPRINT */

	bool continueCode = true;

	sendCMD("ATE0\r");

	while (!continueCode) // TODO: update this code with timeout functionality?
	{
		sleep(2);
		sendCMD("ATE0\r");
		continueCode = waitForResponse("OK", 5); /* Wait for the correct response */
	}
}


/**************************************************************************//**
 * @brief
 *   Print a string (char array) to USARTx.
 *
 * @note
 *   If the input is not a string (ex.: `"Hello world!"`) but a char array,
 *   the input message (array) needs to end with NULL (`"\0"`)!
 *
 * @param[in] message
 *   The string to print to USARTx.
 *****************************************************************************/
void sendCMD (char *message)
{
	/* "message[i] != 0" makes "uint32_t length = strlen(message)"
	 * not necessary (given string MUST be terminated by NULL for this to work) */
	for (uint32_t i = 0; message[i] != 0; i++)
	{
		USART_Tx(BG96_UART, message[i]);
	}
}


/**************************************************************************//**
 * @brief
 *   Read a string (char array) from USARTx.
 *
 * @note
 *   The reading stops when a `"LF"` (Line Feed) character
 *   is received or the maximum length (`UART_BUFFER_SIZE`) is reached.
 *
 * @param[in] buf
 *   The buffer to put the resulting string in.@n
 *   **This needs to have a length of `UART_BUFFER_SIZE` for the function
 *   to work properly: `char buf[UART_BUFFER_SIZE];`!**
 *****************************************************************************/
void readResponse (char *buf)
{
	for (uint32_t i = 0; i < UART_BUFFER_SIZE - 1 ; i++ )
	{
		char localBuffer = USART_Rx(BG96_UART);

		/* Check if a LF character is received */
		if (localBuffer == '\n')
		{
			/* End with a null termination character */
			buf[i] = '\0';
			break;
		}
		else
		{
			buf[i] = localBuffer;
		}
	}
}


/**************************************************************************//**
 * @brief
 *   Wait for the correct response using sleep/timeout functionality.
 *
 * @param[in] response
 *   The correct response to look for.
 *
 * @param[in] timeout
 *   The timeout value.
 *
 * @return
 *   @li `true` - Module responded correctly before timeout.
 *   @li `false` - The module timed out or gave only incorrect responses.
 *****************************************************************************/
bool waitForResponse (char *response, uint8_t timeout)
{
	uint8_t i = 0;

	char rxBuf[UART_BUFFER_SIZE];

	while (i < timeout) // TODO: update timeout functionality
	{
		readResponse(rxBuf);

		if (stringStartsWith((char *)rxBuf, response))
		{

//#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
//			dbprint("INFO: > ");
//			dbprint(response);
//			dbprintln("");
//#endif /* DEBUG_DBPRINT */

			return(true);
		}
		else if (stringStartsWith((char *)rxBuf, "ERROR"))
		{

//#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
//			dbcrit(" > ERROR");
//#endif /* DEBUG_DBPRINT */

			return(false);
		}

		i++;
	}

#if DEBUG_DBPRINT == 1 /* DEBUG_DBPRINT */
	dbprint_color("CRIT: Timeout reached while waiting on ", RED);
	dbprint(response);
	dbprint_color(" command", RED);
	dbprintln("");
#endif /* DEBUG_DBPRINT */

	return(false);
}
