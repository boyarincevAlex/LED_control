#include "stm32f4xx.h"
#include "display mode.h"
#include "device mode.h"

int n = 0;
int count_TIM1;
int count_over;
uint32_t displayMode = MAIN;
uint32_t deviceMode = OFF;
uint32_t timerMode = DISABLE;
uint32_t impulseMode = ENABLE;

int main()
{
	initSystem();
	initLcd();

	while(1)
	{

	}
}

//PERIOD = ARR*PSC/f
//ARR=1000
//1000ms - 25000
//500ms - 12500
//10ms - 250
//1ms - 25


