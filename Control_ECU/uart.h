 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	UART_5_Bit,
	UART_6_Bit,
	UART_7_Bit,
	UART_8_Bit,
	UART_9_Bit=7
}UART_BitData;

typedef enum
{
	No_Partiy,
	Even_Partiy=2,
	Odd_Partiy=3
}UART_Parity;

typedef enum
{
	Stop_OneBit,
	Stop_TwoBit
}UART_StopBit;

typedef enum
{
	UART_Rate_2400=2400,
	UART_Rate_4800=4800,
	UART_Rate_9600=9600,
	UART_Rate_14400=14400,
	UART_Rate_19200=19200,
	UART_Rate_28800=28800,
	UART_Rate_38400=38400,
	UART_Rate_57600=57600,
	UART_Rate_76800=76800,
	UART_Rate_115200=115200,
	UART_Rate_230400=230400,
	UART_Rate_250000=250000,
	UART_Rate_500000=500000,
	UART_Rate_1000000=1000000
}UART_BaudRate;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_ConfigType* UART_Config);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
