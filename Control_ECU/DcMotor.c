/******************************************************************************
 *
 * Module: DcMotor
 *
 * File Name: DcMotor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Omar Talaat
 *
 *******************************************************************************/

#include "DcMotor.h"
#include "gpio.h"
#include "PWM.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "buzzer.h"


/* Description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* Set Enable pin direction as Output */
	GPIO_setupPinDirection(DCMOTOR_ENABLE_PORT, DCMOTOR_ENABLE_PIN, PIN_OUTPUT);

	/* Set Output pins direction as Output */
	GPIO_setupPinDirection(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN2, PIN_OUTPUT);

	/* Stop the DC-Motor at the beginning */
	GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN1, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN2, LOGIC_LOW);

}

/* Description
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,DCMotor_Speed speed)
{
	switch(speed)
		{
		case(0):
		{
			PWM_Timer0_Start(DCMOTOR_SPEED_0);
			break;
		}
		case(1):
		{
			PWM_Timer0_Start(DCMOTOR_SPEED_25);
			break;
		}
		case(2):
		{
			PWM_Timer0_Start(DCMOTOR_SPEED_50);
			break;
		}
		case(3):
		{
			PWM_Timer0_Start(DCMOTOR_SPEED_75);
			break;
		}
		case(4):
		{
			PWM_Timer0_Start(DCMOTOR_SPEED_100);
			break;
		}
		}

	switch(state)
	{
	case(0):
	{
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN1, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN2, LOGIC_LOW);
		break;
	}
	case(1):
	{
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN1, LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN2, LOGIC_LOW);
		break;
	}
	case(2):
	{
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN1, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_OUTPUT_PORT, DCMOTOR_OUTPUT_PIN2, LOGIC_HIGH);
		break;
	}
	}
}
