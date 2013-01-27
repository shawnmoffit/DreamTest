/*
 * *********************CameraInterface.c****************************
 *
 *  Created on: Mar 5, 2011
 *      Author: Shawn
 *  
 *  Camera Interface
 *  
 *  I/0:
 *  
 *  Input: Serial Input to sensor (SI) - begins a scan / exposure
 *  	discrete pulses, pulse must go low before rising edge of next clock pulse 
 *  Input: Clock (CLK)  - latches SI and clocks pixels out (low to high)
 *  	continuous signal
 *  Output: Analog Output (A0) - Analog pixel input from the sensor (0-Vdd) or or tri-stated 
 *      
 *  Exposure or Integration time: 
 *  
 *  Camera begins exposing sensor array 18 clock pulses after SI, 
 *  exposure ends 20us or (tqt)after 129th clock cycle
 *  minimum 20us after 129th clock cycle before next rising edge of SI pulse 
 *  
 *  Integration Time:  T
 *  T = (1/fmax)*(n-18)pixels + 20us, where n is the number of pixels
 *  
 *  Minimum integration time: 33.75us
 *  Maximum integration time: capacitors will saturate if exceeding 100ms
 *  frequency range 5 Khz - 8 Mhz (8 Mhz is fmax in equation above) 
 *  
 *  Note(s):  
 *  
 *  Voltage output is available for entire clock period - so setup 
 *  and hold times for A/D must be less than the clock period
 *  Camera sends out previous data stored in buffer during next operating cycle 
 *  while capturing image data
 *  Assume data is good after 2nd loop through ImageCapture()
 *  
 */

#include "SystemHeaders.h"


#define TAOS_CLK_HIGH  GPIOE_PSOR = TAOS_CLK_LOC  //set register high
#define TAOS_CLK_LOW  GPIOE_PCOR = TAOS_CLK_LOC  //set register low (TAOS_CLK_LOC in K40_Tower_Board_Support)
#define TAOS_SI_HIGH  GPIOC_PSOR = TAOS_SI_LOC
#define TAOS_SI_LOW  GPIOC_PCOR = TAOS_SI_LOC


//loop to set exposure time, can improve later
void ExposureDelay(int delay)
{
int i;
for (i=0;i<delay;i++)
	{
	}	
}	
#define TAOS_EXPOSURE_DELAY ExposureDelay(50)  // 1 ~ 231 us; scale accordingly.
//guad team uses 10ms, reference - 

//turns off CLK and SI
void InitTAOS()
{
	
TAOS_CLK_LOW;
TAOS_SI_LOW;
	
}
/****** Capture Images:*******
 * 
 * Start Clock  
 * Set frequency
 * loop 128 times 
 * ready
 */

void ImageCapture(int * ImageData){//this is a pointer to a single character in memory
	
	unsigned char i;
	TAOS_SI_HIGH;
	TAOS_EXPOSURE_DELAY;
	TAOS_CLK_HIGH;
	TAOS_EXPOSURE_DELAY;
	TAOS_SI_LOW;
	TAOS_EXPOSURE_DELAY;
	ImageData[0] = (int)ReadADCChannel(19);// inputs data from camera (first pixel)
	TAOS_CLK_LOW;
	
	for(i=1;i<128;i++)
	{
		TAOS_EXPOSURE_DELAY;
		TAOS_EXPOSURE_DELAY;
		TAOS_CLK_HIGH;
		TAOS_EXPOSURE_DELAY;
		TAOS_EXPOSURE_DELAY;
		ImageData[i] = (int)ReadADCChannel(19); // inputs data from camera (one pixel each time through loop)
		TAOS_CLK_LOW;
	}
	
	TAOS_EXPOSURE_DELAY;
	TAOS_EXPOSURE_DELAY;
	TAOS_CLK_HIGH;
	TAOS_EXPOSURE_DELAY;
	TAOS_EXPOSURE_DELAY;
	TAOS_CLK_LOW;	
}
