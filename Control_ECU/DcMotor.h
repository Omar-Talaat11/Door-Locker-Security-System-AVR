/******************************************************************************
 *
 * Module: DcMotor
 *
 * File Name: DcMotor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Omar Talaat
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DCMOTOR_ENABLE_PORT PORTB_ID
#define DCMOTOR_ENABLE_PIN PIN3_ID

#define DCMOTOR_OUTPUT_PORT PORTB_ID
#define DCMOTOR_OUTPUT_PIN1 PIN0_ID
#define DCMOTOR_OUTPUT_PIN2 PIN1_ID

#define DCMOTOR_SPEED_0 0
#define DCMOTOR_SPEED_25 64
#define DCMOTOR_SPEED_50 128
#define DCMOTOR_SPEED_75 192
#define DCMOTOR_SPEED_100 255

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/
typedef enum{
	Stop,
	CW,
	A_CW
}DcMotor_State;

typedef enum{
	No_Speed,
	First_Speed,
	Second_Speed,
	Third_Speed,
	Fourth_Speed
}DCMotor_Speed;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

/* Description
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,DCMotor_Speed speed);


#endif /* DCMOTOR_H_ */
