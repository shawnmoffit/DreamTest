/*
 * Pwm_Motor.c
 *
 *  Created on: Mar 31, 2011
 *      Author: Andy
 */

#define Motor_PWM_PIN  0x3 //pin A38 on Tower Header
#define Motor_PWM_complimentary_PIN 0x??  //pin ?? on Tower Header

void InitMotorPWM ();
void MotorTick();
void SetMotorPWM(float DutyCyle);
extern volatile unsigned char MotorTickVar;


