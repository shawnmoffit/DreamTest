#include "derivative.h"

#ifndef K40_TOWER_BOARD_SUPPORT_H_
#define K40_TOWER_BOARD_SUPPORT_H_

//The E1 LED is on Port C, Bit 7
#define LED_E1_LOC (1<<7)
#define LED_E2_LOC (1<<8)
#define LED_E3_LOC (1<<9)
#define LED_E4_LOC (1<<11)

        //There are dedicated set and clear registers.
        //Write a one to PSOR Sets the Bits, Writing to PCOR clears bits.
        //Toggling a bit can be done with the PTOR register
        //You can access the raw register as well -> PDOR |= My Bit
        //but the dedicated bit set/clear/toggle registers are easier!

        //Also,  The cathode of the LEDs are towards the port pin!  This means
        //you have to turn the port off to get the LED to turn the pin on.

#define LED_E1_OFF		GPIOC_PSOR=LED_E1_LOC
#define LED_E1_ON		GPIOC_PCOR=LED_E1_LOC
#define LED_E1_TOGGLE 	GPIOC_PTOR=LED_E1_LOC

#define LED_E2_OFF		GPIOC_PSOR=LED_E2_LOC
#define LED_E2_ON		GPIOC_PCOR=LED_E2_LOC
#define LED_E2_TOGGLE 	GPIOC_PTOR=LED_E2_LOC

#define LED_E3_OFF		GPIOC_PSOR=LED_E3_LOC
#define LED_E3_ON		GPIOC_PCOR=LED_E3_LOC
#define LED_E3_TOGGLE 	GPIOC_PTOR=LED_E3_LOC

#define LED_E4_OFF		GPIOB_PSOR=LED_E4_LOC
#define LED_E4_ON		GPIOB_PCOR=LED_E4_LOC
#define LED_E4_TOGGLE 	GPIOB_PTOR=LED_E4_LOC

// The CameraInterface Module - Enable GPIO on 2 Pins

#define TAOS_CLK_LOC (1<<28) 
#define TAOS_SI_LOC (1<<18) 


#endif /* K40_TOWER_BOARD_SUPPORT_H_ */
