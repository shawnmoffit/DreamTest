#include "SystemHeaders.h"

void InitSysTick()
{

	SYST_RVR = CORE_CLOCK/SYSTICK_FREQUENCY;
	
	SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;
	
}

volatile unsigned char LED_E1_Tick;
volatile unsigned int DelayTimerTick = 0;
volatile unsigned int ImageCaptureTick = 0;

void SysTickIrq()
{
	if(LED_E1_Tick == 250)
	{
		LED_E1_TOGGLE;
		LED_E1_Tick = 0;
	}
	else
	{
		LED_E1_Tick++;
	}
	
	if(DelayTimerTick<0xFFFFFFFF)
	{
		DelayTimerTick++;
	}
	
	if(ImageCaptureTick<0xFFFFFFF)
	{
		ImageCaptureTick++;
	}
}

void Delay(unsigned int TicksIn10mS)
{
	DelayTimerTick = 0;

	while(DelayTimerTick<TicksIn10mS)
	{
	//	asm("WFI"); // wait for an interrupt
	}
}

