/*#include "SystemHeaders.h"

#define FTM1_CLK_PRESCALE			6
#define FTM1_OVERFLOW_FREQUENCY 	100



void InitFlexTimer_Motor()
{
	SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK; //Enable the clock to the FTM0 module
	
	//turn off FTM write protection;
	FTM1_MODE |= FTM_MODE_WPDIS_MASK;
	
	FTM1_SC = 0; //Make sure its Off!
	//Edit registers when no clock is fed to timer so the MOD value, gets pushed in immediately

	FTM1_SC |= FTM_SC_PS(FTM1_CLK_PRESCALE); //divide the input clock down by 2^FTM1_CLK_PRESCALE
	FTM1_CNT = 0;	//reset the counter to zero
	FTM1_MOD = (PERIPHERAL_BUS_CLOCK/(1<<FTM1_CLK_PRESCALE))/FTM1_OVERFLOW_FREQUENCY ;  //Set the overflow rate
	FTM1_SC |= FTM_SC_TOIE_MASK; //Enable the interrupt mask.
	FTM1_SC |= FTM_SC_CLKS(1); //Select the System Clock
	enable_irq(62);

}

unsigned char LED_E3_Tick = 0;

void FlexTimer_Motor_Irq()
{
	//Clear the overflow mask if set
	if(FTM1_SC & FTM_SC_TOF_MASK)
		FTM1_SC &= ~FTM_SC_TOF_MASK;

	//Turn the Led on and off every second
	LED_E3_Tick++;
	
	if(LED_E3_Tick>=100)
	{
		LED_E3_Tick = 0;
		LED_E3_TOGGLE;
	}
}
*/
