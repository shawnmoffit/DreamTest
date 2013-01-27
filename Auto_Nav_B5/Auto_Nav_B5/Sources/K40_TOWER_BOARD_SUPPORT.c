/*
 * K40_TOWER_BOARD_SUPPORT.c
 *
 *  Created on: Mar 2, 2011
 *      Author: Wavenumber
 */
#include "SystemHeaders.h"

void InitK40GPIO()
{
	  SIM_SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
  
      //To use a Port, its Clock must be enabled!!
	  //Lets just enable the clocks for ALL of the ports
	  
      //Important!  Each IO pin has a dedicated 32-bit Register to set it up (Selection GPIO vs peripheral, IRQ, Etc.)
	  //Setup port C7,C8,C9 and B11 as GPIO and enable High Drive Strength
	   PORTC_PCR7 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   //Enable GPIO on on the pin
	   PORTC_PCR8 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   //Enable GPIO on on the pin
	   PORTC_PCR9 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   //Enable GPIO on on the pin
	   PORTB_PCR11 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   //Enable GPIO on on the pin

	   //CLK and SI signal
	   PORTC_PCR18 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	   PORTE_PCR28 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
	   
	   //Make Sure the GPIO is setup to be an output
	   GPIOC_PDDR |= LED_E1_LOC | LED_E2_LOC | LED_E3_LOC | TAOS_SI_LOC;
	   GPIOE_PDDR |= TAOS_CLK_LOC;
	   GPIOB_PDDR |= LED_E4_LOC;
	   
	   
	   
	   LED_E1_OFF;
	   LED_E2_OFF;
	   LED_E3_OFF;
	   LED_E4_OFF;
	   	   
	
}
