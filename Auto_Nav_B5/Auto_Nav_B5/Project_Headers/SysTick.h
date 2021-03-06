#ifndef SYSTICK_H_
#define SYSTICK_H_

void InitSysTick();
void SysTickIrq();
void Delay(unsigned int TicksIn10mS);

#define SYSTICK_FREQUENCY 1000

extern volatile unsigned int ImageCaptureTick;

#endif /* SYSTICK_H_ */
