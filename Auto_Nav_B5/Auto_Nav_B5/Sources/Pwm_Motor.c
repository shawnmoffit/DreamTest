/*
 * Pwm_Motor.c
 *
 *  USing 	Port B 0 (pwm)
 *  		Port B 1 (pwm compliment)
 *  
 *  	FTM1_CH0 PTC8 B68 PWM
 *  	FTM1_CH1 pta9
 *  
 *  This file sets up the Pulse Width Modulation Timer Module for use by other modules
 */

#include "SystemHeaders.h"
#define PWM_FREQUENCY	((float)(4000.0))
#define FTM1_MOD_VALUE	(int)((float)(PERIPHERAL_BUS_CLOCK)/PWM_FREQUENCY)

void InitMotorPWM()  
{
	//Enable the Clock to the FTM1 Module
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; 

	// PORTC_PCR4 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   //Enable GPIO on on the pin - 
    
	//route the output of that channel 0 to the pin... (pick a different multiplexer value for routing the timer)
    //ch 11.4.1 of the k40 reference manual is the pin control register
    //For port c pin 1..   bits 10-8  Pin Mux Control...
    PORTA_PCR8  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK;
    PORTA_PCR9  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK;

    // Choose EDGE-Aligned PWM:  selected when QUADEN=0, DECAPEN=0, COMBINE=0, CPWMS=0, and MSnB=1  (page 964)
    // Properly set up Flex Timer Module
    
    //FTM0_MODE[WPDIS] = 1; //Disable Write Protection - enables changes to QUADEN, DECAPEN, etc.  
    FTM1_MODE |= FTM_MODE_WPDIS_MASK;
    
    //FTMEN is bit 0, need to set to zero so DECAPEN can be set to 0
    FTM1_MODE &= ~1; 
    
    //Set Edge Aligned PWM
    FTM1_QDCTRL &=~FTM_QDCTRL_QUADEN_MASK;  
    //QUADEN is Bit 1, Set Quadrature Decoder Mode (QUADEN) Enable to 0,   (disabled)
    //FTM0_SC = 0x16; //Center Aligned PWM Select = 0, sets FTM Counter to operate in up counting mode, 
    //it is field 5 of FTMx_SC (status control) - also setting the pre-scale bits here
    
  //   Also need to setup the FTM0C0SC channel control register  - Page 897   section 37.3.6
  FTM1_CNT = 0x0; //FTM Counter Value - (initialize the CNT before writing to MOD)  (16 bit available - bits 0-15 are count)
  FTM1_MOD = FTM1_MOD_VALUE; //Set the Modulo resister (16 bit available - bits 0-15), Mod is set to 24000
  FTM1_CNTIN = 0; //Set the Counter Initial Value to 0   (pg 915)
  
  //change MSnB = 1
  
  FTM1_C0SC |= FTM_CnSC_ELSB_MASK;
  FTM1_C0SC &= ~FTM_CnSC_ELSA_MASK;
  FTM1_C0SC |= FTM_CnSC_MSB_MASK;
  FTM1_C0V = FTM1_MOD_VALUE/2; //Set the Channel n Value to  (16 bit available - bits 0-15)
  
  //Set the complimentary pinout
  FTM1_C1SC |= FTM_CnSC_ELSB_MASK;
  FTM1_C1SC &= ~FTM_CnSC_ELSA_MASK;
  FTM1_C1SC |= FTM_CnSC_MSB_MASK;
  FTM1_C1V = FTM1_MOD_VALUE/2;
  FTM1_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1);  

  // Interrupts
  FTM1_SC |= FTM_SC_TOIE_MASK; //enable the interrupt mask
  enable_irq(63);  // (79-16) Set NVIC location, but you still have to change/check NVIC file sysinit.c under Project Settings Folder
}

void SetMotorPWM(float DutyCycle)
{
	//float compDuty = (float)100.0-DutyCycle;
	FTM1_C0V =(int)((DutyCycle*.01)* (float)FTM1_MOD_VALUE);
	FTM1_C1V =(int)((1.0-DutyCycle*.01)* (float)FTM1_MOD_VALUE);
}

/******************************************* Function to control Interrupt ************************************/
volatile unsigned char MotorTickVar;

void MotorTick()
{
if (MotorTickVar < 0xff)//if motor tick less than 255 count up... 
	MotorTickVar++;
//Clear the overflow mask if set
	if(FTM1_SC & FTM_SC_TOF_MASK)
		FTM1_SC &= ~FTM_SC_TOF_MASK;
	//LED_E2_TOGGLE; // ends up being ___ Hz  (correct)
	
}

