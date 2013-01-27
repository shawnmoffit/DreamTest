/**********************************************************************************************
 * Pwm_Servo.c
 *
 *  Created on: Mar 5, 2011
 *      Author: Shawn
 *  
 *  This file sets up the Pulse Width Modulation Timer Module for use by a servo.  It is set 
 *  to utilize Edge-Aligned PWM, and this file properly configures the period, and pulse width 
 *  for use by the other modules
 *  
 *  Several important functions are contained in this file:
 *  1. Init_PWM_Servo () - initializes the timer module 
 *  2. PWM_Servo (double duty_Cycle) - enter the desired duty cycle setting for the servo
 *  3. PWM_Servo_Angle (int Angle) - enter the desired angle for the servo 
 *  	Straight forward - PWM_Servo_Angle (45)
 *  	Full left - PWM_Servo_Angle (90)
 *  	Full right - PWM_Servo_Angle (0)
 *  4. Servo_Tick - interrupt routine which executes once/servo period
 *  
 *  	can choose any angle between 45 and -45 degrees in 5 degree increments
 *  
 * **********  DETAILS *****************
 * 
 * Steering Servo is located on PTC4 - (pin A37 on the tower) (double check this comment)
 *
 * EDGE-Aligned PWM:  selected when QUADEN=0, DECAPEN=0, COMBINE=0, CPWMS=0, and MSnB=1  
 * For typical Servo operation set period to:  20 ms, vary pulse width between .5ms and 1.5ms to set steering angle
 * 
 * Period on chip determined by MOD-CNTIN +0x0001 
 * Pulse width determined by (CnV-CNTIN)  
 * 
 * - see Edge-Aligned PWM (EPWM) Mode in reference manual for details
 * 
 **********************************************************************************************/

#include "SystemHeaders.h"

#define FTM0_CLK_PRESCALE			6  // Prescale Selector value - see comments in Status Control (SC) section for more details
#define FTM0_OVERFLOW_FREQUENCY 	50  // Desired Frequency of PWM Signal - Here 50Hz => 20ms period
// use these to dial in servo steering to your particular servo
#define Pulse_Width_Low 			0.0012  // pulse width required by servo to travel to full left
#define Pulse_Width_High  			0.0018  // pulse width required by servo to travel full right
//add flip servo l/r function

float 	Total_Count;
float	High_Count;
float 	Low_Count;
int 	Scale_Factor;
float 	Angle;
	

/**********************************************************************************************/

void Init_PWM_Servo ()
{

//Enable the Clock to the FTM0 Module
SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;  

//Pin control Register (MUX allowing user to route the desired signal to the pin.  
PORTC_PCR4  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;

//FTM0_MODE[WPDIS] = 1; //Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.  
FTM0_MODE |= FTM_MODE_WPDIS_MASK;

//FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
FTM0_MODE &= ~1; 

//Set Edge Aligned PWM
FTM0_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;  
//QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)

// Also need to setup the FTM0C0SC channel control register 
FTM0_CNT = 0x0; //FTM Counter Value - reset counter to zero
FTM0_MOD = (PERIPHERAL_BUS_CLOCK/(1<<FTM0_CLK_PRESCALE))/FTM0_OVERFLOW_FREQUENCY ;  // Count value of full duty cycle
FTM0_CNTIN = 0; //Set the Counter Initial Value to 0 

// FTMx_CnSC - contains the channel-interrupt status flag control bits
FTM0_C3SC |= FTM_CnSC_ELSB_MASK; //Edge or level select
FTM0_C3SC &= ~FTM_CnSC_ELSA_MASK; //Edge or level Select
FTM0_C3SC |= FTM_CnSC_MSB_MASK; //Channel Mode select

//Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately
FTM0_SC = 0; //Make sure its Off!

//FTMx_CnV contains the captured FTM counter value, this value determines the pulse width
FTM0_C3V = FTM0_MOD; 

//Status and Control bits 
FTM0_SC =  FTM_SC_CLKS(1); // Selects Clock source to be "system clock" or (01) 

//sets pre-scale value see details below
FTM0_SC |= FTM_SC_PS(FTM0_CLK_PRESCALE); 

/******begin FTM_SC_PS details ****************************
* Sets the Prescale value for the Flex Timer Module which divides the 
* Peripheral bus clock -> 48Mhz by the set amount 
* Peripheral bus clock set up in clock.h
*  
* The value of the prescaler is selected by the PS[2:0] bits.  
* (FTMx_SC field bits 0-2 are Prescale bits -  set above in FTM_SC Setting)
*  
*  000 - 0 - No divide
*  001 - 1 - Divide by 2
*  010 - 2 - Divide by 4
*  011 - 3 - Divide by 8
*  100 - 4 - Divide by 16
*  101 - 5 - Divide by 32
*  110 - 6 - Divide by 64 - 
*  111 - 7 - Divide by 128 
*  ******end FTM_SC_PS details*****************************/

// Interrupts
FTM0_SC |= FTM_SC_TOIE_MASK; //Enable the interrupt mask.  timer overflow interrupt.. enables interrupt signal to come out of the module itself...  (have to enable 2x, one in the peripheral and once in the NVIC
enable_irq(62);  // Set NVIC location, but you still have to change/check NVIC file sysinit.c under Project Settings Folder

}

/***************************************Functions to Control Servo Angle ********************************/

void PWM_Servo (double duty_Cycle)  
{
  //FTM0_C3V = FTM0_MOD*(duty_Cycle);
  FTM0_C3V = FTM0_MOD*(duty_Cycle*.01);
}

//PWM_Servo_Angle is an integer value between 0 and 90
//where 0 sets servo to full right, 45 sets servo to middle, 90 sets servo to full left
void PWM_Servo_Angle (float Angle)
{
		High_Count = FTM0_MOD*(Pulse_Width_High)*FTM0_OVERFLOW_FREQUENCY;
		Low_Count = FTM0_MOD*(Pulse_Width_Low)*FTM0_OVERFLOW_FREQUENCY;
		Total_Count = High_Count - Low_Count;
		Scale_Factor = High_Count -Total_Count*(Angle/90);  
		FTM0_C3V = Scale_Factor; //sets count to scaled value based on above calculations
}

/******************************************* Function to control Interrupt ************************************/
volatile unsigned char ServoTickVar;

void ServoTick()
{
if (ServoTickVar < 0xff)//if servo tick less than 255 count up... 
	ServoTickVar++;
//Clear the overflow mask if set
	if(FTM0_SC & FTM_SC_TOF_MASK)
		FTM0_SC &= ~FTM_SC_TOF_MASK;
	LED_E2_TOGGLE; // ends up being 25 Hz  (correct)
	
}
