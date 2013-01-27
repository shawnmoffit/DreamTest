/*#include "SystemHeaders.h"

#define FTM0_CLK_PRESCALE			6
#define FTM0_OVERFLOW_FREQUENCY 	100

void InitFlexTimer0()
{
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK; //Enable the clock to the FTM0 module
	
	//turn off FTM write protection;
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;
	
	FTM0_SC = 0; //Make sure its Off!
	//Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately

	FTM0_SC |= FTM_SC_PS(FTM0_CLK_PRESCALE); //divide the input clock down by 2^FTM0_CLK_PRESCALE
	FTM0_CNT = 0;	//reset the counter to zero
	FTM0_MOD = (PERIPHERAL_BUS_CLOCK/(1<<FTM0_CLK_PRESCALE))/FTM0_OVERFLOW_FREQUENCY ;  //Set the overflow rate
	FTM0_SC |= FTM_SC_TOIE_MASK; //Enable the interrupt mask.
	FTM0_SC |= FTM_SC_CLKS(1); //Select the System Clock
	enable_irq(62);
	
}



void FlexTimer0_Irq()
{
	//Clear the overflow mask if set
	if(FTM0_SC & FTM_SC_TOF_MASK)
		FTM0_SC &= ~FTM_SC_TOF_MASK;

	//Turn the Led on and off every second
	//LED_E2_Tick++;
	
	//if(LED_E2_Tick>=100)
	{
		//LED_E2_Tick = 0;
		LED_E2_TOGGLE;
	}
}
*/
