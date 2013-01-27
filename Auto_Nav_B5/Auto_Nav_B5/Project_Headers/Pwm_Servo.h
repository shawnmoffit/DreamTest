/*
 * Pwm_Servo.h
 *
 *  Created on: Mar 5, 2011
 *      Author: Shawn
 *  
 *  This file set & Pats up the Pulse Width Modulation Timer to go to pin PTC4
 */
 
#define Servo_PWM_PIN  0x4 //pin A37 on Tower Header

void PWM_Servo (double duty_Cycle);
void ServoTick();
void Init_PWM_Servo ();
void PWM_Servo_Angle (float Angle);
extern volatile unsigned char ServoTickVar;
