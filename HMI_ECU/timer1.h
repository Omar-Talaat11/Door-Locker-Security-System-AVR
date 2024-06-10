/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the Timer1 driver
 *
 * Author: Omar Talaat
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                              Definitions		                               *
 *******************************************************************************/
#define TIMER1_DEFAULT_INITIAL	0
#define TIMER1_NOT_COMPARE	0

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

typedef enum{
	Prescaler_No_Clock,
	Prescaler_1,
	Prescaler_8,
	Prescaler_64,
	Prescaler_256,
	Prescaler_1024,
	Prescaler_External_Falling,
	Prescaler_External_Rising
}Timer1_Prescaler;

typedef enum{
	Timer1_Normal_Mode,
	Timer1_Compare_Mode=4
}Timer1_Mode;


typedef struct {
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
	} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description:
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Timer1_Config);


/*
 * Description:
 * Function to de-initialize the Timer driver
 */
void Timer1_deInit(void);

/*
 * Description:
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
