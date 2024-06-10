/******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer1.c
 *
 * Description: Source file for the Timer1 driver
 *
 * Author: Omar Talaat
 *
 *******************************************************************************/
#include "timer1.h"
#include "common_macros.h"
#include "avr/io.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *              				     ISRs                                      *
 *******************************************************************************/

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Timer1_Config)
{
	/* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. Select mode (Timer1_Config->mode)
	 */
	TCCR1A=(1<<FOC1A)|(((Timer1_Config->mode)&0x03)<<WGM10);


	/* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/8 CS10=0 CS11=1 CS12=0
	 */
	TCCR1B=((((Timer1_Config->mode)&0x0C)>>2)<<WGM12)|(Timer1_Config->prescaler);

	TCNT1=Timer1_Config->initial_value;

	OCR1A=Timer1_Config->compare_value;

	TIMSK |= (1<<OCIE1A);

	SREG|=(1<<7);
}


/*
 * Description:
 * Function to de-initialize the Timer driver
 */
void Timer1_deInit(void)
{
	TIMSK&=~(1<<OCIE1A);
	SREG&=~(1<<7);
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	OCR1A=0;
	g_callBackPtr = NULL_PTR;

}

/*
 * Description:
 * Function to set the Call Back function address
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
