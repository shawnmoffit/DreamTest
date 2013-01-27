/*
 * readADC.c
 *
 *  Created on: Apr 17, 2011
 *      Author: Shawn
 */
#include "systemHeaders.h"

unsigned char ReadADCChannel(unsigned char Channel)
	  {
	  			ADC1_SC1A  =  Channel;
	  			while((ADC1_SC1A & ADC_SC1_COCO_MASK) == 0)
	  			{
	  			}
	  			return 	ADC1_RA;	
	  }
